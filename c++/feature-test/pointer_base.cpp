#include <iostream>

class Building {
public:
	virtual void printMe() const = 0;

	void anotherPrint() const {
		std::cout << "Another Print in building..." << std::endl;
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

	void anotherPrint() const {
		std::cout << "Another Print in office..." << std::endl;
	}
};

int main() {
	Home* h = new Home();
	Office* o = new Office();

	Office** opp = &o;
	Building* bpp = *opp;

	h->printMe();
	o->printMe();
	(*opp)->printMe();
	bpp->printMe();

	bpp = h;
	bpp->printMe();

	bpp->anotherPrint();
	o->anotherPrint();
	h->anotherPrint();

	return 0;
}
