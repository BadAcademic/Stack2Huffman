#include "sld.hpp"

#include "bin_tree_tests.hpp"
#include "priority_queue.hpp"

template <typename T>
void priority_queue_simple_visual_test ();


int main () {

	try {


		priority_queue_simple_visual_test<PriorityQueue<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		std::cout << "single big cycle - small pattern\n";
		priority_queue_speed_test<PriorityQueue<std::string>> (10000000, 1, std::string (""));
		std::cout << "many small cycles - small pattern\n";
		priority_queue_speed_test<PriorityQueue<std::string>> (10000, 1000, std::string (""));
		std::cout << "single big cycle - big pattern\n";
		priority_queue_speed_test<PriorityQueue<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		std::cout << "many small cycles - big pattern\n";
		priority_queue_speed_test<PriorityQueue<std::string>> (10000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return (0);
}


template <typename T>
void priority_queue_simple_visual_test () {

	std::initializer_list<std::string> L{
		"noun", "sky", "violin", "table", "window", "queue", "pillow", "room",
		"home", "dream", "key", "bottom", "guest", "jack", "lady", "table",
		"window", "queue", "pillow"
	};

	std::cout << "Input sequence:\n";
	for (auto& e : L)
		std::cout << e << " ";
	std::cout << "\n\n";

	T PQ{L};
	std::cout << "Output sequence:\n";
	for (auto& w : PQ)
		std::cout << w << " ";
	std::cout << "\n\n";

	PQ.pprint (true, true);
	std::cout << "\n";


}