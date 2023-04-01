#include <boost/multi_array.hpp>
#include <iostream>
#include <vector>

int main() {
	std::vector<int> initial_shape{2, 2, 3};

	auto array = boost::multi_array<double, 3>(initial_shape);
	array[0][1][2] = 42;
	array[1][0][0] = 57;

	for (auto i = 0; i < initial_shape[0]; i++) {
		for (auto j = 0; j < initial_shape[1]; j++) {
			for (auto k = 0; k < initial_shape[2]; k++) {
				std::cout << array[i][j][k] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<int> new_shape{3, 3, 3};

	array.resize(new_shape);

	auto shape = array.shape();

	for (auto i = 0; i < shape[0]; i++) {
		for (auto j = 0; j < shape[1]; j++) {
			for (auto k = 0; k < shape[2]; k++) {
				std::cout << array[i][j][k] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

