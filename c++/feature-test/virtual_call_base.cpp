#include <iostream>

class Building {
public:
	Building() {
		this->anotherPrint();
	}

	virtual void printMe() const = 0;

	void anotherPrint() {
		this->printMe();
	}
};

class Home : public Building {
public:
	virtual void printMe() const {
		std::cout << "I am in home..." << std::endl;
	}
};

class Office : public Building {
public:
	virtual void printMe() const {
		std::cout << "I am in office..." << std::endl;
	}
};

int main() {
	Building* h = new Home();
	Building* o = new Office();

	return 0;
}
