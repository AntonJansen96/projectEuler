#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<int>> import(string const &filename, int dim)
{
    ifstream file(filename);
    vector<vector<int>> matrix(dim);

    int element, idx = 0, line = 0;
    
    while (file >> element)
    {
        matrix[line].push_back(element);
        ++idx;

        if (idx == dim)
        {
            idx = 0;
            ++line;
        }
    }

    return matrix;
}

void print(vector<vector<int>> matrix)
{
    for (size_t ii = 0; ii != matrix.size(); ++ii)
    {
        cout << '[';
        
        for (size_t jj = 0; jj != matrix.size(); ++jj)
            cout << matrix[ii][jj] << " ";

        cout << "]\n";
    }

}

int minPathSelf(vector<vector<int>> &matrix) // Right and down
{    
    int dim = matrix.size();

    for (int row = 0; row < dim; ++row)
        for (int col = 0; col < dim; ++col)
        {
            if (row == 0)
                matrix[row][col] += matrix[row][col - 1];

            else if (col == 0)
                matrix[row][col] += matrix[row - 1][col];

            else if (row == 0 && col == 0)
                continue;
            
            else
                matrix[row][col] += min(matrix[row][col - 1], matrix[row - 1][col]);
        }

    // Answer is minimum value of first row.
    int answer = matrix[dim - 1][0];          
    for (auto element : matrix[dim - 1])
        if (element > answer)
            answer = element;
    
    return answer;
}

int main()
{
    vector<vector<int>> matrix = import("p081_matrix.txt", 80);
    vector<vector<int>> test = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    print(test);
    cout << minPathSelf(matrix) << '\n';
    print(matrix);
}




// int minFallingPathSum(vector<vector<int>> matrix, int dim)
// {
//     // R = Row and C = Column 
//     // We begin from second last row and keep 
//     // adding maximum sum.
//     for (int R = dim - 2; R >= 0; --R)
//         for (int C = 0; C < dim; ++C)
//         {   // best = min(matrix[R+1][C-1], matrix[R+1][C], matrix[R+1][C+1]) 
//             int best = matrix[R + 1][C]; 

//             if (C > 0) 
//                 best = min(best, matrix[R + 1][C - 1]); 

//             if (C + 1 < dim) 
//                 best = min(best, matrix[R + 1][C + 1]); 

//             matrix[R][C] = matrix[R][C] + best; 
//         }

//     int ans = 1'000'000'000;
//     for (int i = 0; i < dim; ++i) 
//         ans = min(ans, matrix[0][i]); 
//     return ans;
// } 

// int minPathSelf(vector<vector<int>> &matrix) // right left down
// {
//     int dim = matrix.size();

//     for (int row = dim - 2; row >= 0; row--)
//         for (int col = 0; col != dim; ++col)
//         {
//             if (col == 0) // Boundary case: all the way to left.
//                 matrix[row][col] += min(matrix[row + 1][col], matrix[row + 1][col + 1]);
//             else if (col == dim - 1) // Boundary case: all the way to the right.
//                 matrix[row][col] += min(matrix[row + 1][col - 1], matrix[row + 1][col]);
//             else
//                 matrix[row][col] += min(matrix[row + 1][col - 1], min(matrix[row + 1][col], matrix[row + 1][col + 1]));
//         }

//     // Answer is minimum value of first row.
//     int answer = matrix[0][0];          
//     for (auto element : matrix[0])
//         if (element < answer)
//             answer = element;
    
//     return answer;
// }
