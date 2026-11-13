#include "sld.hpp"

#include <deque>

#include "deque_t.hpp"
#include "deque_tests.hpp"
	

int main () {

	try {

		deque_functional_test<DequeT<std::string>> ();

		deque_rundom_test<DequeT<std::string>> ();
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}
