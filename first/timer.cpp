#include <iostream>
#include <chrono>
#include <cmath>

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
	auto count = 0.;
	{
		Timer t;
		for (auto i = 0; i < 1'000'000; i++) {
			count += std::sin(i) + std::cos(i);
		}
	}

	std::cout << "After" << std::endl;
}

