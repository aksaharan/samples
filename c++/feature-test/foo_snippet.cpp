#include <iostream>
#include <set>

class Foo {
	public:
		const Foo& operator() (int intValue, const char* strValue) const {
			// Some operation on these values
			std::cout << "Values [Int: " << intValue << ", Str: " << (strValue ? strValue : "") << "]" << std::endl;

			// Return itself so the operations can be chained on it
			return *this;
		}
};

int main(void) {
	std::cout << "---- FooSnippet Problem ----" << std::endl << std::endl;

	Foo zz;

	// Write Foo class completion to have following operation working on it.
	zz(5, "Moe")(0, nullptr)(7, "Larry")(3, "Curly")(32767, "Bubba");

	return 0;
}
