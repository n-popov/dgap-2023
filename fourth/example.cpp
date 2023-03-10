#include <iostream>
#include <thread>
#include <future>

void print_word(const std::string& word) {
	std::cout << word << std::endl;
}

int main() {
	std::thread other(print_word, "OTHER");
	print_word("MAIN");
	other.join();

}

