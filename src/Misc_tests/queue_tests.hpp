#include <queue>
#include <string>
#include <vector>
#include <chrono>
#include <format>
#include <numbers>
#include <iostream>

#include "vec.hpp"

template<typename T>
void queue_functional_test ();

template<typename T>
void queue_copy_move_test ();

template<typename T>
void queue_rundom_test ();

template<typename T>
void queue_construct_test ();

template<typename T, typename U>
void queue_speed_test (const uint64_t, const uint32_t, const std::string&);


template<typename T>
void queue_functional_test () {

	std::cout << "Functional test\n\n";

	T Q{};

	std::vector<std::string> p{"apple", "dream", "guest", "lady", "violin", "sky"};
	std::cout << "input sequence: ";
	for (auto& e : p) {
		Q.push (e);
		std::cout << e << " ";
	}
	std::cout << "\nsize: " << Q.size ();

	std::cout << "\noutput sequence: ";
	while (!Q.empty ()) {
		std::cout << Q.front () << " ";
		Q.pop ();
	}
	std::cout << "\n\n";
}


template<typename T, typename U>
bool identity_test (T& a, U& b) {

	if (a.size () != b.size ())
		return false;
	for (int i{}; i < a.size (); i++) {
		if (a.front () != b.front())
			return false; 
		else {
			a.pop ();
			b.pop ();
		}
	}
	return true;
}


template<typename T>
void queue_copy_move_test () {

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
		std::queue<std::string> S{d};
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
		std::queue<std::string> S{d};
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
		std::queue<std::string> S{d};
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
		std::queue<std::string> S{d};
		if (!identity_test (L1, S))
			std::cout << er;
		else
			std::cout << su;
	}
	std::cout << "\n\n";
}


template<typename T>
void queue_rundom_test () {

	std::cout << "Random test\n\n";

	const int eventsPerCycle = 1000;
	const int cycles = 10;
	const int height = 30;

	T Q{};
	std::queue<std::string> S{};

	int maxSize{};
	int nPush{};
	int nPop[]{0,0};

	bool error = false;
	srand(time(NULL));
	int n = eventsPerCycle * cycles;
	for (int k{}; k < n; k++) {

		int m1 = (int)(height * (sin(k * 2 * std::numbers::pi / eventsPerCycle) + 1) / 2.);
		int m2 = (int)(height * (1 - sin(k * 2 * std::numbers::pi / eventsPerCycle)) / 2.);
		int n_push = rand() % (m1 + 1);
		int n_pop = rand() % (m2 + 1);


		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string(rand());
			Q.push(item);
			S.push(item);
			nPush++;
		}
		for (int i{}; i < n_pop; i++) {
			if (!Q.empty())
				nPop[0]++;
			else
				nPop[1]++;
			Q.pop();
			if (!S.empty())
				S.pop();
		}

		if (Q.size() > maxSize)
			maxSize = Q.size();

		if (Q.size() != 0 && S.size() != 0) {
			if (Q.front() != S.front()) {
				std::cout << std::format("ERROR: front {} != {}\n", Q.front(), S.front());
				error = true;
			}
		}
		else {
			if (Q.size() != S.size()) {
				std::cout << std::format("ERROR: size {} != {}\n", Q.size(), S.size());
				error = true;
			}
		}
	}
	if (error == false)
		std::cout << "Success !!!\n";

	std::cout << std::format("Max size: {}\n", maxSize);
	std::cout << std::format("Inserts: {}\n", nPush);
	std::cout << std::format("Removals: {} ({})\n", nPop[0], nPop[1]);
	std::cout << std::format("Inserts - Removals: {}\n", nPush - nPop[0]);
	std::cout << std::format("Final size: {}\n\n", Q.size());
}


template<typename T>
void queue_construct_test () {

	std::cout << "Queue: l-value push\n";
	{
		T S{};
		vec v{1, 2};
		S.push (v);
	}
	std::cout << "\n";
	std::cout << "STL queue: l-value push\n";
	{
		std::queue<vec> S;
		vec v{1, 2};
		S.push (v);
	}
	std::cout << "\n";
	std::cout << "Queue: r-value push\n";
	{
		T Q{};
		Q.push (vec{1, 2});
	}
	std::cout << "\n";
	std::cout << "STL queue: r-value push\n";
	{
		std::queue<vec> S;
		S.push (vec{1, 2});
	}
	std::cout << "\n";
}


template<typename T, typename U>
void queue_speed_test (const uint64_t n, const uint32_t M, const std::string& pattern) {

	std::cout << "Speed test\n";

	std::vector<std::string> d (n);
	for (auto& s : d)
		s = std::format ("{}{}", rand (), pattern);

	std::cout << "Modified";
	T O1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++) {
			O1.push (d[i]);
		}
		while (!O1.empty ())
			O1.pop ();
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "Origial";
	U O2{};
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			O2.push (d[i]);
		while (!O2.empty ())
			O2.pop ();
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL";
	std::queue<std::string> S;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++) {
			S.push (d[i]);
		}
		while (!S.empty ())
			S.pop ();
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}
