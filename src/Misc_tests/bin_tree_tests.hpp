#include <chrono>
#include <string>
#include <vector>
#include <numbers>
#include <iostream>
#include <initializer_list>

#include "vec.hpp"
#include <set>
#include <queue>


template <typename T>
void tree_simple_visual_test ();

template <typename T>
void tree_construct_test ();

template <typename T>
void tree_multi_construct_test ();

template<typename T>
void tree_rundom_test ();

template<typename T>
void tree_multi_rundom_test ();
	
template <typename T>
void tree_copy_move_test ();

template<typename T>
void tree_speed_test (const uint64_t, const uint32_t, const std::string&);

template<typename T>
void tree_multi_speed_test (const uint64_t n, const uint32_t M, const std::string& pattern);

template<typename T>
void priority_queue_speed_test (const uint64_t, const uint32_t, const std::string&);

template<typename T>
void tree_emplace_speed_test (const uint64_t, const uint32_t);

template<typename T>
void tree_multi_emplace_speed_test (const uint64_t, const uint32_t);

template <typename T>
void tree_balance_speed_test (const uint64_t, const uint32_t);

template <typename T>
void tree_multi_balance_speed_test (const uint64_t, const uint32_t);


class stor {

public:
	stor () {
		b = new int[n];
		a = 0;
	}
	stor (int a) : a (a) {
		b = new int[n];
	}
	stor (const stor& o) {
		b = new int[n];
		memcpy (b, o.b, sizeof (int) * n);
		a = o.a;
	}
	stor (stor&& o) noexcept {
		b = o.b;
		o.b = nullptr;
		a = o.a;
	}
	stor& operator= (const stor& o) {

		if (this == &o)
			return *this;

		memcpy (b, o.b, sizeof (int) * n);
		a = o.a;
	}
	stor& operator= (stor&& o) noexcept {

		if (this == &o)
			return *this;

		b = o.b;
		o.b = nullptr;
		a = o.a;
	}
	~stor () {
		if (b != nullptr)
			delete[] b;
	}

	friend bool operator< (const stor& a, const stor& b);
	friend bool operator> (const stor& a, const stor& b);
	friend bool operator== (const stor& a, const stor& b);

	int a;
	int* b;
	const int n = 100000;
};

bool operator< (const stor& a, const stor& b) {
	return a.a < b.a;
}

bool operator> (const stor& a, const stor& b) {
	return a.a > b.a;
}

bool operator== (const stor& a, const stor& b) {
	return a.a == b.a;
}


template <typename T>
void tree_simple_visual_test () {

	std::cout << "Simple visual test\n\n";

	std::initializer_list<std::string> L{
		"noun", "sky", "violin", "table", "window", "queue", "pillow", "room",
		"home", "dream", "key", "bottom", "guest", "jack", "lady", "table", 
		"window", "queue", "pillow"
	};
	std::cout << "Input sequence:\n";
	for (auto& e : L)
		std::cout << e << " ";
	std::cout << "\n\n";

	T BT{L};
	std::cout << "Output sequence:\n";
	for (auto& w : BT)
		std::cout << w << " ";
	std::cout << "\n\n";

	BT.dprint ();
	std::cout << "\n";
}


template <typename T>
void tree_construct_test () {

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
		std::cout << "l-value insert std::set\n";
		std::set<vec> a;
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
		std::cout << "r-value insert std::set\n";
		std::set<vec> a;
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
		a.emplace (1, 1);
		a.emplace (-1, -2);
		a.emplace (3, 3);
		a.emplace (-1, -2);
	}
	std::cout << "\n";
	{
		std::cout << "emplace std::set\n";
		std::set<vec> a;
		a.emplace (1, 2);
		a.emplace (-1, -2);
		a.emplace (3, 3);
		a.emplace (-1, -2);
	}
	std::cout << "\n\n";
}


template <typename T>
void tree_multi_construct_test () {

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
		std::cout << "l-value insert std::multiset\n";
		std::multiset<vec> a;
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
		std::cout << "r-value insert std::multiset\n";
		std::multiset<vec> a;
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
		a.emplace (1, 1);
		a.emplace (-1, -2);
		a.emplace (3, 3);
		a.emplace (-1, -2);
	}
	std::cout << "\n";
	{
		std::cout << "emplace std::multiset\n";
		std::multiset<vec> a;
		a.emplace (1, 2);
		a.emplace (-1, -2);
		a.emplace (3, 3);
		a.emplace (-1, -2);
	}
	std::cout << "\n\n";
}


template <typename T>
void tree_copy_move_test () {

	std::cout << "Copy, move & aasigment test: ";

	T BT{
		"noun", "sky", "violin", "table", "window", "queue", "pillow", "room",
		"home", "dream", "key", "bottom", "guest", "jack", "lady", "table", "window", "queue", "pillow"
	};

	T BT1{BT};
	T BT2{std::move (BT1)};
	T BT3;
	BT3 = BT2;
	T BT4;
	BT4 = std::move (BT3);

	BT4.pprint ();

	auto it1 = BT.begin ();
	auto it2 = BT4.begin ();
	while (it1 != BT.end () && it2 != BT4.end ()) {
		if (*it1 != *it2)
			std::cout << "Error\n";
		++it1;
		++it2;
	}
	std::cout << "Success !!!\n\n";
}


template <typename T>
void tree_multi_copy_move_test () {

	std::cout << "Copy, move & aasigment test: ";

	T BT{
		"noun", "sky", "violin", "table", "window",
	    "queue", "pillow", "room", "home", "dream",
		"key","bottom","guest","jack","lady", "sky", "violin", "sky", "violin"
	};

	T BT1{BT};
	T BT2{std::move (BT1)};
	T BT3;
	BT3 = BT2;
	T BT4;
	BT4 = std::move (BT3);

	BT.insert ("apple");
	BT.insert ("apple");
	BT.insert ("apple");
	BT.insert ("apple");
	BT.emplace ("apple");
	BT.emplace ("forest");
	BT.erase ("noun");
	BT.erase ("apple");

	BT4.insert ("apple");
	BT4.insert ("apple");
	BT4.insert ("apple");
	BT4.insert ("apple");
	BT4.emplace ("apple");
	BT4.emplace ("forest");
	BT4.erase ("noun");
	BT4.erase ("apple");


	BT4.pprint ();

	auto it1 = BT.begin ();
	auto it2 = BT4.begin ();
	while (it1 != BT.end () && it2 != BT4.end ()) {
		if (*it1 != *it2) {
			std::cout << "Error\n";
			std::cout << "Press Enter to continue\n";
			getchar ();
			return;
		}
		++it1;
		++it2;
	}
	std::cout << "Success !!!\n\n";
}


template<typename T>
void tree_rundom_test () {

	std::cout << "Random test\n\n";

	const int eventsPerCycle = 1000;
	const int cycles = 10;
	const int height = 30;

	T Q{};
	std::set<std::string> S{};

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
			bool r = Q.insert (item);
			if (r)
				nInsert[0]++;
			else
				nInsert[1]++;
			S.insert (item);
		}
		for (int i{}; i < n_pop; i++) {
			std::string item = std::to_string (rand () % maxItems);
			bool r = Q.erase (item);
			if (r)
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
					if (Q.find (item) != nullptr)
						std::cout << std::format ("ERROR: find {}\n", item);
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
void tree_multi_rundom_test () {

	std::cout << "Random test\n\n";

	const int eventsPerCycle = 1000;
	const int cycles = 10;
	const int height = 30;

	T Q{};
	std::multiset<std::string> S{};

	int maxSize{};
	int maxItems{1000};
	int nInsert{0};
	int nErase{0};

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
			Q.insert (item);
			nInsert++;
			S.insert (item);
		}
		for (int i{}; i < n_pop; i++) {
			std::string item = std::to_string (rand () % maxItems);
			while (Q.erase (item))
				nErase++;
			if (!S.empty ())
				S.erase (item);
		}

		if (Q.size () > maxSize)
			maxSize = Q.size ();

		for (int i{}; i < n_push; i++) {
			std::string item = std::to_string (rand () % maxItems);
			if (Q.size () != 0 && S.size () != 0) {
				if (S.find (item) == S.end ()) {
					if (Q.find (item) != nullptr)
						std::cout << std::format ("ERROR: find {}\n", item);
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
	std::cout << std::format ("Inserts: {}\n", nInsert);
	std::cout << std::format ("Removals: {}\n", nErase);
	std::cout << std::format ("Inserts - Removals: {}\n", nInsert - nErase);
	std::cout << std::format ("Final size: {}\n\n", Q.size ());
}


template<typename T>
void tree_speed_test (const uint64_t n, const uint32_t M, const std::string& pattern) {

	std::cout << "Speed test\n";

	std::vector<std::string> d (n);
	for (auto& s : d)
		s = std::format ("{}{}", rand (), pattern);

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

	std::cout << "STL";
	std::set<std::string> S;
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
}


template<typename T>
void tree_multi_speed_test (const uint64_t n, const uint32_t M, const std::string& pattern) {

	std::cout << "Speed test\n";

	std::vector<std::string> d (n);
	for (auto& s : d)
		s = std::format ("{}{}", rand (), pattern);

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

	std::cout << "STL multi";
	std::multiset<std::string> S;
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
}


template<typename T>
void priority_queue_speed_test (const uint64_t n, const uint32_t M, const std::string& pattern) {

	std::cout << "Speed test\n";

	std::vector<std::string> d (n);
	for (auto& s : d)
		s = std::format ("{}{}", rand (), pattern);

	std::cout << "Original";
	T O1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			O1.push (d[i]);
		for (int i{}; i < n; i++)
			O1.pop ();
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL priority_queue";
	std::priority_queue<std::string> S;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S.push (d[i]);
		for (int i{}; i < n; i++)
			S.pop ();
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}


template <typename T>
void tree_balance_speed_test (const uint64_t n, const uint32_t M) {

	std::cout << "Speed test: balance insert-erase int\n";

	std::vector<std::string> d (n);
	int i{};
	for (auto& s : d) {
		s = std::format ("{:07}", i);
		++i;
	}

	std::cout << "BinTreeSort: insert-erase int";

	T B1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			B1.insert (d[i]);
		for (int i{}; i < n; i++)
			B1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL set: insert-erase int";

	std::set<std::string> S1;
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


template <typename T>
void tree_multi_balance_speed_test (const uint64_t n, const uint32_t M) {

	std::cout << "Speed test: balance insert-erase int\n";

	std::vector<std::string> d (n);
	int i{};
	for (auto& s : d) {
		s = std::format ("{:07}", i);
		++i;
	}

	std::cout << "BinTreeSortMulti: insert-erase int";

	T B1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			B1.insert (d[i]);
		for (int i{}; i < n; i++)
			B1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL multiset: insert-erase int";

	std::multiset<std::string> S1;
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
void tree_emplace_speed_test (const uint64_t n, const uint32_t M) {

	std::cout << "Speed test: insert-emplace-erase stor\n";

	std::vector<stor> d (n);
	for (auto& s : d)
		s.a = rand ();

	std::cout << "BinTreeSort: insert-erase stor";

	T B1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			B1.insert (d[i]);
		for (int i{}; i < n; i++)
			B1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "BinTreeSort: emplace-erase stor";

	T B2{};
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			B2.emplace (d[i].a);
		for (int i{}; i < n; i++)
			B2.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL set: insert-erase stor";

	std::set<stor> S1;
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

	std::cout << "STL set: emplace-erase stor";

	std::set<stor> S2;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S2.emplace (d[i].a);
		for (int i{}; i < n; i++)
			S2.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}


template<typename T>
void tree_multi_emplace_speed_test (const uint64_t n, const uint32_t M) {

	std::cout << "Speed test: insert-emplace-erase stor\n";

	std::vector<stor> d (n);
	for (auto& s : d)
		s.a = rand ();

	std::cout << "BinTreeSortMulti: insert-erase stor";

	T B1{};
	auto start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			B1.insert (d[i]);
		for (int i{}; i < n; i++)
			B1.erase (d[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "BinTreeSortMulti: emplace-erase stor";

	T B2{};
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			B2.emplace (d[i].a);
		for (int i{}; i < n; i++)
			B2.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());

	std::cout << "STL multiset: insert-erase stor";

	std::multiset<stor> S1;
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

	std::cout << "STL multiset: emplace-erase stor";

	std::multiset<stor> S2;
	start = std::chrono::high_resolution_clock::now ();

	for (int m{}; m < M; m++) {
		for (int i{}; i < n; i++)
			S2.emplace (d[i].a);
		for (int i{}; i < n; i++)
			S2.erase (d[i]);
	}

	stop = std::chrono::high_resolution_clock::now ();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << std::format ("\n\t{} milliseconds\n", duration.count ());
}