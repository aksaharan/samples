#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class A {
public:
	A(const string& name = "") : _name(name) {}

	void printMe(int x) const {
		cout << "My name is '" << _name << "' with value " << x << endl;
	}

private:
	string _name;
};

int main() {
	typedef void (A::*PrintMeFunc)(int) const;

	PrintMeFunc pmf = &A::printMe;

	A a = {"FirstA"};
	const A* b = &a;
	cout << "Calling as member function to object" << endl;
	(a.*pmf)(1);

	cout << "Calling as member function to object pointer" << endl;
	(b->*pmf)(12);

	A a1("SecondA");
	A a3 {};

	return 0;

}
