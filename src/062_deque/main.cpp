#include "sld.hpp"

#include <deque>

#include "deque.hpp"
#include "deque_t.hpp"
#include "deque_sf.hpp"
#include "deque_tests.hpp"


int main () {

	try {

		deque_functional_test<Deque<std::string>> ();

		deque_copy_move_test<Deque<std::string>> ();

		deque_construct_test<Deque<vec>> ();

		deque_rundom_test<Deque<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//deque_speed_test<Deque<std::string>, DequeT<std::string>> (100000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//deque_speed_test<Deque<std::string>, DequeT<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//deque_speed_test<Deque<std::string>, DequeT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//deque_speed_test<Deque<std::string>, DequeT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}








