#include <format>
#include <iostream>

#include "vec.hpp"

void initialization();
void copy_move();
void placement();


int main()
{
	try {

		initialization();
		placement();
		copy_move();
	}
	catch (gexception& e) {

		std::cerr << std::format("exception caught: {}\n", e.message());
	}

	return (0);
}


void initialization() {

	{ vec a; }
	{ vec a{}; } // preferable
	{ vec a(); } // does not initialize an object; it declares a function that takes no arguments and returns vec	
	{ vec a = vec(); }
	{ vec a = vec{}; }
	std::cout << "\n";

	{ vec* a = new vec;	delete a; } // preferable
	{ vec* a = new vec[2]; delete[] a; } // preferable
	{ vec* a = new vec(); delete a; }
	{ vec* a = new vec[2](); delete[] a; }
	{ vec* a = new vec{}; delete a; }
	{ vec* a = new vec[2]{}; delete[] a; }
	std::cout << "\n";

	{
		char* ra = new char[2 * sizeof(vec)];
		vec* a1 = new (ra) vec;
		vec* a2 = new (ra + sizeof(vec)) vec; // vec* a2 = new (a1 + 1) vec;
		a1->~vec();
		a2->~vec();
		delete[] ra;
	}
	std::cout << "\n";

	{
		char* ra = new char[2 * sizeof(vec)];
		vec* a1 = new (ra) vec[2];
		a1->~vec();
		(a1+1)->~vec();
		delete[] ra;
	}
	std::cout << "\n";

	{ vec a(1, 2); } // if vec has constuctor with parameters
	{ vec a{1, 2}; } // if vec is aggregate
	{ vec a = vec(1, 2); }
	{ vec a = vec{1, 2}; }
	std::cout << "\n";

	{ vec* a = new vec(vec(1,2)); delete a; }
	{ vec* a = new vec(vec{1, 2}); delete a; }
	std::cout << "\n";

	{ vec&& a = vec(); }
	{ vec&& a = vec{}; }
	{ vec&& a = vec(1, 2); }
	{ vec&& a = vec{1, 2}; }
	std::cout << "\n";

	{ 
		vec a{1, 2};
		vec b(a);
		vec c{a};
		vec d = a;
	}
	std::cout << "\n";

	{
		vec a{1, 2};
		vec b{std::move(a)};
	}
	std::cout << "\n";
}


void placement() {

	constexpr int n = 3;
	char* rawVec = new char[n * sizeof(vec)];

	vec* Vec = reinterpret_cast<vec*>(rawVec);
	for (int i{}; i < n; i++)
		new (Vec + i) vec{2 * i + 1, 2 * i + 2};

	char* newRawVec = new char[n * sizeof(vec)];
	memcpy(newRawVec, rawVec, n * sizeof(vec));
	delete[] rawVec;

	Vec = reinterpret_cast<vec*>(newRawVec);

	vec a{Vec[0]};

	for (int i{}; i < n; i++) 
		Vec[i].~vec();

	delete[] newRawVec;
}


void f_by_value(vec a) {};
void f_by_lvalue(vec& a) {};
void f_by_rvalue(vec&& a) {};

void f_by_rvalue_to_local(vec&& a) {

	vec c{std::move(a)};
};

template<typename T>
void f_t(T&&);


void copy_move() {

	{
		vec a{1, 2};
		vec b;
		b = a;
	}
	std::cout << "\n";

	{
		vec a{1, 2};
		vec b;
		b = std::move(a);
	}
	std::cout << "\n";

	{
		vec a{1,2};
		f_by_value(a);
		f_by_lvalue(a);

		f_by_rvalue(std::move(a));
		f_by_rvalue(vec{3, 4});
	}
	std::cout << "\n";

	{
		vec a{1,2};
		f_by_rvalue_to_local(std::move(a));
	}
	std::cout << "\n";

	{
		f_by_rvalue_to_local(vec{3, 4});
	}
	std::cout << "\n";

	{
		vec o{1,2};
		vec a{1,2};
		vec&& b = vec{3,4};

		vec c{std::forward<decltype(a)>(a)};
		vec d{std::forward<decltype(b)>(b)};
	}
}
