#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <list>
#include <utility>

template<typename T>
void printRange(T start, T end) {
	std::cout << "[";

	bool isFirst = true;
	for (T it = start; it != end; ++it) {
		if (!isFirst) {
			std::cout << ", ";
		}

		isFirst = false;
		std::cout << "{" << it->first << " - " << it->second << "}";
	}

	std::cout << "]" << std::endl;
}

typedef std::pair<long, long> my_range;

class my_range_comparer {
public:
	bool operator() (const my_range& lhv, const my_range& rhv) const {
		long diff = (lhv.first - rhv.first);
		if (diff == 0) {
			// To make one with larger width as priority
			diff = (rhv.second - lhv.second);
		}
		return (diff == 0 ? false : (diff < 0 ? true : false));
	}
};

/*
	A few assumptions:
	- The list could be unordered
	- The list has range specified in correct order ie {lower, higher}
	- The list may contain duplicates as well, this should be filtered out in sorting / set
*/
void printNonOverlappingRanges(const std::list<my_range>& rangeList, const my_range& range) {
	std::cout << "Input range list => ";
	printRange(rangeList.cbegin(), rangeList.cend());

	if (rangeList.size() == 0) {
		std::cout << "Empty list entire range is non-overlapping [{" << range.first 
				<< " - " << range.second << "}]" << std::endl;
		return;
	}

	std::set<my_range, my_range_comparer> orderedRange;
	for (std::list<my_range>::const_iterator it = rangeList.begin();
			it != rangeList.end();
			++it) {
		orderedRange.insert(*it);
	}

	std::cout << "Ordered Input range list => ";
	printRange(orderedRange.cbegin(), orderedRange.cend());

	std::cout << "Additional Range {" << range.first << " - " << range.second << "}" << std::endl;


	std::cout << "Non-overlapping range [";
	my_range runningRange = range;
	bool isFirst = true;
	for (std::set<my_range>::const_iterator it = orderedRange.begin();
			it != orderedRange.end() && runningRange.first <= runningRange.second;
			++it) {

		if (it->first > runningRange.first) {
			if (it->first > runningRange.second) {
				std::cout << (isFirst ? "" : ", ") << "{" << runningRange.first
						<< " - " << (runningRange.second) << "}";
				runningRange.first = runningRange.second + 1;
			} else if ((it->first >= runningRange.second && it->second > runningRange.second)
					|| it->second <= runningRange.second) {
				std::cout << (isFirst ? "" : ", ") << "{" << runningRange.first
						<< " - " << (it->first - 1) << "}";
				runningRange.first = it->second + 1;
			} else {
				std::cout << (isFirst ? "" : ", ") << "{" << runningRange.first
						<< " - " << (runningRange.second) << "}";
				runningRange.first = runningRange.second + 1;
			}
			isFirst = false;
		} else if (it->second >= runningRange.first) {
			runningRange.first = it->second + 1;
		} else if (it->first <= runningRange.second && it->second >= runningRange.second) {
			runningRange.second = it->second + 1;
		}
	}

	if (runningRange.first <= runningRange.second) {
		std::cout << (isFirst ? "" : ", ") << "{" << runningRange.first << " - "
				<< runningRange.second << "}";
	}

	std::cout << "]" << std::endl;
}

int main(void) {
	std::cout << "---- RangeOverlap Problem ----" << std::endl;

	std::list<my_range> rangeList = { 
			{15000000, 19000000}, 
			{6000000, 10000000}, 
			{17000000, 24000000}
		};

	printNonOverlappingRanges(rangeList, {8000000, 28000000});	

	std::cout << std::endl << std::endl;
	printNonOverlappingRanges({}, {20000000, 3000000});	

	std::cout << std::endl << std::endl;
	printNonOverlappingRanges(rangeList, {25000000, 30000000});	

	std::cout << std::endl << std::endl;
	printNonOverlappingRanges(rangeList, {4000000, 6000000});	

	std::cout << std::endl << std::endl;
	printNonOverlappingRanges(rangeList, {4000000, 5000000});	

	std::cout << std::endl << std::endl;
	printNonOverlappingRanges(rangeList, {6000000, 8000000});	

	std::cout << std::endl << std::endl;
	printNonOverlappingRanges(rangeList, {10000001, 14999999});	
	return 0;
}
