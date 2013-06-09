#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool readData(std::vector<std::pair<long, long> >& breadSizes) {
	long count;
	std::cin >> count;
	if (count <= 0) {
		std::cerr << "Invalid number of objects" << std::endl;
		return false;
	}

	for ( ; count > 0; --count) {
		std::pair<long, long> bread;
		std::cin >> bread.first >> bread.second;
		breadSizes.push_back(bread);
	}

	return true;
}

long getGCF(long a, long b) {
	while (a != b) {
		if (a > b) {
			a = a - b;
		} else {
			b = b - a;
		}
	}

	return a;
}

long getPieces(long length, long breadth) {
	if (length == 0 || breadth == 0) {
		//std::cerr << "Encountered 0 length / breadth : " << length << ":" << breadth << std::endl;
		return 0;
	}

	long gcf = getGCF(length, breadth);
	long gcfLengthMultiple = length / gcf;
	long gcfBreadthMultiple = breadth / gcf;
	if (gcfLengthMultiple == 0 || gcfBreadthMultiple == 0) {
		//std::cerr << "Encountered GCF Multiple of 0 : " << length << ":" << breadth << " - " << gcfLengthMultiple << "-" << gcfBreadthMultiple 
		//		<< ":" << gcf << std::endl;
		return 0;
	}

	return (gcfLengthMultiple * gcfBreadthMultiple) 
			+ getPieces(length, breadth - (gcfBreadthMultiple * gcf))
			+ getPieces(length - (gcfLengthMultiple * gcf), breadth - (gcfBreadthMultiple * gcf))
			;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */    
	std::vector<std::pair<long, long> > breadSizes;
	if (!readData(breadSizes)) {
		return 1;
	}

	for (std::vector<std::pair<long, long> >::const_iterator pIt = breadSizes.begin();
			pIt != breadSizes.end();
			++pIt) {
		std::cout << getPieces(pIt->first, pIt->second) << std::endl;
	}

	return 0;
}

