#include "sld.hpp"

#include <queue>

#include "queue_t.hpp"
#include "queue.hpp"
#include "queue_tests.hpp"
#include "vec.hpp"


int main () {

	try {

		queue_functional_test<Queue<std::string>> ();

		queue_copy_move_test<Queue<std::string>> ();
		
		queue_construct_test<Queue<vec>> ();

		queue_rundom_test<Queue<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//queue_speed_test<Queue<std::string>, QueueT<std::string>> (100000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//queue_speed_test<Queue<std::string>, QueueT<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//queue_speed_test<Queue<std::string>, QueueT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//queue_speed_test<Queue<std::string>, QueueT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}
