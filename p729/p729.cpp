#include <flint/arb_poly.h>
#include <flint/arb_calc.h>

slong eval_count = 0;

int sin_x(arb_ptr out, const arb_t inp, void *params, slong order, slong prec)
{
    int xlen = FLINT_MIN(2, order);

    arb_set(out, inp);
    if (xlen > 1)
        arb_one(out + 1);

    _arb_poly_sin_series(out, out, xlen, order, prec);

    eval_count++;
    return 0;
}

int sin_x2(arb_ptr out, const arb_t inp, void *params, slong order, slong prec)
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

    eval_count++;
    return 0;
}

int sin_1x(arb_ptr out, const arb_t inp, void *params, slong order, slong prec)
{
    arb_ptr x;
    int xlen = FLINT_MIN(2, order);

    x = _arb_vec_init(xlen);

    arb_set(x, inp);
    if (xlen > 1)
        arb_one(x + 1);

    _arb_poly_inv_series(out, x, xlen, order, prec);
    _arb_poly_sin_series(out, out, order, order, prec);

    _arb_vec_clear(x, xlen);

    eval_count++;
    return 0;
}

int main()
{
    arf_interval_ptr blocks;
    int *info;

    int param1 = 0;
    void *params = &param1;

    arb_calc_func_t function = sin_x2;      // function to find root for.
    double a = 0;                           // interval [a, b]
    double b = 10;                          // interval [b, b]

    // int refine = 0;
    slong digits = 0;
    slong maxdepth = 30;
    slong maxeval = 100000;
    slong maxfound = 100000;

    slong low_prec = 30;
    // slong high_prec = digits * 3.32192809488736 + 10;

    slong found_roots = 0;
    slong found_unknown = 0;

    arf_t C;
    arf_init(C);
    arf_interval_t t;
    arf_interval_init(t);    
    arf_interval_t interval;
    arf_interval_init(interval);
    arb_t v;
    arb_init(v);
    arb_t w;
    arb_init(w);
    arb_t z;
    arb_init(z);
    arf_set_d(&interval->a, a);
    arf_set_d(&interval->b, b);

    flint_printf("interval: "); arf_interval_printd(interval, 15); flint_printf("\n");
    flint_printf("maxdepth = %wd, maxeval = %wd, maxfound = %wd, low_prec = %wd\n", maxdepth, maxeval, maxfound, low_prec);

    slong num = arb_calc_isolate_roots(&blocks, &info, function, params, interval, maxdepth, maxeval, maxfound, low_prec);

    for (slong i = 0; i != num; ++i)
    {
        if (info[i] != 1)
        {
            found_unknown++;
            continue;
        }

        found_roots++;

        // Print the midpoint of the interval as an approximate root
        arb_t approx;
        arb_init(approx);
        arf_interval_get_arb(approx, blocks + i, low_prec);
        flint_printf("approx root (%wd/%wd):\n", i, num);
        arb_printn(approx, digits + 2, 0);
        flint_printf("\n\n");
        arb_clear(approx);

        // if (refine)
        // {
        //     if (arb_calc_refine_root_bisect(t, function, params, blocks + i, 5, low_prec) != ARB_CALC_SUCCESS)
        //     {
        //         flint_printf("warning: some bisection steps failed!\n");
        //     }

        //     if (arb_calc_refine_root_bisect(blocks + i, function, params, t, 5, low_prec) != ARB_CALC_SUCCESS)
        //     {
        //         flint_printf("warning: some bisection steps failed!\n");
        //     }

        //     arf_interval_get_arb(v, t, high_prec);
        //     arb_calc_newton_conv_factor(C, function, params, v, low_prec);

        //     arf_interval_get_arb(w, blocks + i, high_prec);

        //     if (arb_calc_refine_root_newton(z, function, params, w, v, C, 10, high_prec) != ARB_CALC_SUCCESS)
        //     {
        //         flint_printf("warning: some newton steps failed!\n");
        //     }

        //     flint_printf("refined root (%wd/%wd):\n", i, num);
        //     arb_printn(z, digits + 2, 0);
        //     flint_printf("\n\n");
        // }
    }

    flint_printf("---------------------------------------------------------------\n");
    flint_printf("Found roots: %wd\n", found_roots);
    flint_printf("Subintervals possibly containing undetected roots: %wd\n", found_unknown);
    flint_printf("Function evaluations: %wd\n", eval_count);

    for (slong i = 0; i < num; i++)
        arf_interval_clear(blocks + i);

    flint_free(blocks);
    flint_free(info);

    arf_interval_clear(t);
    arf_interval_clear(interval);
    arf_clear(C);
    arb_clear(v);
    arb_clear(w);
    arb_clear(z);
    flint_cleanup();
}
