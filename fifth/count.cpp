#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <mutex>
#include <atomic>

const size_t SEQUENTIAL_SIZE = 1000u;
std::mutex count_mutex;

template<typename Iterator, typename T>
void count_block(Iterator first, Iterator last, T value, int&count) {
	auto result = std::count(first, last, value);
	{
		std::lock_guard guard(count_mutex);
		count += result;
	}
}

template<typename Iterator, typename T>
void inefficient_count_block(Iterator first, Iterator last, T value, int& count) {
	for(auto it = first; it != last;
			std::lock_guard(count_mutex), count += (*it++ == value));
}

template<typename Iterator, typename T>
void unsafe_count_block(Iterator first, Iterator last, T value, std::atomic<int>& count) {
	for(auto it = first; it != last; count += (*it++ == value));
}

template<typename Iterator, typename T>
int parallel_count(Iterator first, Iterator last, T value) {
	auto size = std::distance(first, last);
	std::atomic<int> result(0);
	if (size <= SEQUENTIAL_SIZE) {
		unsafe_count_block(first, last, value, result);
		return result;
	}

	auto num_threads = std::thread::hardware_concurrency();
	auto block_size = size / num_threads;
	std::vector<std::thread> threads;
	for (auto i = 0u; i + 1 < num_threads; i++) {
		threads.emplace_back(
			unsafe_count_block<Iterator, T>,
			std::next(first, block_size * i),
			std::next(first, block_size * (i + 1)),
			value,
			std::ref(result)
		);
	}
	unsafe_count_block(std::next(first, block_size * (num_threads - 1)),
				last, value, result);
	for(auto& thread: threads) {
		thread.join();
	}
	return result;
}

int main() {
	std::vector<int> test_values(10000u);
	std::iota(std::begin(test_values), std::end(test_values), 0);
	for(auto& value : test_values) {
		value %= 2;
	}

	std::cout << parallel_count(std::begin(test_values), std::end(test_values), 0)<< std::endl;

}
	
