#include "sld.hpp"

#include "bin_tree_tests.hpp"
#include "set.hpp"


int main () {

	try {

		tree_simple_visual_test<Set<std::string>> ();

		tree_rundom_test<Set<std::string>> ();

		tree_copy_move_test<Set<std::string>> ();//getchar ();

		tree_construct_test<Set<vec>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//tree_speed_test<Set<std::string>> (10000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//tree_speed_test<Set<std::string>> (10000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//tree_speed_test<Set<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//tree_speed_test<Set<std::string>> (10000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));

		//tree_emplace_speed_test<Set<stor>> (3000, 10);

		//tree_balance_speed_test<Set<std::string>> (30000, 1);
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return (0);
}