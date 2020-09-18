def calc_chain(n):
	D = {'0':1,'1':1,'2':2,'3':6,'4':24,'5':120,'6':720,'7':5040,'8':40320,'9':362880}
	z = [n]

	while True:
		y = 0
		for i in str(n):
			y += D[i]

		if y not in z:
			z.append(y)
			n = y
			continue
		
		return z

count = 0
for i in xrange(1,10**6):
	if len(calc_chain(i)) == 60:
		count += 1

print(count)

#Solved (28.2s on Laptop, answer = 402)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

# size_t chainLen(size_t num)
# {
#     std::vector<size_t> const facs = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
#     std::vector<size_t> z = {num};

#     while (true)
#     {
#         size_t y = 0;
#         for (char idx : std::to_string(num))
#             y += facs[idx - '0'];

#         if (find(z.begin(), z.end(), y) == z.end())
#         {
#             z.push_back(y);
#             num = y;
#             continue;
#         }

#         return z.size();
#     }
# }

# int main()
# {
#     size_t count = 0;
#     for (size_t num = 1; num < 1'000'000; ++num)
#         if (chainLen(num) == 60)
#             ++count;

#     std::cout << count << '\n';
# }
