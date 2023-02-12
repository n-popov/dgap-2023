#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

#define ever (;;)
#define range(container) std::begin(container), std::end(container)

std::ostream& operator<<(std::ostream& os, std::vector<int> v) {
	std::copy(range(v), std::ostream_iterator<int>(os, " "));
	return os;
}

std::istream& operator>>(std::istream& is, std::vector<int>& v) {
	std::copy(std::istream_iterator<int>(is), std::istream_iterator<int>(), std::back_inserter(v));
	return is;
}

int main() {
	std::vector<int> array;
	
	std::cin >> array;

	std::cout << array << std::endl;

	std::vector<int> other;

	std::reverse_copy(std::begin(array), std::end(array), std::back_inserter(other));

	std::cout << other << std::endl;

	std::vector<int> squares;

	std::transform(std::begin(array), std::end(array), std::back_inserter(squares), [](auto item){
			return item * item;
			});

	std::cout << squares << std::endl;
	
	auto remove_from = std::remove_if(range(squares), [](auto item){return !(item % 2);});
	squares.erase(remove_from, std::end(squares));
	std::cout << squares << std::endl;

	std::cout << "Product of filtered squares: " << std::accumulate(range(squares), 1llu, [](auto lhs, auto rhs){return lhs * rhs;}) << std::endl;
}
