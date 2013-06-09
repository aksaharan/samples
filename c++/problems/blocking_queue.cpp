#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>

const size_t MAX_QUEUE_SIZE = 5;
std::queue<int> queue;
std::condition_variable fullQueueCV;
std::condition_variable emptyQueueCV;
std::mutex dataGuard;

template<typename T>
void push_back(const T& element) {
	std::unique_lock<std::mutex> g{dataGuard};
	fullQueueCV.wait(g, [] { return queue.size() < MAX_QUEUE_SIZE; } );

	queue.push(element);
	emptyQueueCV.notify_one();
	std::cout << "push_back -> " << queue.size() << std::endl;
}

template<typename T>
T pop_front() {
	std::unique_lock<std::mutex> g{dataGuard};

	std::cout << "pop_front before pop -> " << queue.size() << std::endl;
	emptyQueueCV.wait(g, [] { return !queue.empty(); } );

	T element = queue.front();
	queue.pop();
	fullQueueCV.notify_one();

	return element;
}

const int MAX_LOOP_COUNT = 50;
int main(void) {
	std::cout << "---- BlockingQueue Problem ----" << std::endl << std::endl;

	std::thread thread1([] {
		std::cout << "Producer thread: " << std::this_thread::get_id() << std::endl;
		for (int i = 0; i < MAX_LOOP_COUNT; ++i) {
			if (!(std::rand() % 5)) {
			std::this_thread::sleep_for(std::chrono::milliseconds{std::rand() % 1000});
			}
			push_back(std::rand() % 1000);
		}
	});

	std::thread thread2([] {
		std::cout << "Consumer thread: " << std::this_thread::get_id() << std::endl;
		for (int i = 0; i < MAX_LOOP_COUNT; ++i) {
			if (!(std::rand() % 2)) {
				std::this_thread::sleep_for(std::chrono::milliseconds{std::rand() % 1000});
			}
			pop_front<int>();
		}
	});

	thread1.join();
	thread2.join();
	return 0;
}
