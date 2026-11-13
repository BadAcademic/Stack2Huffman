//#include "sld.hpp"

#define _UNIREF_

#include <list>

#include "list.hpp"
#include "list_tests.hpp"
#include "vec.hpp"


int main () {

	try {


		list_functional_test<List<std::string>> ();

		list_copy_move_test<List<std::string>> (); getchar ();

		list_construct_test<List<vec>> ();

		list_rundom_test<List<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		std::cout << "single big cycle - small pattern\n";
		list_speed_test<List<std::string>> (100000000, 1, std::string (""));
		std::cout << "many small cycles - small pattern\n";
		list_speed_test<List<std::string>> (10000, 10000, std::string (""));
		std::cout << "single big cycle - big pattern\n";
		list_speed_test<List<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		std::cout << "many small cycles - big pattern\n";
		list_speed_test<List<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format("exception caught: {}\n", e.message());
	}

	return (0);
}
