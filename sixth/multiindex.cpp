#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <iostream>

struct Record {
	Record(std::string name, std::string number):
		name(std::move(name)),
		number(std::move(number)) {}

	std::string name, number;

	struct RandomAccess {};
	struct Hashed {};
	struct Ordered {};
};

std::ostream& operator<<(std::ostream& os, Record record) {
	return os << record.name << ": " << record.number;
}

class Catalogue {
public:
	void add(const Record& r) {
		data.insert(r);
	}

	Record operator[](size_t index) {
		return data.get<Record::RandomAccess>()[index];
	}

	Record find(const std::string& number) {
		return *data.get<Record::Hashed>().find(number);
	}

	auto get_ordered() {
		auto& ordered = data.get<Record::Ordered>();
		return std::make_pair(ordered.begin(), ordered.end());
	}

private:
	boost::multi_index::multi_index_container<
		Record, boost::multi_index::indexed_by<
	       		boost::multi_index::ordered_non_unique<
				boost::multi_index::tag<Record::Ordered>,
				boost::multi_index::member<Record, std::string, &Record::name>
			>,
			boost::multi_index::hashed_unique<
				boost::multi_index::tag<Record::Hashed>,
				boost::multi_index::member<Record, std::string, &Record::number>
			>,
			boost::multi_index::random_access<
				boost::multi_index::tag<Record::RandomAccess>
			>
		>
	> data;
	
};

int main() {
	Record first("Niki", "555");
	Record second("Stepan", "422");
	Record third("Rector Kudriavtsev", "777");

	Catalogue catalogue;
	catalogue.add(first);
	catalogue.add(second);
	catalogue.add(third);
	
	std::cout << catalogue.find("422") << std::endl;
	std::cout << catalogue[0] << std::endl;

	auto [begin, end] = catalogue.get_ordered();

	std::copy(begin, end,
		std::ostream_iterator<Record>(std::cout, "\n"));

}
