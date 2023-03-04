#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace nlohmann;

int main() {
	json object = json::parse(std::fstream("price.json", std::ios::in));
	std::cout << object.dump(4) << std::endl;
}
