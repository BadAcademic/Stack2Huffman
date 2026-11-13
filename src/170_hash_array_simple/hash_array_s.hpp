#ifndef _HASHARRAYS_
#define _HASHARRAYS_

#include <fstream>
#include <iostream>

#include "list.hpp"
#include "gexception.h"


template <typename T>
class HashArrayS {

public:

	HashArrayS ();
	HashArrayS (const HashArrayS&) = delete;
	HashArrayS& operator= (const HashArrayS&) = delete;
	~HashArrayS ();

	template <typename U>
	bool insert (U&&);

	T* find (T&);

	bool erase (const T&);

	size_t size ();

	bool empty ();

	void print ();

private:

	List<T>* array{};

	size_t hash_function (const T&);

	const size_t length{40};

	size_t msize{};
};


template <typename T>
HashArrayS<T>::HashArrayS () {

	array = new (std::nothrow) List<T>[length];
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);
}


template <typename T>
HashArrayS<T>::~HashArrayS () {

	if (array != nullptr)
		delete[] array;
}


template <typename T>
size_t HashArrayS<T>::hash_function (const T& data) {

	size_t res = ~data + (data << 15);
	res = res ^ (res >> 12);
	res = res + (res << 2);
	res = res ^ (res >> 4);
	res = (res + (res << 3)) + (res << 11);
	res = res ^ (res >> 16);

	return res;
}


template <typename T>
template <typename U>
bool HashArrayS<T>::insert (U&& data) {

	size_t key = hash_function (data) % length;

	if (array[key].find (data) != nullptr)
		return false;
	else
		array[key].push_back (std::forward<U> (data));
}


template <typename T>
bool HashArrayS<T>::erase (const T& data) {

	size_t key = hash_function (data) % length;

	if (array[key].find (data) == nullptr)
		return false;
	else
		array[key].erase (data);
}


template <typename T>
T* HashArrayS<T>::find (T& data) {

	size_t key = hash_function (data) % length;

	return 	array[key].find ();
}


template <typename T>
size_t HashArrayS<T>::size () {

	return msize;
}


template <typename T>
void HashArrayS<T>::print () {

	for (size_t i{}; i < length; i++) {

		if (!array[i].empty ()) {
			std::cout << i << ": ";
			for (auto& e : array[i])
				std::cout << e << " ";
			std::cout << "\n";
		}
	}
}


template <typename T>
bool HashArrayS<T>::empty () {

	return msize == 0 ? true : false;
}

#endif
