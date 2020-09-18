import numpy as np

z = []
for i in xrange(1,10001):
	for j in xrange(1,10001):
		a = str(i)+str(j)+str(i*j)
		a = sorted(a)
		if a == ['1','2','3','4','5','6','7','8','9'] and i*j not in z:
				z.append(i*j)
				print(np.sum(z))

#Solved (45228)

#include <iostream>
#include <algorithm>
#include <set>

# using namespace std;

# int main()
# {
#     set<int> products;

#     for (int a = 1; a < 100; ++a)
#         for (int b = 100; b < 10'000; ++b)
#         {
#             if ( (a < 10 and b < 10'000) or (a >= 10 and b < 1000) )
#                 if (a * b < 10'000)
#                 {
#                     string str = to_string(a) + to_string(b) + to_string(a * b);
#                     sort(str.begin(), str.end());

#                     if (str == "123456789")
#                         products.insert(a * b);
#                 }
#         }

#     int sum = 0;
#     for (int product : products)
#         sum += product;
    
#     cout << sum << '\n';
# }