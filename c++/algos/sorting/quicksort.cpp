#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#define TYPENAME(x) #x

namespace {
	template<typename T>
	void swap(T& x, T& y) {
		T temp = x;
		x = y;
		y = temp;
	}

	template<typename T>
	void quicksort(std::vector<T>& array, size_t start, size_t end) {
		if (start >= end) {
			return;
		}

		T partitionElem = array[(start + end) / 2];
		std::cout << "   Sort criteria[" << start << ", " << end << "] -> " << " : " << partitionElem << " {";
		std::copy(array.begin(), array.end(), std::ostream_iterator<T>(std::cout, ", "));
		std::cout << "}" << std::endl;

		// Choose paritioning element
		size_t partition = start;
		swap(array[end], array[(start + end) / 2]);

		// Partition
		for (size_t i = start; i < end; ++i) {
			if (array[i] <= partitionElem) {
				swap(array[i], array[partition]);
				++partition;
			}
		}
		swap(array[partition], array[end]);

		// Quick sort left + right sides of array
		if ((start + 1) < partition) {
			quicksort(array, start, partition - 1);
		}

		quicksort(array, partition + 1, end);
	}

	template<typename T>
	void attempSort(std::vector<T> array) {
		std::cout << "Initial List {";
		std::copy(array.begin(), array.end(), std::ostream_iterator<T>(std::cout, ", "));
		std::cout << "}" << std::endl;

		quicksort(array, 0, array.size() - 1);
		std::cout << "Sorted List {";
		std::copy(array.begin(), array.end(), std::ostream_iterator<T>(std::cout, ", "));
		std::cout << "}" << std::endl << std::endl;
	}
}

int main() {
	attempSort(std::vector<long>{10, 78, 562, 89, 562, 929, 53, 19});
	attempSort(std::vector<std::string>{"test", "best", "mest", "cest", "lest", "dest"});
	attempSort(std::vector<long>{1, 2, 3, 4, 5, 6, 7});
	attempSort(std::vector<long>{7, 6, 5, 4, 3, 2, 1});
	return 0;
}
