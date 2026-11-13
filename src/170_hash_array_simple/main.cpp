#include "sld.hpp"

#include <string>
#include <fstream>
#include <iostream>

#include <set>
#include "hash_array_s.hpp"
#include "hash_array_tests.hpp"

void simple_visual_test ();


int main () {

	try {

		simple_visual_test ();

		//hash_array_int_speed_test<HashArrayS<int>> (10000000, 1);
		//hash_array_int_speed_test<HashArrayS<int>> (10000, 1000);
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}
}


void simple_visual_test () {

	const int n = 200;

	HashArrayS<int> HA{};

	for (int i{}; i < n; i++)
		HA.insert (i);

	HA.print ();
	std::cout << "\n";

	for (int i{}; i < n - 2; i++)
		HA.erase (i);

	HA.print ();
	std::cout << "\n";
}
