#include "sld.hpp"

#include "bin_tree_tests.hpp"
#include "red_black_tree_multi.hpp"


int main () {

	try {


		tree_simple_visual_test<RedBlackTreeMulti<std::string>> ();

		tree_multi_rundom_test<RedBlackTreeMulti<std::string>> ();

		tree_multi_copy_move_test<RedBlackTreeMulti<std::string>> ();//getchar ();

		tree_multi_construct_test<RedBlackTreeMulti<vec>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//tree_multi_speed_test<RedBlackTreeMulti<std::string>> (10000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//tree_multi_speed_test<RedBlackTreeMulti<std::string>> (10000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//tree_multi_speed_test<RedBlackTreeMulti<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//tree_multi_speed_test<RedBlackTreeMulti<std::string>> (10000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));

		//tree_multi_emplace_speed_test<RedBlackTreeMulti<stor>> (3000, 10);

		//tree_multi_balance_speed_test<RedBlackTreeMulti<std::string>> (30000, 1);
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return (0);
}
