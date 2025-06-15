#include <flint/arb_poly.h>
#include <flint/arb_calc.h>


slong eval_count = 0; // Tracks how often the function was called/evaluated.


int sin_x(arb_ptr out, const arb_t inp, void * params, slong order, slong prec)
{
    int xlen = FLINT_MIN(2, order);

    arb_set(out, inp);
    if (xlen > 1)
        arb_one(out + 1);

    _arb_poly_sin_series(out, out, xlen, order, prec);

    eval_count++;
    return 0;
}

// Our function that we want to find the roots of.
int myfunc(arb_ptr out, const arb_t inp, void *param, slong order, slong prec)
{
    slong P = 3; // Hardcoded for now.

    arb_t x, invx;
    arb_init(x);
    arb_init(invx);

    arb_set(x, inp);

    for (slong i = 0; i != P - 1; ++i)
    {
        arb_inv(invx, x, prec);    // invx = 1/x
        arb_sub(x, x, invx, prec); // x = x - 1/x
    }

    // out = x - inp
    arb_sub(out, x, inp, prec);

    arb_clear(x);
    arb_clear(invx);

    eval_count++;
    return 0;
}

int main()
{
    slong P = 3;                            // Period P.
    double const a = 1.0;                   // interval [a, b].
    double const b = 4.0;                   // interval [b, b].

    // Set up all the parameters that go into arb_calc_isolate_roots.

    arf_interval_ptr blocks;                // 1. Holds the root interval blocks.
    int *flags;                             // 2. int array; one for each root.
    arb_calc_func_t function = sin_x;       // 3. Function to find root for.
    void *param = &P;                       // 4. Function parameter(s).
    
    arf_interval_t interval;                // 5. interval for searching the roots.
    arf_interval_init(interval);
    arf_set_d(&interval->a, a);
    arf_set_d(&interval->b, b);

    // 6. Max number of recursive subdivisions to be attempted. 
    // Smallest details that can be distinguished are ~2^-maxdepth.
    // A typical, reasonable value might be between 20 and 50.
    slong maxdepth = 20;

    // 7. Total number of tested subintervals before algorithm is terminated.
    // A typical, reasonable value might be between 100 and 100000.
    slong maxeval = 10000;

    // 8. The algorithm terminates if maxfound roots have been isolated.
    // To try to find all roots, LONG_MAX may be passed.
    slong maxfound = LONG_MAX;

    // 9. The argument prec denotes the precision used to evaluate the function.
    // Note that it probably does not make sense for maxdepth to exceed prec.
    slong prec = 30;

    // Main algorithm. Returns number of roots found.
    slong num = arb_calc_isolate_roots(&blocks, &flags, function, param, interval, maxdepth, maxeval, maxfound, prec);

    // Analyze by looping through the roots.
    slong found_roots = 0;
    slong found_unknown = 0;
    slong digits = 6;
    
    arb_t approx;       // Declare and initialize an arb variable 
    arb_init(approx);   // for holding the approximate root.

    for (slong idx = 0; idx != num; ++idx)
    {
        if (flags[idx] == 1) // Correctly found a root.
        {
            ++found_roots;

            // Print the midpoint of the interval as an approximate root.
            arf_interval_get_arb(approx, blocks + idx, prec);
            flint_printf("approx root (%wd/%wd):\n", idx, num);
            arb_printn(approx, digits + 2, 0);
            double mid = arf_get_d(arb_midref(approx), ARF_RND_NEAR);
            printf(", midpoint as double: %.10f\n", mid);
            flint_printf("\n\n");

        }
        else
            ++found_unknown;
    }

    // Summary.
    flint_printf("---------------------------------------------------------------\n");
    flint_printf("Found roots: %wd\n", found_roots);
    flint_printf("Subintervals possibly containing undetected roots: %wd\n", found_unknown);
    flint_printf("Function evaluations: %wd\n", eval_count);

    // Cleanup.
    for (slong idx = 0; idx != num; ++idx)
        arf_interval_clear(blocks + idx);

    flint_free(blocks);
    flint_free(flags);
    arf_interval_clear(interval);
    arb_clear(approx);
    flint_cleanup();
}
