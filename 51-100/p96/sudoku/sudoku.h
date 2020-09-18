#ifndef INCLUDED_SUDOKU_
#define INCLUDED_SUDOKU_

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> grid;

class Sudoku
{
    // DATA MEMBERS
    grid d_elements;

    public:
        // CONSTRUCTORS
        Sudoku(grid const &elements);

        // OVERLOADED OPERATORS
        friend std::ostream &operator<<(std::ostream &out, Sudoku const &sudoku);

        // ACCESSORS
        int topleftnum() const;
        bool errors() const;

        // MEMBER FUNCTIONS
        void solve();

    private:
        void logicSolve();
        void backtrackSolve();
        bool errors(int xCo, int yCo) const;
};

inline int Sudoku::topleftnum() const
{
    return 100 * d_elements[0][0] + 10 * d_elements[0][1] + d_elements[0][2];
}

#endif
