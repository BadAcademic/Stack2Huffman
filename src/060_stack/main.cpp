#include "sld.hpp"

#include <stack>

#include "stack_t.hpp"
#include "stack.hpp"
#include "stack_tests.hpp"
#include "vec.hpp"


int main () {

	try {

		stack_functional_test<Stack<std::string>> ();

		stack_copy_move_test<Stack<std::string>> ();

		stack_construct_test<Stack<vec>> ();

		stack_rundom_test<Stack<std::string>> ();

		// to run the test comment #include "sld.hpp" and switch to Release mode
		//std::cout << "single big cycle - small pattern\n";
		//stack_speed_test<Stack<std::string>, StackT<std::string>> (100000000, 1, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//stack_speed_test<Stack<std::string>, StackT<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//stack_speed_test<Stack<std::string>, StackT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//stack_speed_test<Stack<std::string>, StackT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}
