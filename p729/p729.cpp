#include <flint/arb_poly.h>
#include <flint/arb_calc.h>
#include "cpplib/pythonlike.h"
#include "cpplib/stopwatch.h"

using namespace pythonlike;

static size_t eval_count = 0;  // Tracks how often the function was called/evaluated.

class RootFinder
{
    size_t d_num = 0;
    size_t d_found_roots = 0;
    size_t d_found_unknown = 0;

    arf_interval_ptr d_blocks;  // 1. Holds the root blocks.
    int *d_flags;               // 2. int array; one for each root.
    arb_calc_func_t d_func;     // 3. function to find root for.
    void *d_param;              // 4. Function parameter(s).
    arf_interval_t d_interval;  // 5. interval for searching the roots.
    size_t d_maxdepth;          // 6. Max #recursive subdivisions attempted.
    size_t d_maxeval;           // 7. Max #tested subintervals.
    size_t d_maxfound;          // 8. Max found number of roots.
    size_t d_prec;              // 9. Precision used for evaluation.

    public:
        // Constructor.
        RootFinder() = delete;
        RootFinder(size_t P, double a, double b);
        // Destructor.
        ~RootFinder();
        // Run root finding.
        void run();
        // Compute intervals.
        void compute_intervals();
        // Refine interval using bisection.
        void refine_bisect();
        // Print the intervals (midpoints).
        void printintervals();
        // Provide summary.
        void summary();

    private:
        // Test function sin(x^2).
        static int sin_x2(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
        // My function for project Euler problem 729.
        static int myfunc(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
};

// Constructor.
inline RootFinder::RootFinder(size_t P, double a, double b)
:
    d_func(sin_x2),
    d_param(&P),
    d_maxdepth(20),
    d_maxeval(100000),
    d_maxfound(LONG_MAX),
    d_prec(30)
{
    arf_interval_init(d_interval);
    arf_set_d(&d_interval->a, a);
    arf_set_d(&d_interval->b, b);
}

// Destructor.
inline RootFinder::~RootFinder()
{
    for (size_t idx = 0; idx != d_num; ++idx)
        arf_interval_clear(d_blocks + idx);

    flint_free(d_blocks);
    flint_free(d_flags);
    arf_interval_clear(d_interval);
    flint_cleanup();
}

// Run root finding.
inline void RootFinder::run()
{
    stopwatch::Stopwatch timer;
    timer.start();

    this->compute_intervals();
    // this->printintervals();
    this->refine_bisect();
    this->printintervals();

    this->summary();
    print(fs("\nRootFinder took {}", timer));
}

// Compute intervals.
inline void RootFinder::compute_intervals()
{
    d_num = arb_calc_isolate_roots(&d_blocks, &d_flags, d_func, d_param, d_interval, d_maxdepth, d_maxeval, d_maxfound, d_prec);
    
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
    size_t const iter = 10;
     for (size_t idx = 0; idx != d_num; ++idx)
        if (arb_calc_refine_root_bisect(d_blocks + idx, d_func, d_param, d_blocks + idx, iter, d_prec) != ARB_CALC_SUCCESS)
            print(fs("WARNING: refine_bisect failed for root interval #{}", idx + 1));
}

// Print the intervals (midpoints).
inline void RootFinder::printintervals()
{
    size_t const digits = 10;
    
    arb_init(d_temp);

    for (size_t idx = 0; idx != d_num; ++idx)
    {
        arf_interval_get_arb(d_temp, d_blocks + idx, digits);

        if (d_flags[idx] == 1)
            print(fs("{}. {}", idx + 1, arb_get_str(d_temp, digits, 0)));
        else
            print(fs("{}. {} undetected", idx + 1, arb_get_str(d_temp, digits, 0)));
    }

    arb_clear(d_temp);
}

// inline void RootFinder::refine_bisect()
// {
    // Refines root interval entry idx in d_blocks array using bisection.
    // size_t const iter = 10;
    // arb_calc_refine_root_bisect(d_blocks + idx, myfunc, d_param, d_blocks + idx, iter, d_prec);

    // // Refines root interval entry idx in d_block array using Newton's method.
    // arb_t root;
    // arb_init(root);
    // arf_interval_get_arb(root, d_blocks + idx, d_prec); // Root now holds starting midpoint.

    // arf_t conv_factor;
    // arf_init(conv_factor);
    // arb_calc_newton_conv_factor(conv_factor, myfunc, d_param, root, d_prec); // Conv factor now holds conversion factor.

    // if (arb_calc_refine_root_newton(root, myfunc, d_param, root, root, conv_factor, 10, d_prec) == ARB_CALC_SUCCESS)
    // {
    //     print("Newton's method ran succesfully");
    //     print(arb_get_str(root, 50, 0));
    // }

    // arb_clear(root);
    // arf_clear(conv_factor);
// }

// Provide summary.
inline void RootFinder::summary()
{
    print("---------------------------------------------------------------");
    print(fs("Found roots: {}", d_found_roots));
    print(fs("Subintervals possibly containing undetected roots: {}", d_found_unknown));
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
    size_t const P = *static_cast<size_t*>(param); // This works correctly.

    arb_t x, invx;
    arb_init(x);
    arb_init(invx);

    arb_set(x, inp);

    for (size_t i = 0; i != P - 1; ++i)
    {
        arb_inv(invx, x, prec);    // invx = 1/x
        arb_sub(x, x, invx, prec); // x = x - 1/x
    }

    // out = x - inp
    arb_sub(out, x, inp, prec);

    arb_clear(x);
    arb_clear(invx);

    ++eval_count;
    return 0;
}

int main()
{
    RootFinder(3, 0.001, 7.0).run();
}
