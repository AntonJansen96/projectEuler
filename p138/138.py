#!/usr/bin/env python3


def profile(func, *args, sort_by="cumtime", lines=20, **kwargs):
    import cProfile
    import pstats

    profiler = cProfile.Profile()
    profiler.enable()
    func(*args, **kwargs)
    profiler.disable()

    stats = pstats.Stats(profiler)
    stats.strip_dirs().sort_stats(sort_by).print_stats(lines)


def assert_example():
    b = 16  # base length
    L = 17  # Legs

    h = (L**2 - (0.5 * b) ** 2) ** 0.5
    print(h)
    assert abs(b - h) <= 1

    b = 272
    L = 305

    h = (L**2 - (0.5 * b) ** 2) ** 0.5
    print(h)
    assert abs(b - h) <= 1


def naive():
    for b in range(1, 5500):
        for L in range(1, 5500):
            if 2 * L > b:
                h = (L * L - 0.25 * b * b) ** 0.5
                if int(h) == h and abs(b - h) <= 1:
                    print(b, L, int(h))


def efficient():
    lim = 10**4

    for m in range(1, lim):
        for n in range(m + 1, lim):
            if not (m & 1 and n & 1):
                a = n * n - m * m
                b = 2 * m * n
                c = n * n + m * m

                if a < b:
                    if b < c:
                        # order = (a, b, c)
                        if 2 * a - b in [1, -1]:
                            print(a, b, c)
                    elif a < c:
                        # order = (a, c, b)
                        if 2 * a - c in [1, -1]:
                            print(a, b, c)
                    else:
                        # order = (c, a, b)
                        if 2 * c - a in [1, -1]:
                            print(a, b, c)
                else:
                    if a < c:
                        # order = (b, a, c)
                        if 2 * b - a in [1, -1]:
                            print(a, b, c)
                    elif b < c:
                        # order = (b, c, a)
                        if 2 * b - c in [1, -1]:
                            print(a, b, c)
                    else:
                        # order = (c, b, a)
                        if 2 * c - b in [1, -1]:
                            print(a, b, c)


# In the end, solved it by realizing can rewrite the problem to Pell's equation.
# Then use Pell's equation solver to obtain recursive expressions for x_next
# and y_next.

# 2b \pm 1 = sqrt(L^2 - b^2)  ->
# 5x^2 - y^2 \pm 4x + 1 = 0
# https://www.alpertron.com.ar/QUAD.HTM


def final():
    x = 0
    y = 1

    total = -1  # ignore first solution [0, 1]

    for _ in range(12 + 1):
        x_next = -9 * x + 4 * y - 4
        y_next = 20 * x - 9 * y + 8
        total += max(abs(x_next), abs(y_next))
        x, y = x_next, y_next

    print(total)


if __name__ == "__main__":
    # assert_example()
    # naive()
    # pythagoras()
    # efficient()
    # profile(efficient)
    # profile(alternative)
    final()
