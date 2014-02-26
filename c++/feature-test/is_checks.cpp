#include <iostream>
#include <type_traits>

using namespace std;

struct PodStruct {
	int x;
} podStruct;

enum TestEnum {
};

class PodClass {
	int x;
};

int test_function(int, char, bool, char*, int*, double, unsigned long long, size_t, TestEnum, PodClass) {
	return 0;
}

template<typename T>
void printVariousTypes(const std::string& comment) {
	std::cout << "------- Testing for various conditions for - " << comment << endl;
	std::cout << "  is_void<T>: " << is_void<T>() << endl;
	std::cout << "  is_integral<T>: " << is_integral<T>() << endl;
	std::cout << "  is_pointer<T>: " << is_pointer<T>() << endl;
	std::cout << "  is_function<T>: " << is_function<T>() << endl;
	std::cout << "  is_class<T>: " << is_class<T>() << endl;
	std::cout << "  is_union<T>: " << is_union<T>() << endl;
	std::cout << "  is_enum<T>: " << is_enum<T>() << endl;
	std::cout << "  is_fundamental<T>: " << is_fundamental<T>() << endl;
	std::cout << "  is_object<T>: " << is_object<T>() << endl;
	std::cout << "  is_reference<T>: " << is_reference<T>() << endl;
	std::cout << "  is_pod<T>: " << is_pod<T>() << endl;
	std::cout << "  is_trivial<T>: " << is_trivial<T>() << endl;
	std::cout << "  is_polymorphic<T>: " << is_polymorphic<T>() << endl;
}


int main(void) {
	std::cout << "Testing various is_condition tests for C++11" << endl;
	printVariousTypes<decltype(test_function)>("Function");
	printVariousTypes<PodClass>("PodClass");
	printVariousTypes<TestEnum>("Enum");
	printVariousTypes<decltype(podStruct)>("PodStruct");
	return 0;
}
