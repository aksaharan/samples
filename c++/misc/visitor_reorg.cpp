#include <iostream>
#include <set>

class Visitor;
struct Blue;
struct Red;
struct Green;

struct BaseVisitable {
public:
	virtual void accept(Visitor& v) = 0;
};

class Visitor {
public:
	virtual void visit(Blue&) = 0;
	virtual void visit(Red&) = 0;
	virtual void visit(Green&) = 0;
};

struct Blue : BaseVisitable {
public:
	virtual void accept(Visitor& visitor) {
		visitor.visit(*this);
	}

	void see_the_sky() {
		std::cout << "The Sky is blue" << std::endl;
	}
};

struct Red : BaseVisitable {
public:
	virtual void accept(Visitor& visitor) {
		visitor.visit(*this);
	}

	void see_the_sky() {
		std::cout << "The Sky is red" << std::endl;
	}
};

struct Green : BaseVisitable {
public:
	virtual void accept(Visitor& visitor) {
		visitor.visit(*this);
	}

	void see_the_sky() {
		std::cout << "The Sky is green" << std::endl;
	}
};

class CallVisitor : public Visitor {
public:
	virtual void visit(Blue& b) {
		b.see_the_blue_sky();
	}

	virtual void visit(Red& r) {
		r.see_the_sky();
	}

	virtual void visit(Green& g) {
		g.see_the_sky();
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
