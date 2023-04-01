#include <boost/asio.hpp>
#include <iostream>

int main() {
	auto port = 65001u;
	std::string ip = "127.0.0.1";

	boost::asio::ip::tcp::endpoint e(
			boost::asio::ip::address::from_string(ip), port);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket s(io_service, e.protocol());

	s.connect(e);
	std::string message = "Connected!"; 
	for (
		boost::asio::write(s, boost::asio::buffer(message + "\n"));
		std::getline(std::cin, message);
		boost::asio::write(s, boost::asio::buffer(message + "\n"))
	); 
	
	boost::asio::write(s, boost::asio::buffer("EXIT\n"));
}
