#include <atomic>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>
#include <flint/arb_poly.h>
#include <flint/arb_calc.h>
#include <cpplib/stopwatch.h> // Can safely comment out if you don't have this.

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
    size_t d_found_unknown = 0; // Number of empty intervals (debug variable).
    size_t d_bisect_fail = 0;   // Number of bisection failures (debug variable).

    size_t d_P;                 // Period.
    arf_interval_ptr d_blocks;  // 1. Holds the root blocks.
    int *d_flags;               // 2. int array; one for each root.
    arb_calc_func_t d_func;     // 3. function to find root for.
    void *d_param;              // 4. Function parameter(s).
    arf_interval_t interval;    // 5. interval for searching the roots.

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
        // Function for project Euler problem 729.
        static int func(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
};

// Constructor.
inline RootFinder::RootFinder(size_t P, double a, double b)
:
    d_P(P),
    d_func(func),
    d_param(&d_P)
{
    arf_interval_init(interval);
    arf_set_d(&interval->a, a);
    arf_set_d(&interval->b, b);
}

// Destructor.
inline RootFinder::~RootFinder()
{
    for (size_t idx = 0; idx != d_num; ++idx)
        arf_interval_clear(d_blocks + idx);

    flint_free(d_blocks);
    flint_free(d_flags);
    arf_interval_clear(interval);
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
    // Together with intervals = 50000, these parameters I have checked to
    // provide all roots for P = 25 (and therefore any P < 25). DO NOT MODIFY.
    size_t const maxdepth = 30;         // Max #recursive subdivisions attempted (20-100).
    size_t const maxeval = 1'000'000;   // Max #tested subintervals (10'000 - 1'000'000).
    size_t const maxfound = LONG_MAX;   // Max found number of roots.
    size_t const prec = 128;            // Precision used during evaluation (30-200 bits).

    d_num = arb_calc_isolate_roots(&d_blocks, &d_flags, d_func, d_param, interval, maxdepth, maxeval, maxfound, prec);

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
    size_t const iter = 75;   // Number of bisection steps per interval (5-100).
    size_t const prec = 200;  // Working precision for interval arithmetic (30-200 bits).

    for (size_t idx = 0; idx != d_num; ++idx)
    {
        if (d_flags[idx] == 1 && arb_calc_refine_root_bisect(d_blocks + idx, d_func, d_param, d_blocks + idx, iter, prec) != ARB_CALC_SUCCESS)
        {
            std::cout << "WARNING: refine_bisect failed" << std::endl;
            ++d_bisect_fail;
        }
    }
}

// Function for project Euler problem 729.
inline int RootFinder::func(arb_ptr out, const arb_t inp, void* param, slong order, slong prec)
{
    size_t const P = *static_cast<size_t*>(param);

    if (order == 1)
    {
        arb_t x, invx;
        arb_init(x);
        arb_init(invx);
        arb_set(x, inp);

        for (size_t i = 0; i != P; ++i)
        {
            arb_inv(invx, x, prec);
            arb_sub(x, x, invx, prec);
        }

        arb_sub(out, x, inp, prec);
        arb_clear(x);
        arb_clear(invx);
        return 0;
    }

    arb_ptr x = _arb_vec_init(order);
    arb_ptr tmp = _arb_vec_init(order);

    arb_set(x, inp);
    if (order > 1)
        arb_one(x + 1);
    if (order > 2)
        _arb_vec_zero(x + 2, order - 2);

    for (size_t i = 0; i < P; ++i)
    {
        _arb_poly_inv_series(tmp, x, order, order, prec);
        _arb_vec_sub(tmp, x, tmp, order, prec);
        std::swap(x, tmp);
    }

    arb_set(tmp, inp);
    if (order > 1)
        arb_one(tmp + 1);
    if (order > 2)
        _arb_vec_zero(tmp + 2, order - 2);

    _arb_vec_sub(out, x, tmp, order, prec);

    _arb_vec_clear(x, order);
    _arb_vec_clear(tmp, order);
    return 0;
}

// Handles calculation of the orbit ranges and orbit multiplicity correction.
// Note: not thread safe! Instantiate within pragma loop, not outside!
class Orbitrange
{
    arb_t root, max, min, inv_root;
    size_t const d_prec = 200;

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

        // Corrects the Sarray for orbit multiplicity (in-place).
        void correct(std::vector<arb_t> &Sarray)
        {
            for (size_t ii = 2; ii != Sarray.size(); ++ii)
                for (size_t div : this->divisors(ii))
                    arb_sub(Sarray[ii], Sarray[ii], Sarray[div], d_prec);
        }

    private:
        // Non-trivial divisors of num. Naive implementation fine for 25 <=.
        std::vector<size_t> divisors(size_t num)
        {
            std::vector<size_t> divisors;
            for (size_t div = 2; div != num; ++div)
                if (num % div == 0)
                    divisors.push_back(div);
            return divisors;
        }
};

int main()
{
    omp_set_num_threads(4);              // Number of threads to use.
    size_t const Pmax = 25;              // Compute S(Pmax).

    // These parameters for b and intervals find all roots for P <= 25 (checked).
    double const b = 6.75;               // interval limit [0, b].
    size_t const intervals = 50000;      // Number of subintervals to multithread.

    size_t theoretical = 0;              // Theoretical total #roots up to Pmax.
    for (size_t n = 2; n <= Pmax; ++n)   // This sum(https://oeis.org/A000918).
        theoretical += pow(2, n) - 2;    // This is 67108812 for P = 25.

    // Class that handles progress tracking.
    #ifdef CPPLIB_STOPWATCH_H
    stopwatch::ProgressReport report(theoretical);
    #endif

    // Declare and initialze Sarray vector containing arb_t objects.
    std::vector<arb_t> Sarray(Pmax + 1);
    for (auto &obj : Sarray)
    {
        arb_init(obj);                   // Initialize arb_t obj in Sarray.
        arb_zero(obj);                   // Set value to 0.
    }

    for (size_t P = 2; P <= Pmax; ++P)
    {
        // Total number of roots found for given P. Should correspond to A000918.
        std::atomic<size_t> total_found_roots{0};

        #pragma omp parallel
        {
            arb_t local_sum;        // Per-thread local accumulators.
            arb_init(local_sum);
            arb_zero(local_sum);

            #pragma omp for schedule(dynamic)
            for (size_t idx = 0; idx != intervals; ++idx)
            {
                // Class that handles calculation of orbit ranges and multiplicity correction.
                Orbitrange orbit;

                arb_t root, range1, range2;          // Store intermediate values.
                arb_init(root);
                arb_init(range1);
                arb_init(range2);

                double const width = b / intervals;  // Compute x and y for this
                double const x = idx * width;        // specific interval.
                double const y = (idx + 1) * width;

                RootFinder calc(P, x, y);
                RootFinderResult const result = calc.run();

                // Loop through all the intervals...
                for (size_t ii = 0; ii != result.num; ++ii)
                {   // Only consider intervals with a root...
                    if (result.flags[ii] == 1)
                    {   // Convert from arf_interval to arb_t.
                        arf_interval_get_arb(root, result.blocks + ii, 200);
                        orbit.range(range1, root, P);  // range from positive root
                        arb_neg(root, root);           // swap root sign
                        orbit.range(range2, root, P);  // range from negative root

                        arb_add(local_sum, local_sum, range1, 200);
                        arb_add(local_sum, local_sum, range2, 200);
                    }
                }

                total_found_roots += result.found_roots;
                #ifdef CPPLIB_STOPWATCH_H
                report.tick(2 * result.found_roots); // 2x since interval [0, b].
                #endif

                arb_clear(root);
                arb_clear(range1);
                arb_clear(range2);
            }

            #pragma omp critical
            {
                arb_add(Sarray[P], Sarray[P], local_sum, 200);
            }
            arb_clear(local_sum);
        }

        #ifdef CPPLIB_STOPWATCH_H
        stopwatch::sleep(0.1); // Allow progthread to catch up for better formatting.
        #endif

        // User update.
        size_t const theoretical_P = pow(2, P) - 2;
        double const ratio = 200 * total_found_roots / static_cast<double>(theoretical_P);
        std::cout << "P = " << P << " | Found roots: " << 2 * total_found_roots 
                  << "/" << theoretical_P << " (" << ratio << "%)" << std::endl;
    }

    #ifdef CPPLIB_STOPWATCH_H
    report.join();                  // Finish the progress report.
    #endif

    Orbitrange orbit;               // Perform the correction for
    orbit.correct(Sarray);          // the orbit multiplicity.

    arb_t total;                    // Print Sarray and compute the sum.
    arb_init(total);
    arb_zero(total);
    std::cout << "\nSarray:" << std::endl;
    for (size_t idx = 0; idx != Sarray.size(); ++idx)
    {
        std::cout << idx << ' ' << arb_get_str(Sarray[idx], 200, 0) << std::endl;
        arb_add(total, total, Sarray[idx], 200);
    }

    std::cout << "sum: " << arb_get_str(total, 200, 0) << std::endl;

    arb_clear(total);               // Clear and free memory.
    for (arb_t &obj : Sarray)
        arb_clear(obj);
}
