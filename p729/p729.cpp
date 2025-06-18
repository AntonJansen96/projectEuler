#include <atomic>
#include <iomanip>
#include <omp.h>
#include <flint/arb_poly.h>
#include <flint/arb_calc.h>
#include <cpplib/pythonlike.h>
#include <cpplib/stopwatch.h>

using namespace pythonlike;

static size_t eval_count = 0;  // Tracks how often the function was called/evaluated.

struct RootFinderResult
{
    size_t num;
    size_t found_roots;
    arf_interval_ptr blocks;
    int *flags;
};

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
        RootFinderResult run();

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
    d_func(myfunc),     // Actual function for Project Euler problem 729.
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
inline RootFinderResult RootFinder::run()
{
    this->compute_intervals(); 
    this->refine_bisect();

    return RootFinderResult{d_num, d_found_roots, d_blocks, d_flags};
}

// Compute intervals.
inline void RootFinder::compute_intervals()
{
    // Tunable parameters.
    // Together with intervals = 50000, these parameters I have checked to 
    // provide all roots for P = 25 (and therefore any P < 25). DO NOT MODIFY.
    size_t const maxdepth = 30;         // Max #recursive subdivisions attempted (20-100).
    size_t const maxeval = 1'000'000;   // Max #tested subintervals (10'000 - 1'000'000).
    size_t const maxfound = LONG_MAX;   // Max found number of roots.
    size_t const prec = 128;            // Precision used during evaluation (30-200 bits).

    arf_interval_t interval;
    arf_interval_init(interval);
    arf_set_d(&interval->a, d_a);
    arf_set_d(&interval->b, d_b);

    d_num = arb_calc_isolate_roots(&d_blocks, &d_flags, d_func, d_param, interval, maxdepth, maxeval, maxfound, prec);

    for (size_t idx = 0; idx != d_num; ++idx)
    {
        if (d_flags[idx] != 1)
            ++d_found_unknown;
        else
            ++d_found_roots;
    }

    arf_interval_clear(interval);
}

// Refine interval using bisection.
inline void RootFinder::refine_bisect()
{
    // Tunable parameters.
    size_t const iter = 75;   // Number of bisection steps per interval (5-100).
    size_t const prec = 128;  // Working precision for interval arithmetic (30-200 bits).

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

// Handles calculation of the orbit ranges and orbit multiplicity correction.
class Orbitrange
{
    arb_t root, max, min, inv_root;
    size_t const d_prec = 128;

    public:
        Orbitrange()
        {
            arb_init(root);
            arb_init(max);
            arb_init(min);
            arb_init(inv_root);
        }

        ~Orbitrange()
        {
            arb_clear(root);
            arb_clear(max);
            arb_clear(min);
            arb_clear(inv_root);
        }

        // Calculate the orbit range for given root and periodicity P.
        // Out is set to the output (the range), for given root and period P.
        void range(arb_t out, arb_t root_in, size_t P)
        {
            arb_set(root, root_in);     // Making a copy here to be safe.
            arb_set(max, root_in);
            arb_set(min, root_in);

            for (size_t idx = 0; idx != P; ++idx)
            {
                if (arb_gt(root, max))                   // if root > max
                    arb_set(max, root);
                else if (arb_lt(root, min))              // if root < min
                    arb_set(min, root);

                arb_inv(inv_root, root, d_prec);         // inv_root = 1/root
                arb_sub(root, root, inv_root, d_prec);   // root = root - 1/root
            }

            arb_sub(out, max, min, d_prec);
        }

        // Calculate the orbit range for given root and periodicity P.
        // This is just a test function that works with doubles.
        double test_range(double root, size_t P)
        {
            double max = root;
            double min = root;
            for (size_t idx = 0; idx != P; ++idx)
            {
                if (root > max)
                    max = root;
                else if (root < min)
                    min = root;
                root -= 1 / root;
            }
            return max - min;
        }

        // Corrects the Sarray for orbit multiplicity (in-place).
        void correct(std::vector<arb_t> &Sarray)
        {
            for (size_t ii = 2; ii != Sarray.size(); ++ii)
                for (size_t div : this->divisors(ii))
                    arb_sub(Sarray[ii], Sarray[ii], Sarray[div], d_prec);
        }

        // Corrects the Sarray for orbit multiplicity (in-place).
        // This is just a test function that works with std::vector<double>.
        void test_correct(std::vector<double> &Sarray)
        {
            for (size_t ii = 2; ii != Sarray.size(); ++ii)
                for (size_t div : this->divisors(ii))
                    Sarray[ii] -= Sarray[div];
        }

        // Run example code of how we can compute an Sarray from the roots.
        // Also performs the multiplicity correction.
        void run_test_code()
        {
            std::vector<double> const root2 = {0.7071067812};
            std::vector<double> const root3 = {0.5077133059, 0.7778619134, 1.4619022001};
            std::vector<double> const root4 = {0.4158233816, 0.5411961001, 0.7071067812, 0.8134732862, 1.3065629649, 1.4862896510, 1.9890437907};
            std::vector<double> const root5 = {0.3602664845, 0.4363958122, 0.5165981962, 0.5561971984, 0.6851062005, 0.7144911876, 0.7745215176, 0.8359612342, 1.2417262771, 1.3160479384, 1.4191422057, 1.5018199946, 1.8551018882, 2.0014562076, 2.4154566070};

            std::vector<double> Sarray(5 + 1);

            for (double root : root2)
                Sarray[2] += this->test_range(root, 2) + this->test_range(-root, 2);

            for (double root : root3)
                Sarray[3] += this->test_range(root, 3) + this->test_range(-root, 3);

            for (double root : root4)
                Sarray[4] += this->test_range(root, 4) + this->test_range(-root, 4);

            for (double root : root5)
                Sarray[5] += this->test_range(root, 5) + this->test_range(-root, 5);

            print(Sarray);
            std::cout << "Naive sum: " << std::fixed << std::setprecision(4) << sum(Sarray) << std::endl;

            // Helper/debug code to set Sarray to https://oeis.org/A000918.
            // for (size_t idx = 2; idx != 25 + 1; ++idx)
                // Sarray[idx] = pow(2, idx) - 2;

            // Running this confirms code below gives https://oeis.org/A056267.
            this->test_correct(Sarray);

            print(Sarray);
            std::cout << "Corrected sum: " << std::fixed << std::setprecision(4) << sum(Sarray) << std::endl;
        }

    private:
        // Non-trivial divisors of num.
        // Naive implementation but only required up to num = 25 so fine here.
        std::vector<size_t> divisors(size_t num)
        {
            std::vector<size_t> divisors;
            for (size_t div = 2; div != num; ++div)
                if (num % div == 0)
                    divisors.push_back(div);
            return divisors;
        }
};

// int main() // debug Newton.
// {
//     RootFinder(10, 0, 6.75).run();
// }

int main()
{   
    omp_set_num_threads(4);             // Number of threads to use.
    size_t const Pmax = 5;              // Compute S(Pmax).

    // These parameters for b and intervals find all roots for P <= 25 (checked).

    double const b = 6.75;               // interval limit [0, b].
    size_t const intervals = 50000;      // Number of subintervals to multithread.

    size_t theoretical = 0;              // Theoretical total #roots up to Pmax.
    for (size_t n = 2; n <= Pmax; ++n)   // This sum(https://oeis.org/A000918).
        theoretical += pow(2, n) - 2;    // This is 67108812 for P = 25.

    // Class that handles progress tracking.
    stopwatch::ProgressReport report(theoretical);  

    // Class that handles calculation of orbit ranges and multiplicity correction.
    Orbitrange orbit;                    
    
    // Declare and initialze Sarray vector containing arb_t objects.
    std::vector<arb_t> Sarray(Pmax + 1);  
    for (auto &obj : Sarray)            
    {
        arb_init(obj);                  // Initialize arb_t obj in Sarray.
        arb_zero(obj);                  // Set value to 0.
    }

    arb_t root, range1, range2;         // Store intermediate values.
    arb_init(root);
    arb_init(range1);
    arb_init(range2);
    
    for (size_t P = 2; P <= Pmax; ++P)  // Main loop starts here.
    {
        // Total number of roots found for given P. Should correspond to A000918.
        std::atomic<size_t> total_found_roots{0};

        // Multithreaded loop over the subdivided interval.
        #pragma omp parallel for schedule(dynamic)
        for (size_t idx = 0; idx != intervals; ++idx)
        {
            double const width = b / intervals;     // Compute x and y
            double const x = idx * width;           // for this specific
            double const y = (idx + 1) * width;     // interval.

            RootFinder calc(P, x, y);
            RootFinderResult const result = calc.run();

            // Loop through all the intervals...
            for (size_t ii = 0; ii != result.num; ++ii)
            {   // Only consider intervals with a root...
                if (result.flags[ii] == 1) 
                {   // Convert from arf_interval to arb_t.
                    arf_interval_get_arb(root, result.blocks + ii, 128);
                    orbit.range(range1, root, P);  // range from positive root
                    arb_neg(root, root);           // swap root sign
                    orbit.range(range2, root, P);  // range from negative root

                    arb_add(Sarray[P], Sarray[P], range1, 128);
                    arb_add(Sarray[P], Sarray[P], range2, 128);
                }
            }
            total_found_roots += result.found_roots;
            report.tick(2 * result.found_roots); // 2x since interval [0, b].
        }

        // Allow progress thread to catch up for nicer output formatting.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // User update.
        size_t const theoretical_P = pow(2, P) - 2;
        double const ratio = 200 * total_found_roots / static_cast<double>(theoretical_P);
        print(fs("P = {} | Found roots: {}/{} ({}%)", P, 2 * total_found_roots, theoretical_P, ratio));
    }

    // Finish the progress report.
    report.join();

    // Perform the correction for the orbit multiplicity.
    orbit.correct(Sarray);

    // Print Sarray and compute the sum.
    arb_t total;
    arb_init(total);
    arb_zero(total);
    print("\nSarray:");
    for (size_t idx = 0; idx != Sarray.size(); ++idx)
    {
        print(idx, arb_get_str(Sarray[idx], 128, 0));
        arb_add(total, total, Sarray[idx], 128);
    }

    // Print final answer.
    print(fs("sum: {}", arb_get_str(total, 128, 0)));

    // Clear and free memory.
    arb_clear(root);                    
    arb_clear(range1);
    arb_clear(range2);
    arb_clear(total);

    for (arb_t &obj : Sarray)
        arb_clear(obj);
}

// root interval finding only (8 threads) ~ 40min.
// root interval finding + bisection[10 iter, 128 bits] (4 threads) ~ 51min.
// root interval finding + bisection[75 iter, 128 bits] (4 threads) ~ 51min.
