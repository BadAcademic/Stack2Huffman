#include "sld.hpp"

#include <queue>

#include "queue_t.hpp"
#include "queue_f.hpp"
#include "queue_tests.hpp"
#include "vec.hpp"

void construct_test ();


int main () {

	try {

		queue_functional_test<QueueF<std::string>> ();

		construct_test ();

		queue_rundom_test<QueueF<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//queue_speed_test<QueueF<std::string>, QueueT<std::string>> (100000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//queue_speed_test<QueueF<std::string>, QueueT<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//queue_speed_test<QueueF<std::string>, QueueT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//queue_speed_test<QueueF<std::string>, QueueT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}


void construct_test () {
	{
		std::queue<vec> S;
		vec v{1, 2};
		S.push (v);
	}
	std::cout << "\n";
	{
		std::queue<vec> S;
		vec v{1, 2};
		S.push (v);
		S.push (v);
		S.push (v);
		S.pop ();
		S.pop ();
		S.pop ();
	}
	std::cout << "\n";
	{
		std::queue<vec> S;
		S.push (vec{1, 2});
	}
	std::cout << "\n";
	{
		QueueF<vec> S{};
		vec v{1, 2};
		S.push (v);
	}
	std::cout << "\n";
}
