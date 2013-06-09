#include <iostream>
#include <set>

template<typename T>
class Visitor;

struct Blue;
struct Red;
struct Green;

struct BaseVisitable {
public:
	virtual void accept(Visitor<BaseVisitable>& v) = 0;
	virtual void see_the_sky() = 0;
};

template<typename T>
class Visitor {
public:
	virtual void visit(T&) = 0;
};

struct Blue : BaseVisitable {
public:
	virtual void accept(Visitor<BaseVisitable>& visitor) {
		visitor.visit(*this);
	}

	virtual void see_the_sky() {
		std::cout << "The Sky is blue" << std::endl;
	}
};

struct Red : BaseVisitable {
public:
	virtual void accept(Visitor<BaseVisitable>& visitor) {
		visitor.visit(*this);
	}

	virtual void see_the_sky() {
		std::cout << "The Sky is red" << std::endl;
	}
};

struct Green : BaseVisitable {
public:
	virtual void accept(Visitor<BaseVisitable>& visitor) {
		visitor.visit(*this);
	}

	virtual void see_the_sky() {
		std::cout << "The Sky is green" << std::endl;
	}
};

template<typename T>
class CallVisitor : public Visitor<T> {
public:
	virtual void visit(T& x) {
		x.see_the_sky();
	}
};

int main(void) {
	std::cout << "---- Visitor Problem ----" << std::endl;

	CallVisitor<BaseVisitable> cv;
	Red().accept(cv);
	Blue().accept(cv);
	Green().accept(cv);
	return 0;
}
