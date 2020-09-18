#include "sudoku.ih"

bool Sudoku::errors(int xCo, int yCo) const
{
    // CHECK ROW CONTAINING COORDINATE
    bitset<10> bit;
    
    for (int num : d_elements[xCo])
        if (num != 0)
        {
            if (not bit[num])
                bit.set(num);
            else
                return true;
        }

    // CHECK COLUMN CONTAINING COORDINATE
    bit.reset();
    
    for (vector<int> const &row : d_elements)
        if (row[yCo] != 0)
        {
            if (not bit[row[yCo]])
                bit.set(row[yCo]);
            else
                return true;            
        }

    // CHECK SQUARE CONTAINING COORDINATE
    bit.reset();

    int row = 6, col = 6;

    if (xCo < 3)
        row = 0;
    else if (xCo < 6)
        row = 3;

    if (yCo < 3)
        col = 0;
    else if (yCo < 6)
        col = 3;

    for (int ii = row; ii != row + 3; ++ii)
        for (int jj = col; jj != col + 3; ++jj)
            if (d_elements[ii][jj] != 0)
            {
                if(not bit[d_elements[ii][jj]])
                    bit.set(d_elements[ii][jj]);
                else
                    return true;
            }

    return false;
}
