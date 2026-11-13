#include "sld.hpp"

#include <string>
#include <fstream>
#include <iostream>

#include <map>
#include "multimap.hpp"
#include "vec.hpp"

void simple_visual_test ();

void makeVocab (const char*, const char*);


int main () {

	try {

		simple_visual_test ();
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return 0;
}


void simple_visual_test () {

	Multimap<std::string, int> M{{"noun", 1}, {"sky", 2}, {"violin", 3}, {"table", 4}, {"window", 5}, {"queue", 6}, {"pillow", 7},
{"room", 8}, {"home", 9}, {"dream", 10}, {"key", 11}, {"bottom", 12},{"guest", 14}};

	M.insert ("jack", 15);
	M.insert ("lady", 16);
	M.insert ("noun", 17);
	M.insert ("sky", 18);
	M.insert ("violin", 19);

	Multimap<std::string, int> M1{M};
	Multimap<std::string, int> M2{std::move (M1)};
	Multimap<std::string, int> M3;
	M3 = M2;
	Multimap<std::string, int> M4;
	M4 = std::move (M3);

	auto it1 = M.begin ();
	auto it2 = M4.begin ();
	while (it1 != M.end () && it2 != M4.end ()) {
		if (*it1 != *it2)
			std::cout << "Error\n";
		++it1;
		++it2;
	}

	for (auto& e : M4)
		std::cout << e << "\n";
	std::cout << "\n";

	M4.pprint (true, true);

	{
		Multimap<std::string, vec> M5;
		M5.insert ("apple", vec{3,4});
	}
	std::cout << "\n";
	{
		std::multimap<std::string, vec> S;
		S.insert (std::make_pair ("apple", vec{3,4}));
	}
	std::cout << "\n";
	std::cout << "\n";
	{
		Multimap<std::string, vec> M5;
		M5.emplace ("apple", vec{3, 4});
	}
	std::cout << "\n";
	{
		std::multimap<std::string, vec> S;
		S.emplace ("apple", vec{3, 4});
	}
}

