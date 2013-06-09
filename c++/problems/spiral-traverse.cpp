#include <vector>
#include <iostream>

typedef std::vector<std::vector<long> > Vector2D;

void printSpiral(Vector2D array) {
	int maxRow = array.size();
	if (!maxRow) {
		return;
	}

	int maxColumn = array[0].size();
	if (!maxColumn) {
		return;
	}

	std::cout << "Spiral formation for [" << maxRow << ", " << maxColumn << "]" << std::endl;

	int minRow = 0, minColumn = 0;
	enum Direction { LeftToRight, TopToDown, RightToLeft, DownToTop} runDirection;
	runDirection = LeftToRight;
	for (int maxElements = maxRow * maxColumn; maxElements > 0;) {
		switch (runDirection) {
			case LeftToRight:
				for (int i = minColumn; i < maxColumn; ++i, --maxElements) {
					std::cout << array[minRow][i] << " -> " << std::flush;
				}
				runDirection = TopToDown;
				minRow++;
				break;
				;

			case TopToDown:
				for (int i = minRow; i < maxRow; ++i, --maxElements) {
					std::cout << array[i][maxColumn - 1] << " -> " << std::flush;
				}
				runDirection = RightToLeft;
				maxColumn--;
				break;
				;

			case RightToLeft:
				for (int i = maxColumn - 1; i >= minColumn; --i, --maxElements) {
					std::cout << array[maxRow - 1][i] << " -> " << std::flush;
				}
				runDirection = DownToTop;
				maxRow--;
				break;
				;

			case DownToTop:
				for (int i = maxRow - 1; i >= minRow; --i, --maxElements) {
					std::cout << array[i][minColumn] << " -> " << std::flush;
				}
				runDirection = LeftToRight;
				minColumn++;
				break;
				;
		}
	}

	std::cout << std::endl;
}

void print(Vector2D array) {
	for (Vector2D::const_iterator pIt = array.begin(); pIt != array.end(); ++pIt) {
		for (std::vector<long>::const_iterator pIt2 = pIt->begin(); pIt2 != pIt->end(); ++pIt2) {
			std::cout << *pIt2 << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	std::vector<Vector2D> testData = {
			{
				{1, 2, 3},
				{4, 5, 6},
				{7, 8, 9}
			},
			{
			},
			{
				{1, 2},
				{3, 4}
			},
			{
				{1, 2, 3, 4, 5, 6},
				{6, 7, 8, 9, 10, 11}
			},
			{
				{1, 2, 3, 4, 5, 6},
				{6, 7, 8, 9, 10, 11},
				{12, 13, 14, 15, 16, 17}
			},
			{
				{1, 2, 3},
				{4, 5, 6},
				{7, 8, 9},
				{10, 11, 12},
				{13, 14, 15}
			}
		};

	for (std::vector<Vector2D>::iterator pIt = testData.begin(); pIt != testData.end(); ++pIt) {
		std::cout << std::endl << "------------- New Set -------------" << std::endl;
		print(*pIt);
		printSpiral(*pIt);
	}

	return 0;
}
