#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> import(string const &filename)
{
    ifstream file(filename);
    vector<string> numerals;

    string word;
    while (file >> word)
        numerals.push_back(word);
    
    return numerals;
}

size_t countChars(vector<string> const &vector)
{
    size_t count = 0;
    for (size_t idx = 0; idx != vector.size(); ++idx)
        count += vector[idx].length();
    
    return count;
}

size_t roman2dec(string &roman)
{
    map<char, size_t> dict =
    { 
        {'M', 1000},
        {'D', 500},
        {'C', 100},
        {'L', 50},
        {'X', 10},
        {'V', 5},
        {'I', 1}
    };

    size_t decimal = 0; 
  
    for (size_t idx = 0; idx < roman.length(); ++idx)
    { 
        if (idx + 1 < roman.length()) 
        { 
            if (dict[roman[idx]] >= dict[roman[idx + 1]]) 
                decimal += dict[roman[idx]];
            else
            { 
                decimal += (dict[roman[idx + 1]] - dict[roman[idx]]);
                ++idx;
            } 
        } 
        else
            decimal += dict[roman[idx]]; 
    } 
    return decimal; 
} 

string dec2roman(size_t dec)
{
    string M[] = {"", "M", "MM", "MMM", "MMMM"};
    string H[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string T[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string O[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    
    return M[dec / 1000] + H[dec % 1000 / 100] + T[dec % 100 / 10] + O[dec % 10];
}

int main()
{
    vector<string> oldNumerals = import("roman.txt");
    vector<string> newNumerals;

    for (size_t idx = 0; idx != oldNumerals.size(); ++idx)
        newNumerals.push_back(dec2roman(roman2dec(oldNumerals[idx])));

    cout << countChars(oldNumerals) - countChars(newNumerals) << '\n';
}
