/*
Triangle - Maximum adjacent number sum

Triangle
By starting at the top of the triangle and moving to adjacent numbers on the row below, the maximum total from top to bottom is 27.

        5
      9  6
    4   6  8
  0   7  1   5

I.e. 5 + 9 + 6 + 7 = 27.

*/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>

/*
	A few key assumptions / thoughts:
	- The triangle data can be loaded into memory
	- Instead of top-down, a bottom-up approach seems more reasonable to understand / code
	- Top-approach can be more optimized in terms of space complexity
*/

void usage(const char* progName) {
	std::cout << "Usage: " << progName << " <file1> [<file2>...]" << std::endl;
}

bool loadFile(const std::string& filename, std::vector<std::vector<long> >& triangle) {
	long row = 0;

	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Error: Failed to open file [" << filename << "], will not proceed further for this file" << std::endl;
		return false;
	}

	bool returnStatus = true;
	long totalElements = 0;
	std::vector<long> rowValues;
	while (inFile.good() && !inFile.eof()) {
		std::string line;
		std::getline(inFile, line);
		if (inFile.eof() && line.size() == 0) {
			break;
		}

		++row;

		std::istringstream inStr(line);
		rowValues.clear();
		std::copy(std::istream_iterator<long>(inStr), std::istream_iterator<long>(), std::back_insert_iterator<std::vector<long> >(rowValues));
		if (rowValues.size() != row) {
			std::cerr << "Error: values on the row does not match expected rows [Row: " << row << ", Elements: " << rowValues.size() 
					<< "], will not continue further." << std::endl;
			returnStatus = true;
			break;
		}
		triangle.push_back(rowValues);
		totalElements += rowValues.size();

	}

	inFile.close();
	return returnStatus;
}

bool processFile(std::string filename, long& maxValue, long& rows) {
	std::vector<std::vector<long> > triangle;	
	if (!loadFile(filename, triangle) || triangle.size() == 0) {
		std::cerr << "Error: Failed to load triangle or empty triangle detected [File: " << filename << "]" << std::endl;
		return false;
	}

	rows = triangle.size();
	// Keys Assumptions:
	// - long value can contain the maximum sum and does not overflow on value
	// - data is perfect triangle
	for (int activeRow = triangle.size() - 2; activeRow >= 0; --activeRow) {
		std::vector<long>& thisRow = triangle[activeRow];
		std::vector<long>& nextRow = triangle[activeRow + 1];
		for (int activeCol = 0; activeCol < thisRow.size(); ++activeCol) {
			thisRow[activeCol] = std::max((thisRow[activeCol] + nextRow[activeCol]), (thisRow[activeCol] + nextRow[activeCol + 1]));
		}
	}

	maxValue = triangle[0][0];
	return true;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "Error: Missing expected command line arguments" << std::endl;
		usage(argv[0]);
		return 1;
	}

	long maxValue, rows;
	long failedCount = 0;
	for (int i = 1; i < argc; ++i) {
		// Assuming there are no negative values in the triangle, even otherwise this should be fine, since the error is captured
		// by return status of the processFile method
		maxValue = -1;
		rows = 0;

		std::cout << std::endl << "Working on file: " << argv[i] << std::endl;
		if (processFile(argv[i], maxValue, rows)) {
			std::cout << "   Processed [File: " << argv[i] << ", Rows: " << rows << ", MaxSum: " << maxValue << "]" << std::endl;
		} else  {
			++failedCount;
		}
	}
	
	return failedCount;
}
