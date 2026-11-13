#include "sld.hpp"

#include <string>
#include <fstream>
#include <iostream>

#include <set>
#include <unordered_set>
#include "hash_array.hpp"
#include "hash_array_tests.hpp"

void simple_visual_test ();

void simple_hash_test ();


class p3d {
public:

	p3d (const double& a, const double& b, const double& c) : a (a), b (b), c (c) {};

	double a{};
	double b{};
	double c{};

	struct Hash {
		size_t operator() (const p3d& o) const {
			return 1;
		}
	};

	bool operator== (const p3d& o) const {

		if (a == o.a && b == o.b && c == o.c)
			return true;
		else
			return false;
	}
};

std::ostream& operator<< (std::ostream& out, const p3d& o) {

	out << "(" << o.a << "," << o.b << "," << o.c << ")";
	return out;
}

template <>
class std::hash<p3d> {
public:

	size_t operator() (const p3d& o) const {

		return 1;
	}
};


int main () {

	try {

		simple_hash_test ();

		hash_array_copy_move_test<HashArray<std::string>> ();

		hash_array_construct_test<HashArray<vec>> ();

		simple_visual_test ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//hash_array_speed_test<HashArray<std::string>> (100000000, 3, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//hash_array_speed_test<HashArray<std::string>> (10000, 10000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//hash_array_speed_test<HashArray<std::string>> (100000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//hash_array_speed_test<HashArray<std::string>> (10000, 10000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}
}


void simple_hash_test () {

	HashArray<p3d> HA{};

	HA.insert (p3d{1., 2., 3.});
	HA.insert (p3d{1., 3., 3.});
	HA.insert (p3d{1., 1., 3.});

	HA.print ();

	HashArray<int> HA1{};
}


void simple_visual_test () {

	const int n = 200;

	HashArray<int> HA{};

	for (int i{}; i < n; i++)
		HA.insert (i);

	HA.print ();
	std::cout << "\n";

	for (int i{}; i < n - 2; i++)
		HA.erase (i);

	HA.print ();
	std::cout << "\n";
}
