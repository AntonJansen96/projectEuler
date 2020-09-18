#145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
#Find the sum of all numbers which are equal to the sum of the factorial of their digits.
#Note: as 1! = 1 and 2! = 2 are not sums they are not included.

def factorial(n):
	g = 1
	for i in xrange(1,n+1):
		g *= i
	return g

total = 0

for i in xrange(3,10**6):

	a = 0
	b = str(i)

	for j in range(0,len(b)):
		a += factorial(int(b[j]))

	if a == i:
		total += i
		print(total)

#Solved (40730)

# // C++

#include <iostream>
#include <vector>
#include <string>

# using namespace std;

# int main()
# {
#     vector<int> const facs = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

#     int solution = 0;
#     for (int num = 3; num != 50'000; ++num)
#     {
#         int sum = 0;
#         for (char digit : to_string(num))
#             sum += facs[digit - '0'];
        
#         if (sum == num)
#             solution += sum;
#     }

#     cout << solution << '\n';
# }