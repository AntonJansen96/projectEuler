#include "sudoku.ih"

void Sudoku::solve()
{
    // CHECK IF SUDOKU IS VALID TO BEGIN WITH
    if (this->errors())
        throw(logic_error("starting Sudoku contains errors"));

    // APPLY DETERMINISTIC SIMPLIFICATION AS MUCH AS POSSIBLE
    logicSolve();

    // BRUTE FORCE REMAINING ZEROS (IF ANY)
    backtrackSolve();
}
