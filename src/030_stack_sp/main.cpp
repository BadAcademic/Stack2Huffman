//#include "sld.hpp"

#include <stack>

#include "stack_t.hpp"
#include "stack_sp.hpp"
#include "stack_tests.hpp"


int main () {

	try {

		stack_functional_test<StackSP<std::string>> ();

		stack_rundom_test<StackSP<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		std::cout << "single big cycle - small pattern\n";
		stack_speed_test<StackSP<std::string>, StackT<std::string>> (100000000, 1, std::string (""));
		std::cout << "many small cycles - small pattern\n";
		stack_speed_test<StackSP<std::string>, StackT<std::string>> (100000, 1000, std::string (""));
		std::cout << "single big cycle - big pattern\n";
		stack_speed_test<StackSP<std::string>, StackT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		std::cout << "many small cycles - big pattern\n";
		stack_speed_test<StackSP<std::string>, StackT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}
