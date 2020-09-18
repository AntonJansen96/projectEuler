#include "sudoku.ih"

ostream &operator<<(ostream &out, Sudoku const &sudoku)
{
    for (int ii = 0; ii != 9; ++ii)
    {
        for (int jj = 0; jj != 9; ++jj)
            out << sudoku.d_elements[ii][jj] << ((jj == 2 || jj == 5) ? " | " : " ");

        out << ((ii == 2 || ii == 5) ? "\n----------------------\n" : "\n");
    }

    return out;
}
