#include "main.ih"

vector<Sudoku> import(string const &fileName)
{
    vector<Sudoku> sudokus;             // Initialize vector of Sudoku objects.

    ifstream file(fileName);            // Initialize input filestream object.

    vector<vector<int>> tmpSudoku;      // Temporary Sudoku vector.
    int count = 0;                      // Reset every nine lines.

    string line;                        // Mold for reading lines.
    while (getline(file, line))
    {
        if (line.find("Grid") == string::npos)   // Ignore lines with "Grid".
        {
            vector<int> tmpLine;
            for (int idx = 0; idx != 9; ++idx)
                tmpLine.push_back(static_cast<int>(line[idx]) - '0');

            tmpSudoku.push_back(tmpLine);       // Add line to temp.
            ++count;
        }

        if (count == 9)                         // Reset every nine lines.
        {
            Sudoku next(tmpSudoku);             // Initialze next Sudoko object.
            sudokus.push_back(next);            // Add to Sudoku object vector.
            
            count = 0;                          // Reset count and vector.
            tmpSudoku.clear();
        }
    }
                                                
    vector<Sudoku>(sudokus).swap(sudokus);      // Shed excess capacity.

    return sudokus;                             // Return sudoku vector.
}
