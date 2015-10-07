#include <iostream>
#include <set>

class Visitor;

struct BaseVisitable {
public:
	virtual void accept(Visitor& v) = 0;
	virtual void see_the_sky() = 0;
};

class Visitor {
public:
	virtual void visit(BaseVisitable&) = 0;
};

struct DefaultVisitable : public BaseVisitable {
public:
	virtual void accept(Visitor& v) {
		v.visit(*this);
	}
};

struct Blue : DefaultVisitable {
public:
	virtual void see_the_sky() {
		std::cout << "The Sky is blue" << std::endl;
	}
};

struct Red : DefaultVisitable {
public:
	virtual void see_the_sky() {
		std::cout << "The Sky is red" << std::endl;
	}
};

struct Green : DefaultVisitable {
public:
	virtual void see_the_sky() {
		std::cout << "The Sky is green" << std::endl;
	}
};

class CallVisitor : public Visitor {
public:
	virtual void visit(BaseVisitable& x) {
		x.see_the_sky();
	}
};

int main(void) {
	std::cout << "---- Visitor Problem ----" << std::endl;

	CallVisitor cv;
	Red().accept(cv);
	Blue().accept(cv);
	Green().accept(cv);
	return 0;
}
