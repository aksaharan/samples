#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

std::mutex m;
std::condition_variable cv;
bool isNotified = false;

void play_ping(long toggle_count) {

	long toggle = 0;
	while (toggle < toggle_count) {
		std::unique_lock<std::mutex> u(m);
		while (isNotified != true) {
			cv.wait(u);
		}

		std::cout << "Ping!" << std::endl;
		isNotified = false;

		u.unlock();
		cv.notify_all();
		++toggle;
	}
}

void play_pong(long toggle_count) {

	long toggle = 0;
	while (toggle < toggle_count) {
		std::unique_lock<std::mutex> u(m);
		while (isNotified != false) {
			cv.wait(u);
		}

		std::cout << "Pong!" << std::endl;
		isNotified = true;

		u.unlock();
		cv.notify_all();
		++toggle;
	}
}

int main() {
	long max_toggle = 5;

	std::cout << "Ready... Set... Go!" << std::endl;

	auto t1 = std::thread(play_ping, max_toggle);
	auto t2 = std::thread(play_pong, max_toggle);

	t1.join();
	t2.join();
	std::cout << "Done!" << std::endl;

	return 0;
}
