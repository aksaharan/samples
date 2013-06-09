#include <iostream>
#include <vector>

int main(void) {
	std::cout << "---- VectorSize Problem ----" << std::endl << std::endl;

	std::vector<int> list(10000);
	std::cout << "Vector Size [AfterInit: " << list.size() << "]" << std::endl;

	list.resize(150);
	std::cout << "Vector Size [AfterResize: " << list.size() << "]" << std::endl;

	list.resize(0);
	std::cout << "Vector Size [AfterResize: " << list.size() << "]" << std::endl;
	return 0;
}
