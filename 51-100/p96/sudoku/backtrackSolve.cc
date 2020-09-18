#include "sudoku.ih"

void Sudoku::backtrackSolve()
{
    vector<int> xCo, yCo;           // Get grid coordinates of remaining zeros.
    
    for (int x = 0; x != 9; ++x)
        for (int y = 0; y != 9; ++y)
            if (d_elements[x][y] == 0)
            {
                xCo.push_back(x);
                yCo.push_back(y);
            }

    size_t idx = 0;
    while (idx != xCo.size())       // Backtracking algorithm.
    {
        while (d_elements[xCo[idx]][yCo[idx]] == 9)
        {
            d_elements[xCo[idx]][yCo[idx]] = 0;
            idx--;                  // Go back if error and number = 9.
        }
                                    // Increment.
        ++d_elements[xCo[idx]][yCo[idx]];
                                    
        if (!this->errors(xCo[idx], yCo[idx])) 
            ++idx;                  // If no errors, move to next coordinate.
    }    
}
