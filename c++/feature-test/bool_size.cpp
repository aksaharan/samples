#include <iostream>

int main(void) {
	bool x = true;
	bool* xDynList = new bool[100];
	bool xStaticList[100];

	std::cout << "bool: " << sizeof(x) << ", new bool[100]: " << sizeof(xDynList) << ", bool[100]: " << sizeof(xStaticList) << std::endl;
}
