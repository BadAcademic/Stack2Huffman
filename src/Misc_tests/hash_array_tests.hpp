#include <chrono>
#include <string>
#include <vector>
#include <numbers>
#include <iostream>
#include <initializer_list>

#include "vec.hpp"
#include <set>
#include <unordered_set>

template <typename T>
void hash_array_copy_move_test ();

template<typename T>
void hash_array_int_speed_test (const uint64_t, const uint32_t);

template <typename T>
void hash_array_construct_test ();

template<typename T>
void hash_array_rundom_test ();

template<typename T>
void hash_array_speed_test (const uint64_t, const uint32_t, const std::string);

template<typename T>
void hash_array_multi_rundom_test ();


template <typename T>
void hash_array_copy_move_test () {

	std::cout << "Copy, move & asigment test: ";

	T HA {
		"noun", "sky", "violin", "table", "window", "queue", "pillow", "room", "cucmber", "city",
		"home", "dream", "key", "bottom", "guest", "jack", "lady", "table", "window", "queue", "pillow"
	};

	T HA1{HA};
	T HA2{std::move (HA1)};
	T HA3;
	HA3 = HA2;
	T HA4;
	HA4 = std::move (HA3);

	std::cout << "\n\n";
	HA4.print ();

	for (auto& e : HA4)
		std::cout << e << " ";

	auto it1 = HA.begin ();
	auto it2 = HA4.begin ();
	while (it1 != HA.end () && it2 != HA4.end ()) {
		if (*it1 != *it2)
			std::cout << "Error\n";
		++it1;
		++it2;
	}
	std::cout << "\nSuccess !!!\n\n";
}


template <typename T>
void hash_array_construct_test () {

	std::cout << "Construct test\n\n";
	{
		std::cout << "l-value insert\n";
		T a{};
		vec v{1,2};
		a.insert (v);
		a.insert (v);
		a.insert (v);
	}
	std::cout << "\n";
	{
		std::cout << "l-value insert std::unordered_set\n";
		std::unordered_set<vec> a;
		vec v{1,2};
		a.insert (v);
		a.insert (v);
		a.insert (v);
	}
	std::cout << "\n\n";
	{
		std::cout << "r-value insert\n";
		T a{};
		a.insert (vec{1, 2});
		a.insert (vec{-1, -2});
		a.insert (vec{3, 3});
	}
	std::cout << "\n";
	{
		std::cout << "r-value insert std::unordered_set\n";
		std::unordered_set<vec> a;
		a.insert (vec{1, 2});
		a.insert (vec{-1, -2});
		a.insert (vec{3, 3});
	}
	//std::cout << "Press Enter to continue\n";
	std::cout << "\n\n";
	//getchar ();
	{
		std::cout << "emplace\n";
		T a{};
		a.emplace (1, 2);
		a.emplace (1, 2);
		a.emplace (3, 3);
		a.emplace (-1, -2);
	}
	std::cout << "\n";
	{
		std::cout << "emplace std::unordered_set\n";
		std::unordered_set<vec> a;
		a.emplace (1, 2);
		a.emplace (1, 2);
		a.emplace (3, 3);
		a.emplace (-1, -2);
	}
	std::cout << "\n\n";
}


template<typename T>
void hash_array_int_speed_test (const uint64_t n, const uint32_t M) {

	std::cout << "Speed test\n";

	std::vector<int> d (n);
	for (auto& s : d)
		s = rand ();

	std::cout << "Original";
	T O1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			O1.insert (d[i]);
		for (int i{}; i < n; i++)
			O1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL set";
	std::set<int> S;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S.insert (d[i]);
		for (int i{}; i < n; i++)
			S.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL unordered_set";
	std::unordered_set<int> S1;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S1.insert (d[i]);
		for (int i{}; i < n; i++)
			S1.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}


template<typename T>
void hash_array_speed_test (const uint64_t n, const uint32_t M, std::string pattern) {

	std::cout << "Speed test\n";

	std::vector<std::string> d (n);

//	int k{0};
	for (auto& s : d) {
		s = std::format ("{}{}", rand(), pattern);
//		k++;
	}

	std::cout << "Original";
	T O1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			O1.insert (d[i]);
//		O1.clear ();
		for (int i{}; i < n; i++)
			O1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	//std::cout << "STL set";
	//std::set<std::string> S;
	//start = std::chrono::high_resolution_clock::now ();

	//for (int m{}; m < M; m++) {
	//	for (int i{}; i < n; i++)
	//		S.insert (d[i]);
	//	for (int i{}; i < n; i++)
	//		S.erase (d[i]);
	//}

	//stop = std::chrono::high_resolution_clock::now ();
	//duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	//std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL unordered_set";
	std::unordered_set<std::string> S1;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S1.insert (d[i]);
//		S1.clear ();
		for (int i{}; i < n; i++)
			S1.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}


template<typename T>
void hash_array_multi_speed_test (const uint64_t n, const uint32_t M, std::string pattern) {

	std::cout << "Speed test\n";

	std::vector<std::string> d (n);

	//	int k{0};
	for (auto& s : d) {
		s = std::format ("{}{}", rand (), pattern);
		//		k++;
	}

	std::cout << "Original";
	T O1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			O1.insert (d[i]);
		//		O1.clear ();
		for (int i{}; i < n; i++)
			O1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	//std::cout << "STL set";
	//std::set<std::string> S;
	//start = std::chrono::high_resolution_clock::now ();

	//for (int m{}; m < M; m++) {
	//	for (int i{}; i < n; i++)
	//		S.insert (d[i]);
	//	for (int i{}; i < n; i++)
	//		S.erase (d[i]);
	//}

	//stop = std::chrono::high_resolution_clock::now ();
	//duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	//std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL unordered_multiset";
	std::unordered_multiset<std::string> S1;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S1.insert (d[i]);
		//		S1.clear ();
		for (int i{}; i < n; i++)
			S1.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds> (stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}


template<typename T>
void hash_array_rundom_test () {

	std::cout << "Random test\n\n";

	const int eventsPerCycle = 1000;
	const int cycles = 10;
	const int height = 30;

	T Q{};
	std::unordered_set<std::string> S{};

	int maxSize{};
	int maxItems{1000};
	int nInsert[]{0,0};
	int nErase[]{0,0};

	bool error = false;
	srand (time (NULL));
	int n = eventsPerCycle * cycles;
	for (int k{}; k < n; k++) {

		int m1 = (int)(height * (sin (k * 2 * std::numbers::pi / eventsPerCycle) + 1) / 2.);
		int m2 = (int)(height * (1 - sin (k * 2 * std::numbers::pi / eventsPerCycle)) / 2.);
		int n_push = rand () % (m1 + 1);
		int n_pop = rand () % (m2 + 1);

		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string (rand () % maxItems);
			if (Q.insert (item))
				nInsert[0]++;
			else
				nInsert[1]++;
			S.insert (item);
		}
		for (int i{}; i < n_pop; i++) {
			std::string item = std::to_string (rand () % maxItems);
			if (Q.erase (item))
				nErase[0]++;
			else
				nErase[1]++;
			if (!S.empty ())
				S.erase (item);
		}

		if (Q.size () > maxSize)
			maxSize = Q.size ();

		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string (rand () % maxItems);
			if (Q.size () != 0 && S.size () != 0) {
				if (S.find (item) == S.end ()) {
					if (Q.find (item) != nullptr) {
						std::cout << std::format ("ERROR: find {}\n", item);
						error = true;
					}
				}
				else if (*Q.find (item) != *S.find (item)) {
					std::cout << std::format ("ERROR: find item {} != {}\n", *Q.find (item), *S.find (item));
					error = true;
				}
			}
			else {
				if (Q.size () != S.size ()) {
					std::cout << std::format ("ERROR: size {} != {}\n", Q.size (), S.size ());
					error = true;
				}
			}
		}
	}
	if (error == false)
		std::cout << "Success !!!\n";

	std::cout << std::format ("Max size: {}\n", maxSize);
	std::cout << std::format ("Inserts: {} ({})\n", nInsert[0], nInsert[1]);
	std::cout << std::format ("Removals: {} ({})\n", nErase[0], nErase[1]);
	std::cout << std::format ("Inserts - Removals: {}\n", nInsert[0] - nErase[0]);
	std::cout << std::format ("Final size: {}\n\n", Q.size ());
}


template<typename T>
void hash_array_multi_rundom_test () {

	std::cout << "Random test\n\n";

	const int eventsPerCycle = 1000;
	const int cycles = 10;
	const int height = 30;

	T Q{};
	std::unordered_set<std::string> S{};

	int maxSize{};
	int maxItems{1000};
	int nInsert[]{0,0};
	int nErase[]{0,0};

	bool error = false;
	srand (time (NULL));
	int n = eventsPerCycle * cycles;
	for (int k{}; k < n; k++) {

		int m1 = (int)(height * (sin (k * 2 * std::numbers::pi / eventsPerCycle) + 1) / 2.);
		int m2 = (int)(height * (1 - sin (k * 2 * std::numbers::pi / eventsPerCycle)) / 2.);
		int n_push = rand () % (m1 + 1);
		int n_pop = rand () % (m2 + 1);

		bool r{};
		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string (rand () % maxItems);
			if (Q.insert (item))
				nInsert[0]++;
			else
				nInsert[1]++;
			S.insert (item);
		}
		for (int i{}; i < n_pop; i++) {
			std::string item = std::to_string (rand () % maxItems);
			while (true) {				
				if (Q.erase (item))
					nErase[0]++;
				else {
					break;
					nErase[1]++;
				}
			}
			if (!S.empty ())
				S.erase (item);
		}

		if (Q.size () > maxSize)
			maxSize = Q.size ();

		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string (rand () % maxItems);
			if (Q.size () != 0 && S.size () != 0) {
				if (S.find (item) == S.end ()) {
					if (Q.find (item) != nullptr) {
						std::cout << std::format ("ERROR: find {}\n", item);
						error = true;
					}
				}
				else if (*Q.find (item) != *S.find (item)) {
					std::cout << std::format ("ERROR: find item {} != {}\n", *Q.find (item), *S.find (item));
					error = true;
				}
			}
			else {
				if (Q.size () != S.size ()) {
					std::cout << std::format ("ERROR: size {} != {}\n", Q.size (), S.size ());
					error = true;
				}
			}
		}
	}
	if (error == false)
		std::cout << "Success !!!\n";

	std::cout << std::format ("Max size: {}\n", maxSize);
	std::cout << std::format ("Inserts: {} ({})\n", nInsert[0], nInsert[1]);
	std::cout << std::format ("Removals: {} ({})\n", nErase[0], nErase[1]);
	std::cout << std::format ("Inserts - Removals: {}\n", nInsert[0] - nErase[0]);
	std::cout << std::format ("Final size: {}\n\n", Q.size ());
}
