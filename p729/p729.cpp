#include <flint/arb_poly.h>
#include <flint/arb_calc.h>
#include <omp.h>
#include "cpplib/pythonlike.h"
#include "cpplib/stopwatch.h"

using namespace pythonlike;

static size_t eval_count = 0;  // Tracks how often the function was called/evaluated.

class RootFinder
{
    size_t d_num = 0;           // Holds total number of intervals/roots.
    size_t d_found_roots = 0;   // Number of actual roots found.
    size_t d_found_unknown = 0; // Number of empty intervals (with potential root).
    size_t d_bisect_fail = 0;   // Number of bisection failures (debug variable).
    size_t d_newton_fail = 0;   // Number of Newton failures (debug variable).

    size_t d_P;                 // Period.
    arf_interval_ptr d_blocks;  // 1. Holds the root blocks.
    int *d_flags;               // 2. int array; one for each root.
    arb_calc_func_t d_func;     // 3. function to find root for.
    void *d_param;              // 4. Function parameter(s).
    double const d_a;           // 5. interval for searching the roots [a, b].
    double const d_b;

    public:
        // Constructor.
        RootFinder() = delete;
        RootFinder(size_t P, double a, double b);
        // Destructor.
        ~RootFinder();
        // Run root finding.
        void run();

    private:
        // Compute intervals.
        void compute_intervals();
        // Refine interval using bisection.
        void refine_bisect();
        // Find the actual root using Newton's method.
        void refine_newton();
        // Print the intervals (midpoints).
        void printintervals();
        // Provide summary.
        void summary();
        // Test function sin(x^2).
        static int sin_x2(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
        // My function for project Euler problem 729.
        static int myfunc(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
};

// Constructor.
inline RootFinder::RootFinder(size_t P, double a, double b)
:
    d_P(P),    
    // d_func(sin_x2),  // Test function sin(x^2).
    d_func(myfunc),     // Actualy function for Project Euler problem 729.
    d_param(&d_P),
    d_a(a),
    d_b(b)
{}

// Destructor.
inline RootFinder::~RootFinder()
{
    for (size_t idx = 0; idx != d_num; ++idx)
        arf_interval_clear(d_blocks + idx);

    flint_free(d_blocks);
    flint_free(d_flags);
    flint_cleanup();
}

// Run root finding.
inline void RootFinder::run()
{
    stopwatch::Stopwatch timer1, timer2, timer3;
    
    timer1.start(); this->compute_intervals(); timer1.stop();
    // this->printintervals(); // debug

    // timer2.start(); this->refine_bisect(); timer2.stop();
    // this->printintervals();
    
    // timer3.start(); this->refine_newton(); timer3.stop();

    this->summary();
    print(fs("Compute_intervals: {}", timer1));
    print(fs("Refine_bisect:     {}", timer2));
    print(fs("Refine_newton:     {}", timer3));
    print(fs("Total time:        {}", timer1 + timer2 + timer3));
}

// Compute intervals.
inline void RootFinder::compute_intervals()
{
    // Tunable parameters.
    size_t const maxdepth = 30;         // Max #recursive subdivisions attempted (20-100).
    size_t const maxeval = 1'000'000;   // Max #tested subintervals (10'000 - 1'000'000).
    size_t const maxfound = LONG_MAX;   // Max found number of roots.
    size_t const prec = 128;            // Precision used during evaluation (30-200 bits).
    size_t const subintervals = 1000;   // To tune multithreading.

    // Initialize blocks_vector, flags_vector, interval_vector, blocks vector.
    // These will function kind of like a starmap in Python multiprocessing.
    std::vector<arf_interval_ptr> blocks_vector(subintervals);
    std::vector<int*> flags_vector(subintervals);
    std::vector<arf_interval_struct> interval_vector;
    std::vector<size_t> block_counts(subintervals);

    // Set up the interval vector.
    for (size_t idx = 0; idx != subintervals; ++idx)
    {
        arf_interval_struct interval;
        arf_interval_init(&interval);

        double width = (d_b - d_a) / subintervals;
        double x = d_a + idx * width;
        double y = d_a + (idx + 1) * width;
        arf_set_d(&interval.a, x);
        arf_set_d(&interval.b, y);

        interval_vector.push_back(interval);
    }

    // Multithreaded execution of arb_calc_isolate_roots.
    #pragma omp parallel for schedule(dynamic)
    for (size_t idx = 0; idx != subintervals; ++idx)
    {
        block_counts[idx] = arb_calc_isolate_roots(&(blocks_vector[idx]), &(flags_vector[idx]), d_func, d_param, &interval_vector[idx], maxdepth, maxeval, maxfound, prec);;
    }

    // Reduce block_counts to d_num.
    d_num = sum(block_counts);

    // Reduce blocks_vector into d_blocks and flags_vector into d_flags.
    d_blocks = (arf_interval_ptr)flint_malloc(d_num * sizeof(arf_interval_struct));
    d_flags = (int*)flint_malloc(d_num * sizeof(int));

    size_t pos = 0;
    for (size_t idx = 0; idx != subintervals; ++idx)
    {
        for (size_t j = 0; j != block_counts[idx]; ++j)
        {
            arf_interval_init(d_blocks + pos); // Copy interval
            arf_interval_set(d_blocks + pos, blocks_vector[idx] + j);
            d_flags[pos] = flags_vector[idx][j]; // Copy flag
            ++pos;
        }
    }

    // Free objects in interval_vector.
    for (auto &interval : interval_vector)
        arf_interval_clear(&interval);

    // Count roots and unknowns as per usual.
    for (size_t idx = 0; idx != d_num; ++idx)
    {
        if (d_flags[idx] != 1)
            ++d_found_unknown;
        else
            ++d_found_roots;
    }
}

// Refine interval using bisection.
inline void RootFinder::refine_bisect()
{
    // Tunable parameters.
    size_t const iter = 10;   // Number of bisection steps per interval (5-100).
    size_t const prec = 64;   // Working precision for interval arithmetic (30-200 bits).

    for (size_t idx = 0; idx != d_num; ++idx)
    {
        if (d_flags[idx] == 1 && arb_calc_refine_root_bisect(d_blocks + idx, d_func, d_param, d_blocks + idx, iter, prec) != ARB_CALC_SUCCESS)
        {
            print(fs("WARNING: refine_bisect failed for root interval idx = {}", idx));
            ++d_bisect_fail;
        }
    }
}

inline void RootFinder::refine_newton()
{
    // Tunable parameters.
    size_t const eval_extra_prec = 5;   // Extra prec to use internally during calc.
    size_t const prec1 = 128;           // Precision used when converting (30-200 bits).
    size_t const prec2 = 200;           // Target Precision of after Newton (64-500 bits).

    arb_t root;
    arb_init(root);
    arf_t conv_factor;
    arf_init(conv_factor);

    size_t count = 1;
    for (size_t idx = 0; idx != d_num; ++idx)
    {
        if (d_flags[idx] == 1)
        {
            arf_interval_get_arb(root, d_blocks + idx, prec1); // Midpoint.
            arb_calc_newton_conv_factor(conv_factor, d_func, d_param, root, prec1);

            if (arb_calc_refine_root_newton(root, d_func, d_param, root, root, conv_factor, eval_extra_prec, prec2) != ARB_CALC_SUCCESS)
            {
                print(fs("WARNING: refine_newton failed for d_blocks[{}]", idx));
                ++d_newton_fail;
            }
            else
            {
                print(fs("{}. {}", count, arb_get_str(root, prec2, 0)));
                ++count;
            }
        }
    }
    arb_clear(root);
    arf_clear(conv_factor);
}

// Print the intervals (midpoints).
inline void RootFinder::printintervals()
{
    // Tunable parameters.
    size_t const digits = 10; // This is fine, don't change.
    
    size_t count = 1;
    arb_t d_temp;
    arb_init(d_temp);

    for (size_t idx = 0; idx != d_num; ++idx)
    {
        arf_interval_get_arb(d_temp, d_blocks + idx, digits);

        if (d_flags[idx] == 1) // Only print if we actually found a root in interval.
        {
            print(fs("{}. {}", count, arb_get_str(d_temp, digits, 0)));
            ++count;
        }
    }
    arb_clear(d_temp);
}

// Provide summary.
inline void RootFinder::summary()
{
    size_t const theoretical = pow(2, d_P) - 2;

    print("---------------------------------------------------------------");
    print(fs("Found roots: {} (should be {} for P = {})", 2 * d_found_roots, theoretical, d_P));
    print(fs("Subintervals possibly containing undetected roots: {}", d_found_unknown));
    print(fs("Bisection failures: {}/{}", d_bisect_fail, d_found_roots));
    print(fs("Newton failures: {}/{}", d_newton_fail, d_found_roots));
    print(fs("Function evaluations: {}", eval_count));
}

// Test function sin(x^2).
inline int RootFinder::sin_x2(arb_ptr out, arb_t const inp, void *param, slong order, slong prec)
{
    arb_ptr x;

    int xlen = FLINT_MIN(2, order);
    int ylen = FLINT_MIN(3, order);

    x = _arb_vec_init(xlen);

    arb_set(x, inp);
    if (xlen > 1)
        arb_one(x + 1);

    _arb_poly_mullow(out, x, xlen, x, xlen, ylen, prec);
    _arb_poly_sin_series(out, out, ylen, order, prec);

    _arb_vec_clear(x, xlen);

    ++eval_count;
    return 0;
}

// My function for project Euler problem 729.
inline int RootFinder::myfunc(arb_ptr out, const arb_t inp, void *param, slong order, slong prec)
{
    size_t const P = *static_cast<size_t*>(param);

    // Initialize x as the power series for the variable centered at inp
    arb_ptr x = _arb_vec_init(order);
    arb_set(x, inp);
    if (order > 1)
        arb_one(x + 1);
    for (slong i = 2; i < order; ++i)
        arb_zero(x + i);

    // Compose the map P times as a power series
    for (size_t i = 0; i < P; ++i)
    {
        arb_ptr invx = _arb_vec_init(order);
        _arb_poly_inv_series(invx, x, order, order, prec);

        arb_ptr next = _arb_vec_init(order);
        _arb_vec_sub(next, x, invx, order, prec);

        _arb_vec_clear(x, order);
        _arb_vec_clear(invx, order);

        x = next;
    }

    // Subtract the original power series (the variable) from the result
    arb_ptr var = _arb_vec_init(order);
    arb_set(var, inp);
    if (order > 1)
        arb_one(var + 1);
    for (slong i = 2; i < order; ++i)
        arb_zero(var + i);

    _arb_vec_sub(out, x, var, order, prec);

    _arb_vec_clear(x, order);
    _arb_vec_clear(var, order);

    ++eval_count;
    return 0;
}

int main()
{
    // RootFinder(3, 0.001, 7.0).run();
    // RootFinder(10, -4.1, 4.1).run(); // Project Euler
    RootFinder(15, 0, 5.05).run(); // Project Euler
    // RootFinder(20, 0, 6.0).run(); // Project Euler
}

// P = 3 (count = 6)
// -1.4619022001
// -0.7778619134
// -0.5077133059
//  0.5077133059
//  0.7778619134
//  1.4619022001

// P = 4 (count = 14)
// -1.9890437907
// -1.4862896510
// -1.3065629649
// -0.8134732862
// -0.7071067819
// -0.5411961001
// -0.4158233816
//  0.4158233816
//  0.5411961001
//  0.7071067819
//  0.8134732862
//  1.3065629649
//  1.4862896510
//  1.9890437907
