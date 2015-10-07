#include <iostream>

class Test {
public:
	Test() {
		std::cout << "Called Constructor for [" << __FUNCTION__ << "]" << std::endl;
	}

	Test(const Test&) {
		std::cout << "Called Copy Constructor for [" << __FUNCTION__ << "]" << std::endl;
	}

	~Test() {
		std::cout << "Called Destructor for [" << __FUNCTION__ << "]" << std::endl;
	}

	Test& operator= (const Test& x) {
		std::cout << "Called Assignment Operator for [" << __FUNCTION__ << "]" << std::endl;
	}

/*
	// Destructor cannot be overloaded
	~Test(int) {
		std::cout << "Called Destructor with int argument" << std::endl;
	}
	*/
};

class TestDerived : public Test {
public:
	TestDerived() {
		std::cout << "Called Constructor for [" << __FUNCTION__ << "]" << std::endl;
	}

	~TestDerived() {
		std::cout << "Called Destructor for [" << __FUNCTION__ << "]" << std::endl;
	}
		
};

int main(void) {
	Test t = TestDerived();
	// t.Test(); // Would give error for call
	//t.~Test();
	t = TestDerived();
//	t.~Test(int);
}
