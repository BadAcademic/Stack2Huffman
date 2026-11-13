#include <string>
#include <iostream>

#include "pair.hpp"
#include "vec.hpp"


int main ()
{
	{
		vec a{1,2};
		Pair<std::string, vec> b{"apple", a};
	}
	std::cout << "\n";
	{
		vec a{1,2};
		std::pair<std::string, vec> b{"apple", a};
	}
	std::cout << "\n\n";
	{
		Pair<std::string, vec> a{"apple", vec{1,2}};
	}
	std::cout << "\n";
	{
		std::pair<std::string, vec> a{"apple", vec{1,2}};
	}
	std::cout << "\n\n";
	{
		Pair<std::string, vec> a;
		Pair<std::string, vec> b{"cat", vec{1,2}};
		a = b;
	}
	std::cout << "\n";
	{
		std::pair<std::string, vec> a;
		std::pair<std::string, vec> b{"cat", vec{1,2}};
		a = b;
	}
	std::cout << "\n\n";
	{
		Pair<std::string, vec> a;
		Pair<std::string, vec> b{"cat", vec{1,2}};
		a = std::move(b);
	}
	std::cout << "\n";
	{
		std::pair<std::string, vec> a;
		std::pair<std::string, vec> b{"cat", vec{1,2}};
		a = std::move (b);
	}
	std::cout << "\n\n";
	{
		Pair<std::string, std::string> b{"apple", "sky"};
		std::cout << b << "\n";
		std::cout << std::format ("{}\n", b);

	}
	std::cout << "\n";
	{
		Pair<std::string, int> a ("apple", 2);
		Pair<std::string, int> b ("bottom", 3);
		Pair<std::string, int> c ("apple", 1);


		std::cout << (a < a) << "\n";
		std::cout << (a < b) << "\n";
		std::cout << (a < c) << "\n";
		std::cout << (a == a) << "\n";
		std::cout << (a != b) << "\n";
		std::cout << (a == c) << "\n";
	}
}
