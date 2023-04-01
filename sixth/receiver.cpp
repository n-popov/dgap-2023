#include <iostream>

#include <boost/asio.hpp>


bool read(boost::asio::ip::tcp::socket& s, std::string& message) {
	boost::asio::streambuf buffer;

	boost::asio::read_until(s, buffer, '\n');

	std::istream stream(&buffer);

	std::getline(stream, message);
	return message != "EXIT";
}

int main() {
	auto port = 65001u;
	std::string ip = "127.0.0.1";

	boost::asio::ip::tcp::endpoint e(boost::asio::ip::address::from_string(ip), port);

	boost::asio::io_service serv;

	boost::asio::ip::tcp::acceptor a(serv, e.protocol());
	a.bind(e);
	a.listen();

	boost::asio::ip::tcp::socket s(serv);
	a.accept(s);

	std::string message;

	while (read(s, message)) {
		std::cout << message << std::endl;
	}
}
