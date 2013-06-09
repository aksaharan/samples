#include <future>
#include <iostream>
#include <thread>

long fibonacci_async(long num) {
	std::cout << "Called fibonacci_async [" << num << "] => " << std::this_thread::get_id()  << std::endl;
	if (num <= 0) {
		return 0;
	} else if (num <= 2) {
		return num;
	}

	auto handle = std::async(std::launch::async, fibonacci_async, num - 1);
	long num_2 = fibonacci_async(num - 2);
	return handle.get() + num_2;
}

int main() {
	long input_num = 10;
	std::cout << "Computing Fibonacci for : " << input_num << std::endl;

	long fib_value = fibonacci_async(input_num);
	std::cout << "Computed Fibonacci [" << input_num << "] => " << fib_value << std::endl;

	return 0;
}
