#include "sld.hpp"

#include <vector>

#include "vector.hpp"
#include "vector_tests.hpp"
#include "vec.hpp"


int main () {

	try {

		vector_functional_test<Vector<int>> ();

		vector_copy_move_test<Vector<std::string>> ();

		vector_construct_test<Vector<vec>> ();
		std::cout << "Prees Enter to continue"; getchar ();

		vector_rundom_test<Vector<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//vector_speed_test<Vector<std::string>> (100000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//vector_speed_test<Vector<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//vector_speed_test<Vector<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//vector_speed_test<Vector<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return (0);
}
