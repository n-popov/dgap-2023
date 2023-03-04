#include <filesystem>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std::filesystem;

int main() {
	path current_dir(".");

	std::cout << "Available space: " << space(current_dir).available << std::endl;

	auto this_file = current_dir / "fs.cpp";

	std::cout << absolute(this_file) << std::endl;
	std::fstream fin(this_file, std::ios::in);

	std::copy(std::istream_iterator<char>(fin),std::istream_iterator<char>(), std::ostream_iterator<char>(std::cout, ""));

	auto copied_path = path("fs_copied.cpp");

	if (!exists(copied_path)) {
		copy(this_file, copied_path);
	}
	
	for(auto file: directory_iterator(current_dir)) {
		std::cout << "File path: " << absolute(file) << std::endl;
		std::cout << "File extension: " << file.path().extension() << std::endl; 
	}
	
	remove(copied_path);
}
