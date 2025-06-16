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

    arb_t d_temp;               // Temp variable used in printing function.

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
        // Provide summary.
        void summary();
        // Print the interval (midpoint).
        void printinterval(size_t idx);

    private:
        // Test function sin(x).
        static int sin_x(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
        // My function for project Euler problem 729.
        static int myfunc(arb_ptr out, arb_t const inp, void *param, slong order, slong prec);
};

// Constructor.
inline RootFinder::RootFinder(size_t P, double a, double b)
:
    d_func(myfunc),
    d_param(&P),
    d_maxdepth(20),
    d_maxeval(100000),
    d_maxfound(LONG_MAX),
    d_prec(30)
{
    arb_init(d_temp);
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
    arb_clear(d_temp);
    arf_interval_clear(d_interval);
    flint_cleanup();
}

// Run root finding.
inline void RootFinder::run()
{
    stopwatch::Stopwatch timer;
    timer.start();

    // Compute intervals (d_blocks, d_flags, d_num).
    d_num = arb_calc_isolate_roots(&d_blocks, &d_flags, d_func, d_param, d_interval, d_maxdepth, d_maxeval, d_maxfound, d_prec);

    // Loop through each interval.
    for (size_t idx = 0; idx != d_num; ++idx)
    {
        this->printinterval(idx);

        if (d_flags[idx] != 1)
        {
            ++d_found_unknown;
            continue;
        }

        ++d_found_roots;
    }

    this->summary();
    print(fs("\nrun() took {}", timer));
}

// Print the interval (midpoint).
void RootFinder::printinterval(size_t idx)
{
    arf_interval_get_arb(d_temp, d_blocks + idx, d_prec);
    if (d_flags[idx] == 1)
        print(fs("{}. {}", idx + 1, arb_get_str(d_temp, 10, 0)));
    else
        print(fs("{}. {} undetected", idx + 1, arb_get_str(d_temp, 10, 0)));
}

// Provide summary.
inline void RootFinder::summary()
{
    print("---------------------------------------------------------------");
    print(fs("Found roots: {}", d_found_roots));
    print(fs("Subintervals possibly containing undetected roots: {}", d_found_unknown));
    print(fs("Function evaluations: {}", eval_count));
}

// Test function sin(x).
inline int RootFinder::sin_x(arb_ptr out, const arb_t inp, void *param, slong order, slong prec)
{
    int xlen = FLINT_MIN(2, order);

    arb_set(out, inp);
    if (xlen > 1)
        arb_one(out + 1);

    _arb_poly_sin_series(out, out, xlen, order, prec);

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
    RootFinder(3, -3.0, 3.0).run();
}







// int main()
// {
//     // Set up all the parameters that go into arb_calc_isolate_roots.

//     slong d_P = 3          // Period P.
//     double d_a = 1.0,       // interval [a, b].
//     double d_b = 3.0;       // interval [b, b].
//     slong d_num;

//     arf_interval_ptr blocks;                // 1. Holds the root blocks.
//     int *flags;                             // 2. int array; one for each root.
//     arb_calc_func_t function = sin_x;       // 3. Function to find root for.
//     void *param = &P;                       // 4. Function parameter(s).
    
//     arf_interval_t interval;                // 5. interval for searching the roots.
//     arf_interval_init(interval);
//     arf_set_d(&interval->a, a);
//     arf_set_d(&interval->b, b);

//     // 6. Max number of recursive subdivisions to be attempted. 
//     // Smallest details that can be distinguished are ~2^-maxdepth.
//     // A typical, reasonable value might be between 20 and 50.
//     slong maxdepth = 20;

//     // 7. Total number of tested subintervals before algorithm is terminated.
//     // A typical, reasonable value might be between 100 and 100000.
//     slong maxeval = 10000;

//     // 8. The algorithm terminates if maxfound roots have been isolated.
//     // To try to find all roots, LONG_MAX may be passed.
//     slong maxfound = LONG_MAX;

//     // 9. The argument prec denotes the precision used to evaluate the function.
//     // Note that it probably does not make sense for maxdepth to exceed prec.
//     slong prec = 30;

//     // Main algorithm. Returns number of roots found.
//     slong num = arb_calc_isolate_roots(&blocks, &flags, function, param, interval, maxdepth, maxeval, maxfound, prec);

//     // Analyze by looping through the roots.
//     slong found_roots = 0;
//     slong found_unknown = 0;
//     slong digits = 6;
    
//     arb_t approx;       // Declare and initialize an arb variable 
//     arb_init(approx);   // for holding the approximate root.

//     for (slong idx = 0; idx != num; ++idx)
//     {
//         if (flags[idx] == 1) // Correctly found a root.
//         {
//             ++found_roots;

//             // Print the midpoint of the interval as an approximate root.
//             arf_interval_get_arb(approx, blocks + idx, prec);
//             flint_printf("approx root (%wd/%wd):\n", idx, num);
//             arb_printn(approx, digits + 2, 0);
//             double mid = arf_get_d(arb_midref(approx), ARF_RND_NEAR);
//             printf(", midpoint as double: %.10f\n", mid);
//             flint_printf("\n\n");

//             // Refine the interval to high precision
//             arf_interval_t refined;
//             arf_interval_init(refined);

//             slong high_prec = 200; // or whatever precision you want
//             if (arb_calc_refine_root_bisect(refined, function, param, blocks + idx, 10, high_prec) == ARB_CALC_SUCCESS)
//             {
//                 arb_t root;
//                 arb_init(root);
//                 arf_interval_get_arb(root, refined, high_prec); // Get midpoint as high-precision root
//                 flint_printf("high-precision root (%wd/%wd):\n", idx, num);
//                 arb_printn(root, 50, 0); // Print with 50 digits
//                 double mid = arf_get_d(arb_midref(root), ARF_RND_NEAR);
//                 printf(", midpoint as double: %.10f\n", mid);
//                 flint_printf("\n\n");
//                 arb_clear(root);
//             }
//             else
//             {
//                 std::cout << 
//             }

//             arf_interval_clear(refined);
//         }
//         else
//             ++found_unknown;
//     }

//     // Summary.
//     flint_printf("---------------------------------------------------------------\n");
//     flint_printf("Found roots: %wd\n", found_roots);
//     flint_printf("Subintervals possibly containing undetected roots: %wd\n", found_unknown);
//     flint_printf("Function evaluations: %wd\n", eval_count);

//     // Cleanup.
//     for (slong idx = 0; idx != num; ++idx)
//         arf_interval_clear(blocks + idx);

//     flint_free(blocks);
//     flint_free(flags);
//     arf_interval_clear(interval);
//     arb_clear(approx);
//     flint_cleanup();
// }
