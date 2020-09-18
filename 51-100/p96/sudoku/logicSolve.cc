#include "sudoku.ih"

void Sudoku::logicSolve()
{
    bitset<9> bit;
    int x = 0, sol = 0;

    while (x != 9)          // Loop through coordinates.
    {
        int y = 0;
        while (y != 9)
        {
            if (d_elements[x][y] == 0)              // If a zero is found,
            {
                bit.reset();

                for (int num = 1; num <= 9; ++num)  // test numbers 1 to 9.
                {
                    d_elements[x][y] = num;

                    if (this->errors(x, y))     // If a number gives an error,
                        bit[num - 1] = 1;       // set according bit.
                    else
                        sol = num;
                }

                if (bit.count() == 8)           // If 8/9 nums gave an error,
                {
                    d_elements[x][y] = sol;     // fill in sol in Sudoku.
                    x = 0, y = -1;              // Start from beginning.
                    break;
                }
                else
                    d_elements[x][y] = 0;       // Else restore element to zero.
            }
            ++y;
        }
        ++x;
    }
}
