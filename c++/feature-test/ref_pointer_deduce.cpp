#include <iostream>
#include <string>
#include <type_traits>

using std::string;
using std::cout;
using std::endl;


template<typename T>
struct __reference_type : std::false_type {
public:
	static string type() {
		return "value type";
	}
};

template<typename T>
struct __reference_type<T&> : std::true_type {
	static string type() {
		return "lvalue_ref";
	}
};

template<typename T>
struct __reference_type<T&&> : std::true_type {
	static string type() {
		return "rvalue_ref";
	}
};

template<typename T>
struct __reference_type<T*> : std::false_type {
	static string type() {
		return "pointer";
	}
};

template <typename T>
T&& myMove(T& val) {
	return static_cast<T&&>(val);
}

class MyClass {
public:
	MyClass() {
		cout << "MyClass::MyClass()" << endl;
	}

	MyClass(const MyClass&) {
		cout << "MyClass::MyClass(const MyClass&)" << endl;
	}

	MyClass(MyClass&&) {
		cout << "MyClass::MyClass(MyClass&&)" << endl;
	}

	MyClass& operator = (MyClass&) {
		cout << "MyClass::=(MyClass&)" << endl;
		return *this;
	}

	MyClass& operator = (MyClass&&) {
		cout << "MyClass::=(MyClass&&)" << endl;
		return *this;
	}

	~MyClass() {
		cout << "MyClass::~MyClass()" << endl;
	}
};

int main() {
	MyClass x;
	MyClass* xPtr = &x;
	MyClass& xRef = x;

	cout << "Is Value Type: " << __reference_type<decltype(x)>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(&x)>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(std::cref(x).get())>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(std::move(x))>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(std::move(xRef))>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(myMove(x))>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(myMove(xRef))>::type() << endl;
	cout << "Is Value Type: " << __reference_type<decltype(myMove(xPtr))>::type() << endl;
	return 0;
}
