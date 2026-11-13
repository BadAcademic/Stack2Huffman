//#include "sld.hpp"

#include <stack>

#include "stack_t.hpp"
#include "stack_f.hpp"
#include "stack_tests.hpp"
#include "vec.hpp"

void construct_test ();


int main () {

	try {

		//stack_functional_test<StackF<std::string>> ();

		//construct_test ();

		//stack_rundom_test<StackF<std::string>> ();

		// to run the tests comment #include "sld.hpp" and switch to Release mode
		std::cout << "single big cycle - small pattern\n";
		stack_speed_test<StackF<std::string>, StackT<std::string>> (100000000, 3, std::string (""));
		//std::cout << "many small cycles - small pattern\n";
		//stack_speed_test<StackF<std::string>, StackT<std::string>> (100000, 1000, std::string (""));
		//std::cout << "single big cycle - big pattern\n";
		//stack_speed_test<StackF<std::string>, StackT<std::string>> (10000000, 1, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
		//std::cout << "many small cycles - big pattern\n";
		//stack_speed_test<StackF<std::string>, StackT<std::string>> (100000, 1000, std::string ("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"));
	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}

	return 0;
}


void construct_test () {
	{
		std::stack<vec> S;
		vec v{1, 2};
		S.push (v);
	}
	std::cout << "\n";
	{
		std::stack<vec> S;
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
		StackF<vec> S;
		vec v{1, 2};
		S.push (v);
	}
	std::cout << "\n";
	{
		StackF<vec> S;
		vec v{1, 2};
		S.push (v);
		S.push (v);
		S.push (v);
		S.pop ();
		S.pop ();
		S.pop ();
	}
}

