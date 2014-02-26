#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>

int main(void) {
	std::cout << "---- ThreadJoin Problem ----" << std::endl << std::endl;

	std::srand(std::time(NULL));

	std::thread threadList[10];
	for (long i = 0; i < sizeof(threadList); ++i) {
		std::cout << "Creating Thread [" << i << "]" << std::endl;
		threadList[i] = std::thread([i] {
			long sleepTime = std::rand() % 10;
			std::cout << "Thread [#: " << i << ", Id: " << std::this_thread::get_id() 
				<< ", Sleep: " << sleepTime << "]" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds{sleepTime});
			std::cout << "Completed Thread [#: " << i << ", Id: " << std::this_thread::get_id() 
				<< ", Sleep: " << sleepTime << "]" << std::endl;
		});
	}

	std::cout << "** Waiting to join on threads" << std::endl;
	for (long i = 0; i < sizeof(threadList); ++i) {
		threadList[i].join();
	}

	std::cout << "** Completed waiting to join on threads" << std::endl;
	return 0;
}
