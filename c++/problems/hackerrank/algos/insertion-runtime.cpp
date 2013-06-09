#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

/* Head ends here */
int insertionSort(vector <int>  ar) {
	int count = 0;
	for (int i = 1; i < ar.size(); ++i) {
		int value = ar[i];
		int j = i - 1;
		for (; j >= 0; --j) {
			if (ar[j] > value) {
				ar[j + 1] = ar[j];
				++count;
			} else {
				break;
			}
		}

		ar[j + 1] = value;
	}
	return count;
}

/* Tail starts here */
int main(void) {
	vector <int>  _ar;
	int _ar_size;
	cin >> _ar_size;
	for(int _ar_i=0; _ar_i<_ar_size; _ar_i++) {
		int _ar_tmp;
		cin >> _ar_tmp;
		_ar.push_back(_ar_tmp); 
	}

	std::cout << insertionSort(_ar);
	return 0;
}
