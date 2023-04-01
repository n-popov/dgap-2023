#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;

std::mutex m1, m2;

void lock_mutexes_first() {
	m1.lock();
	std::cout << "Working with resource #1" << std::endl;
	std::this_thread::sleep_for(seconds(1));

	m2.lock();
	std::cout << "Working with resource #2" << std::endl;
	m2.unlock();
	m1.unlock();
}

void lock_mutexes_second() {
	m2.lock();
	std::cout << "Working with resoutce #2" << std::endl;
	std::this_thread::sleep_for(seconds(1));

	m1.lock();
	std::cout << "Working with resource #1" << std::endl;
	m1.unlock();
	m2.unlock();
}

int main() {
	std::thread t1(lock_mutexes_first);
	std::thread t2(lock_mutexes_second);

	t1.join();
	t2.join();
}
	

