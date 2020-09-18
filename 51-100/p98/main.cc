#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

// Generate anagrams.
vector<pair<string, string>> genanagrams(vector<string> const &words)
{
    vector<string> sortedWords = words;

    for (size_t idx = 0; idx != words.size(); ++idx)
        sort(sortedWords[idx].begin(), sortedWords[idx].end());    

    vector<pair<string, string>> anagrams;

    for (size_t ii = 0; ii != words.size(); ++ii)
        for (size_t jj = ii + 1; jj != words.size(); ++jj)
            if (sortedWords[ii] == sortedWords[jj])
                anagrams.push_back(make_pair(words[ii], words[jj]));
    
    return anagrams;
}

// Generates all potential square numbers for a given anagramic pair.
vector<size_t> gensquarenums(pair<string, string> const &anagram)
{
    vector<size_t> squarenums;
    size_t digits = anagram.first.length();
    
    size_t num = 1;    
    while (true)
    {
        if (pow(num, 2) > pow(10, digits))
            return squarenums;

        if (pow(num, 2) >= pow(10, digits - 1))
            squarenums.push_back(pow(num, 2));

        ++num;
    }
}

// Generate a permutation using a number for a given anagramic pair.
size_t genperm(size_t num, pair<string, string> const &anagram)
{
    string tempnum = to_string(num);
    string str = anagram.second;

    for (size_t idx = 0; idx != tempnum.length(); ++idx)
        replace(str.begin(), str.end(), anagram.first[idx], tempnum[idx]);
    
    return stoul(str);
}

// Check if all characters in a string are unique (no doubles).
bool uniquechars(string str)
{ 
    for (size_t ii = 0; ii != str.length(); ii++)
        for (size_t jj = ii + 1; jj != str.length(); jj++)
            if (str[ii] == str[jj])
                return false; 

    return true; 
}

int main()
{
    // Load words.txt into words vector.
    ifstream file("words.txt"); 

    vector<string> words;

    string word;
    while (file >> word)
        words.push_back(word);

    // Find all anagramic pairs.
    vector<pair<string, string>> anagrams = genanagrams(words);

    // The number we want to find.
    size_t largestsquare = 0;   

    // Loop over all anagram pairs.
    for (size_t ii = 0; ii != anagrams.size(); ++ii)
    {
        pair<string, string> anagram = anagrams[ii];

        // For each anagram pair, generate all square numbers with the same
        // amount of digits as the anagram has letters.
        vector<size_t> squares = gensquarenums(anagram);

        // Loop over every such square number.
        for (size_t idx = 0; idx != squares.size(); ++idx)
        {
            // Generate permutation of anagram using square number.
            size_t permutation = genperm(squares[idx], anagram);
            
            if
            (           // If permutation is also a square and
                find(squares.begin(), squares.end(), permutation) != squares.end()
                &&      // the permutation is not itself and
                squares[idx] != permutation
                &&      // all digits are unique and
                uniquechars(to_string(squares[idx]))
                &&      // the permutation is larger than the previous largest,
                largestsquare < permutation
            )           // save the permutation.
                largestsquare = permutation;
        }
    }
    cout << largestsquare << '\n';      // Print solution.
}
