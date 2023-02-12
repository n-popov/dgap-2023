#include <vector>
#include <array>
#include <deque>
#include <list>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>

class Timer {
public:
	Timer(): start(std::chrono::steady_clock::now()) {}

	~Timer() {
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
	}
private:
	std::chrono::steady_clock::time_point start;
};

int main() {
	std::array<int, 5> arr;
	arr[2] = 42;
	
	for (auto item: arr) {
		std::cout << item << ' ';
	}

	std::vector<int> vector;
	std::deque<int> deque;

	{
		Timer t;
		for (auto i = 0; i < 1'000; i++) {
			vector.insert(std::begin(vector), i);
		}
	}

	{
		Timer t;
		for (auto i = 0; i < 1'000; i++) {
			deque.push_back(i);
		}
	}

	std::random_device d;
	std::mt19937_64 mt(d());
	std::uniform_int_distribution<int> distribution(1, 1000);
	
	std::vector<int> v;
	std::list<int> list;

	for(auto i = 0; i < 100'000; i++) {
		auto random_element = distribution(mt);
		v.push_back(random_element);
		list.push_back(random_element);
	}

	std::cout << "Vector:" << std::endl;
	{
		Timer t;
		std::sort(std::begin(v), std::end(v));
	}

	std::cout << "List:" << std::endl;
	{
		Timer t;
		list.sort();
	}
}
