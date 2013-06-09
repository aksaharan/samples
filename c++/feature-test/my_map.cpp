#include <iostream>
#include <map>
#include <string>

class my_map : public std::map<std::string, int> {
};

class A {
public:
	A() {
		std::cout << "A::A" << std::endl;
	}

	~A() {
		std::cout << "A::~A" << std::endl;
	}
};

class B : public A {
public:
	B() {
		std::cout << "B::B" << std::endl;
	}

	~B() {
		std::cout << "B::~B" << std::endl;
	}
};

int main(void) {
	std::cout << "---- my_map Problem ----" << std::endl << std::endl;

	{
		std::cout << "--- Testing A ----" << std::endl;
		A a;
	}

	{
		std::cout << "--- Testing B ----" << std::endl;
		B b;
	}

	{
		std::cout << "--- Testing B as A ----" << std::endl;
		A a = B();
	}

	{
		std::cout << "--- Testing B as A with new / delete ----" << std::endl;
		A* a = new B();
		delete a;
	}

	return 0;
}
