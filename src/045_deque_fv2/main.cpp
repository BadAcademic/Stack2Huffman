#include "sld.hpp"

#include <deque>

#include "deque_t.hpp"
#include "deque_fv2.hpp"
#include "deque_tests.hpp"
#include "vec.hpp"

void construct_test ();


int main () {

	try {

		deque_functional_test<DequeFv2<std::string>> ();

		construct_test ();

		deque_rundom_test<DequeFv2<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//deque_speed_test<DequeFv2<std::string>, DequeT<std::string>> (100000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//deque_speed_test<DequeFv2<std::string>, DequeT<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//deque_speed_test<DequeFv2<std::string>, DequeT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//deque_speed_test<DequeFv2<std::string>, DequeT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}


void construct_test () {
	{
		std::deque<vec> S;
		vec v{1, 2};
		S.push_back (v);
	}
	std::cout << "\n";
	{
		std::deque<vec> S;
		S.push_back (vec{1, 2});
	}
	std::cout << "\n";
	{
		DequeFv2<vec> S{};
		vec v{1, 2};
		S.push_back (v);
	}
	std::cout << "\n";
	{
		DequeFv2<vec> S;
		S.push_back (vec{1, 2});
	}
	std::cout << "\n";
}
