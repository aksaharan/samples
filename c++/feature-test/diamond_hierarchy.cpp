#include <iostream>

class A {
public:
	A() {
		std::cout << "A::A()" << std::endl;
	}

	~A() {
		std::cout << "A::~A()" << std::endl;
	}
};

class B {
public:
	B() {
		std::cout << "B::B()" << std::endl;
	}

	~B() {
		std::cout << "B::~B()" << std::endl;
	}
};

class C : A {
public:
	C() {
		std::cout << "C::C()" << std::endl;
	}

	~C() {
		std::cout << "C::~C()" << std::endl;
	}
};

class D : A, B, C {
public:
	D() {
		std::cout << "D::D()" << std::endl;
	}

	~D() {
		std::cout << "D::~D()" << std::endl;
	}
};

class E : virtual A {
public:
	E() {
		std::cout << "E::E()" << std::endl;
	}

	~E() {
		std::cout << "E::~E()" << std::endl;
	}
};

class F : B, virtual A, E, C {
public:
	F() {
		std::cout << "F::F()" << std::endl;
	}

	~F() {
		std::cout << "F::~F()" << std::endl;
	}
};

int main(void) {
	{
		std::cout << "--------- Non-virtual Diamond Inheritance ---------" << std::endl;
		{ C c; }
		{ D d; }
	}

	{
		std::cout << "--------- Partial-Virtual Diamond Inheritance ---------" << std::endl;
		{ E e; }
		{ F f; }
	}

	return 0;
}
