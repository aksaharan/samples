#include <iostream>

class A {
 public:
 	int x;

 	virtual void p() {}
 	virtual void q() {}
 	virtual void r() {}
};

int main(void)
{
	A a;
	std::cout << "Sizeof Value - " << sizeof(a) << std::endl;
	return 0;
}
