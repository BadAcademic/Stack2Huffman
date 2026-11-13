#include "sld.hpp"

#include "bin_tree_tests.hpp"
#include "bin_tree_sort.hpp"



int main () {

	try {


		tree_simple_visual_test<BinTreeSort<std::string>> ();

		tree_copy_move_test<BinTreeSort<std::string>> (); getchar ();

		tree_construct_test<BinTreeSort<vec>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//tree_speed_test<BinTreeSort<std::string>> (10000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//tree_speed_test<BinTreeSort<std::string>> (10000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//tree_speed_test<BinTreeSort<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//tree_speed_test<BinTreeSort<std::string>> (10000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));

		//tree_emplace_speed_test<BinTreeSort<stor>> (3000, 10);

		//tree_balance_speed_test<BinTreeSort<std::string>> (30000, 1);
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return (0);
}
