#include <iostream>
#include <cstring>

/*
	Depending on behaviour of empty string, we culd be treating it either as nullptr
	or an null terminated 0 length string.

	Here for this example, we are considering and empty string to be a nullptr
	representation
*/
class my_string {
public:
	my_string()
		: m_pString(nullptr), m_capacity(0), m_length(0) {
	}

	// Copy constructor
	my_string(const my_string& str)
		: m_pString(nullptr), m_capacity(0), m_length(0) {
		if (str.m_length <= 0) {
			// Default initialization is good enough
			return;
		}

		m_length = str.m_length;
		m_capacity = str.m_capacity;
		m_pString = new char[m_capacity];
		std::strcpy(m_pString, str.m_pString);
	}

	// Constructor to construct from a raw char string, this assumes the string being passed ie 
	// either valid or nullptr
	my_string(const char* pStr)
		: m_pString(nullptr), m_capacity(0), m_length(0) {
		if (!pStr) {
			// Default initialization is good enough
			return;
		}

		// Assumes valid string on which c-string functions work correctly
		m_length = std::strlen(pStr);
		m_capacity = m_length + 1;
		m_pString = new char[m_capacity];
		std::strcpy(m_pString, pStr);
	}

	// We could be implementing a move constructor as well if needed

	// Destructor
	~my_string() {
		delete[] m_pString;
		m_pString = nullptr;
		m_capacity = m_length = 0;
	}

	// Additionally can also have operator =(const char* pStr) with 
	// similar logic
	my_string& operator =(const my_string& str) {
		// Check if this is the same object
		if (this == &str) {
			return *this;
		}

		if (str.m_length <= 0) {
			m_length = 0;
			m_capacity = 0;
			delete[] m_pString;
			m_pString = nullptr;
		} else if (m_capacity > (str.m_length + 1)) {
			// No allocation needed
			m_length = str.m_length;
			strcpy(m_pString, str.m_pString);
		} else {
			// Make appropriate allocation to accomodate for the string
			// Make the object strong exception safe
			char* pTemp = new char[str.m_length + 1];
			char* pPrev = m_pString;

			strcpy(pTemp, str.m_pString);
			m_length = str.m_length;
			m_capacity = str.m_length + 1;
			m_pString = pTemp;
			delete[] pPrev;
		}

		return *this;
	}

	inline bool empty() const {
		return m_length == 0;
	}

	inline size_t size() const {
		return m_length;
	}

	inline size_t capacity() const {
		return m_capacity;
	}

private:
	char* m_pString;
	size_t m_capacity;

	// Length is an invariants of this class and always need to be consistent 
	// with the contants of pString
	size_t m_length;

friend std::ostream& operator <<(std::ostream& out, const my_string& str);
};

std::ostream& operator <<(std::ostream& out, const my_string& str) {
	if (str.m_length > 0) {
		out << str.m_pString;
	}
	return out;
}

int main(void) {
	std::cout << "---- my_string Problem ----" << std::endl << std::endl;

	my_string str;
	my_string strHelloWorld("Hello World");
	my_string strHelloWorldCC(strHelloWorld);
	std::cout << "my_string() = " << str.capacity() << ":" << str.size() << ": " << str << std::endl;
	std::cout << "my_string(const my_string&) = " << strHelloWorldCC.capacity() << ":" << strHelloWorldCC.size() 
		<< ": " << strHelloWorldCC << std::endl;
	std::cout << "my_string(const char*) = " << strHelloWorld.capacity() << ":" << strHelloWorld.size() 
		<< ": " << strHelloWorld << std::endl;

	my_string str1 = "Yet Another Hello World";
	str = str1;
	std::cout << "my_string operator=(const my_string) = " << str.capacity() << ":" << str.size() << ": " << str << std::endl;

	str = "Test Again";
	std::cout << "my_string operator=(const my_string) = " << str.capacity() << ":" << str.size() << ": " << str << std::endl;

	return 0;
}
