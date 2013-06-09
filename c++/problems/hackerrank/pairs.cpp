#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;


int main() {
	std::set<int> values;
	int count, k, value;

	std::cin >> count >> k;
	for (int i = 0; i < count; ++i) {
		std::cin >> value;
		values.insert(value);
	}

	int kCount = 0;
	for (std::set<int>::const_iterator pIt = values.begin(); pIt != values.end(); ++pIt) {
		if (values.end() != values.find(*pIt - k)) {
			++kCount;
		}
	}

	std::cout << kCount;

	return 0;
}
