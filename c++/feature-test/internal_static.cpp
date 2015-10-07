#include <iostream>

using namespace std;

class Test {
public:
	int getNextId(void) const {
		static int id = 0;
		return ++id;
	}
};

int main(void) {
	Test x, y;
	cout << "X[id => " << x.getNextId() << "],  Y[id => " << y.getNextId() << "]" << std::endl;
	cout << "X[id => " << x.getNextId() << "],  Y[id => " << y.getNextId() << "]" << std::endl;
	return 0;
}
