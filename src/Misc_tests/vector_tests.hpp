#include <string>
#include <vector>
#include <chrono>
#include <format>
#include <numbers>
#include <iostream>

#include "vec.hpp"


template<typename T>
void vector_functional_test ();

template<typename T>
void vector_copy_move_test ();

template<typename T>
void vector_rundom_test ();

template<typename T>
void vector_construct_test ();

template<typename T>
void vector_speed_test (const uint64_t, const uint32_t, const std::string&);


template<typename T>
void vector_functional_test () {

	std::cout << "Functional test\n\n";

	T L{};

	const int n{20};
	std::cout << "back input sequence: ";
	for (int i{}; i < n; i++) {
		L.push_back (i);
		std::cout << i << " ";
	}
	std::cout << "\nsize: " << L.size ();

	std::cout << "\nback output sequence: ";
	while (!L.empty ()) {
		std::cout << L.back () << " ";
		L.pop_back ();
	}
	std::cout << "\n\n";
}


template<typename T, typename U>
bool identity_test (T& a, U& b) {

	if (a.size () != b.size ())
		return false;
	auto ita = a.begin ();
	auto itb = b.begin ();
	for (int i{}; i < a.size (); i++) {
		if (*ita != *itb)
			return false;
	}
	return true;
}


template<typename T>
void vector_copy_move_test () {

	std::cout << "Copy & move test\n\n";

	std::initializer_list<std::string>d{"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y",
	"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y",
	"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y",
	"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y",
	"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y",
	"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y",
	"a","b","c","d","e","f","g","i","j","k","l","m","n","p","r","s","t","v","w","y"};
	std::string er{"error"};
	std::string su{"success"};

	{
		std::cout << "copy constructor: ";
		T L{d};
		T L1{L};
		std::vector<std::string> S{d};
		if (!identity_test (L1, S))
			std::cout << er;
		else
			std::cout << su;
	}
	std::cout << "\n";

	{
		std::cout << "move constructor: ";
		T L{d};
		T L1{std::move (L)};
		std::vector<std::string> S{d};
		if (!identity_test (L1, S))
			std::cout << er;
		else
			std::cout << su;
	}
	std::cout << "\n";

	{
		std::cout << "copy assignment: ";
		T L{d};
		T L1;
		L1 = L;
		std::vector<std::string> S{d};
		if (!identity_test (L1, S))
			std::cout << er;
		else
			std::cout << su;
	}
	std::cout << "\n";

	{
		std::cout << "move assignment: ";
		T L{d};
		T L1;
		L1 = std::move (L);
		std::vector<std::string> S{d};
		if (!identity_test (L1, S))
			std::cout << er;
		else
			std::cout << su;
	}
	std::cout << "\n\n";
}

template<typename T>
void vector_rundom_test () {

	std::cout << "Random test\n\n";

	const int eventsPerCycle = 1000;
	const int cycles = 10;
	const int height = 30;

	T L{};
	std::vector<std::string> S{};

	int maxSize{};
	int nPush{};
	int nPop[]{0,0};

	bool error = false;
	srand (time (NULL));
	int n = eventsPerCycle * cycles;
	for (int k{}; k < n; k++) {

		int m1 = (int)(height * (sin (k * 2 * std::numbers::pi / eventsPerCycle) + 1) / 2.);
		int m2 = (int)(height * (1 - sin (k * 2 * std::numbers::pi / eventsPerCycle)) / 2.);
		int n_push = rand () % (m1 + 1);
		int n_pop = rand () % (m2 + 1);


		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string (rand ());
			L.push_back (item);
			S.push_back (item);
			nPush++;
		}
		for (int i{}; i < n_pop; i++) {
			if (!L.empty ())
				nPop[0]++;
			else
				nPop[1]++;
			L.pop_back ();
			if (!S.empty ())
				S.pop_back ();
		}

		if (L.size () > maxSize)
			maxSize = L.size ();

		if (L.size () != 0 && S.size () != 0) {
			if (L.front () != S.front ()) {
				std::cout << std::format ("ERROR: front {} != {}\n", L.front (), S.front ());
				error = true;
			}
		}
		else {
			if (L.size () != S.size ()) {
				std::cout << std::format ("ERROR: size {} != {}\n", L.size (), S.size ());
				error = true;
			}
		}
	}
	if (error == false)
		std::cout << "Success !!!\n";

	std::cout << std::format ("Max size: {}\n", maxSize);
	std::cout << std::format ("Inserts: {}\n", nPush);
	std::cout << std::format ("Removals: {} ({})\n", nPop[0], nPop[1]);
	std::cout << std::format ("Inserts - Removals: {}\n", nPush - nPop[0]);
	std::cout << std::format ("Final size: {}\n\n", L.size ());
}


template<typename T>
void vector_construct_test () {

	std::cout << "Vector: l-value push\n";
	{
		T S{};
		vec v{1, 2};
		S.push_back (v);
	}
	std::cout << "\n";
	std::cout << "STL vector: l-value push\n";
	{
		std::vector<vec> S;
		vec v{1, 2};
		S.push_back (v);
	}
	std::cout << "\n";
	std::cout << "Vector: r-value push\n";
	{
		T L{};
		L.push_back (vec{1, 2});
	}
	std::cout << "\n";
	std::cout << "STL vector: r-value push\n";
	{
		std::vector<vec> S;
		S.push_back (vec{1, 2});
	}
	std::cout << "\n";
	std::cout << "Vector: emplace\n";
	{
		T L{};
		L.emplace_back (1, 2);
	}
	std::cout << "\n";
	std::cout << "STL vector: emplace\n";
	{
		std::vector<vec> S;
		S.emplace_back (1, 2);
	}
	std::cout << "\n";
	std::cout << "Prees Enter to continue";
	getchar ();
	{
		// capacity, resize, reserve
		std::initializer_list<vec> d{vec{1,2}, vec{3,4}, vec{5,6}, vec{7,8}};
		T L{d};
		std::cout << std::format ("\n4 push_backs\n");
		std::cout << std::format ("size: {}, capacity {}\n", L.size (), L.capacity ());
		std::cout << std::format ("1 push_back\n");
		L.push_back (vec{7,8});
		std::cout << std::format ("size: {}, capacity {}\n", L.size (), L.capacity ());
		std::cout << std::format ("reserve(5)\n");
		L.reserve (5);
		std::cout << std::format ("size: {}, capacity {}\n", L.size (), L.capacity ());
		std::cout << std::format ("reserve(9)\n");
		L.reserve (9);
		std::cout << std::format ("size: {}, capacity {}\n", L.size (), L.capacity ());
		std::cout << std::format ("resize(7)\n");
		L.resize (7);
		std::cout << std::format ("size: {}, capacity {}\n", L.size (), L.capacity ());
		std::cout << std::format ("resize(11)\n");
		L.resize (11);
		std::cout << std::format ("size: {}, capacity {}\n", L.size (), L.capacity ());
	}
}


template<typename T>
void vector_speed_test (const uint64_t n, const uint32_t M, const std::string& pattern) {

	std::cout << "Speed test\n";
	
	std::vector<std::string> d (n);
	for (auto& s : d)
		s = std::format ("{}{}", rand (), pattern);

	std::cout << "Origial";
	T O1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++) {
			O1.push_back (d[i]);
		}
		while (!O1.empty ())
			O1.pop_back ();
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "Origial emplace";
	T T2{};
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++) {
			T2.emplace_back (d[i]);
		}
		while (!T2.empty ())
			T2.pop_back ();
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL";
	std::vector<std::string> O2;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++) {
			O2.push_back (d[i]);
		}
		while (!O2.empty ())
			O2.pop_back ();
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL emplace";
	std::vector<std::string> U2;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++) {
			U2.emplace_back (d[i]);
		}
		while (!O2.empty ())
			U2.pop_back ();
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}
