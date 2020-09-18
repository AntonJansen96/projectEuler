#include "sudoku.ih"

bool Sudoku::errors() const
{
    bitset<10> bit;
    
    for (int row = 0; row != 9; ++row)
    {
        bit.reset();
        
        for (int num : d_elements[row])
            if (num != 0)
            {
                if (not bit[num])
                    bit.set(num);
                else
                    return true;
            }
    }

    // CHECK COLUMNS
    for (int col = 0; col != 9; ++col)
    {
        bit.reset();

        for (vector<int> const &row : d_elements)
            if (row[col] != 0)
            {
                if (not bit[row[col]])
                    bit.set(row[col]);
                else
                    return true;            
        }
    }

    // CHECK SQUARES
    for (int row : {0, 3, 6})
        for (int col : {0, 3, 6})
        {
            bit.reset();
            
            for (int ii = row; ii != row + 3; ++ii)
                for (int jj = col; jj != col + 3; ++jj)
                    if (d_elements[ii][jj] != 0)
                    {
                        if(not bit[d_elements[ii][jj]])
                            bit.set(d_elements[ii][jj]);
                        else
                            return true;
                    }
        }

    return false;
}
