#include <iostream>

class Test {
	public:
		virtual void VirtTest();
};

class Best : public Test {
};

int main(void)
{
	std::cout << "Hands Stream...." << std::endl;
	return 0;
}
