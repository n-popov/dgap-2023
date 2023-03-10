#include <iostream>
#include <random>
#include <future>
#include <thread>

class MonteCarlo {
public:
	MonteCarlo(): rd(), d(0, 1), gen(rd()) {}
	
	double pi(unsigned amount) {
		auto amount_inside = 0u;
		for (auto i = 0u; i < amount; i++) {
			amount_inside += (std::pow(d(gen), 2) + std::pow(d(gen), 2) <= 1);
		}
		return 4. * amount_inside / amount;
	}

private:
	std::random_device rd;
	std::uniform_real_distribution<double> d;
	std::mt19937 gen;
};	

int main() {
	std::vector<std::future<double>> futures;
	auto num_threads = std::thread::hardware_concurrency();
	MonteCarlo pi_generator;

	for(auto i = 0u; i + 1 < num_threads; i++) {
		futures.push_back(std::async(std::launch::async, &MonteCarlo::pi,
			&pi_generator, 10000000));
	}
	std::cout << "Pi is " << std::accumulate(std::begin(futures), std::end(futures), pi_generator.pi(10000000), [](auto acc, auto& value){return acc + value.get();}) / num_threads << std::endl;
}
