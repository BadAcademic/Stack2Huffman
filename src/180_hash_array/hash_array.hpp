#ifndef _HASHARRAY_
#define _HASHARRAY_

#include <fstream>
#include <iostream>

#include "list.hpp"
#include "gexception.h"


template <typename T>
class HashArray {

public:

	HashArray ();
	HashArray (const std::initializer_list<T>&);
	HashArray (const HashArray&);
	HashArray (HashArray&&) noexcept;
	HashArray& operator= (const HashArray&);
	HashArray& operator= (HashArray&&) noexcept;
	~HashArray ();

	template <typename U>
	bool insert (U&&);

	template <typename... U>
	bool emplace (U&&... args);

	T* find (T&);

	bool erase (const T&);

	size_t size ();

	bool empty ();

	void clear ();

	float max_load_factor ();
	void max_load_factor (float);

	void print ();

	class iterator;

	iterator begin ();
	iterator end ();

private:

	void rehash ();

	std::hash<T> hasher;

	List<T>* array{};

	List<T> buffer;

	size_t bcount{8};

	size_t msize{};
	float maxloadfactor{1};
};


template <typename T>
HashArray<T>::HashArray () {

	array = new (std::nothrow) List<T>[bcount];
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);
}


template <typename T>
HashArray<T>::HashArray (const std::initializer_list<T>& l) {

	array = new (std::nothrow) List<T>[bcount];
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (auto& e : l)
		insert (e);
}


template <typename T>
HashArray<T>::HashArray (const HashArray& o) {

	msize = o.msize;
	bcount = o.bcount;
	maxloadfactor = o.maxloadfactor;

	array = new (std::nothrow) List<T>[bcount];
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (size_t i{}; i < bcount; i++)
		array[i] = o.array[i];
}


template <typename T>
HashArray<T>::HashArray (HashArray&& o) noexcept {

	msize = o.msize;
	o.msize = 0;
	bcount = o.bcount;
	o.bcount = 8;
	maxloadfactor = o.maxloadfactor;
	o.maxloadfactor = 1;

	array = o.array;
	o.array = nullptr;
}


template <typename T>
HashArray<T>& HashArray<T>::operator= (const HashArray& o) {

	if (this == &o)
		return *this;

	if (array != nullptr)
		delete[] array;

	msize = o.msize;
	bcount = o.bcount;
	maxloadfactor = o.maxloadfactor;

	array = new (std::nothrow) List<T>[bcount];
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (size_t i{}; i < bcount; i++)
		array[i] = o.array[i];

	return *this;
}


template <typename T>
HashArray<T>& HashArray<T>::operator= (HashArray&& o) noexcept {

	if (this == &o)
		return *this;

	if (array != nullptr)
		delete[] array;

	msize = o.msize;
	o.msize = 0;
	bcount = o.bcount;
	o.bcount = 8;
	maxloadfactor = o.maxloadfactor;
	o.maxloadfactor = 1;

	array = o.array;
	o.array = nullptr;

	return *this;
}


template <typename T>
HashArray<T>::~HashArray () {

	if (array != nullptr)
		delete[] array;
}


template <typename T>
template <typename U>
bool HashArray<T>::insert (U&& data) {

	size_t key = hasher (data) % bcount;

	if (array[key].find (data) != nullptr)
		return false;
	else {
		array[key].push_back (std::forward<U> (data));

		msize++;
		float load_factor = msize / (float) bcount;
		if (load_factor > maxloadfactor)
			rehash ();
	}
}


template <typename T>
template <typename... U>
bool HashArray<T>::emplace (U&&... args) {

	buffer.emplace_back (std::forward<U> (args)...);
	T& data = buffer.back ();

	size_t key = hasher (data) % bcount;

	if (array[key].find (data) != nullptr) {

		buffer.clear ();
		return false;
	}
	else {
		array[key].splice_e2e (buffer);

		msize++;
		float load_factor = msize / (float) bcount;
		if (load_factor > maxloadfactor)
			rehash ();
	}
}


template <typename T>
bool HashArray<T>::erase (const T& data) {

	size_t key = hasher (data) % bcount;

	if (!array[key].erase (data))
		return false;

	msize--;

	return true;
}


template <typename T>
T* HashArray<T>::find (T& data) {

	size_t key = hasher (data) % bcount;

	return 	array[key].find ();
}


template <typename T>
size_t HashArray<T>::size () {

	return msize;
}


template <typename T>
void HashArray<T>::print () {

	for (size_t i{}; i < bcount; i++) {

		if (!array[i].empty ()) {
			std::cout << i << ": ";
			for (auto& e : array[i])
				std::cout << e << " ";
			std::cout << "\n";
		}
	}
}


template <typename T>
bool HashArray<T>::empty () {

	return msize == 0 ? true : false;
}


template <typename T>
void HashArray<T>::clear () {

	for (size_t i{}; i < bcount; i++)
		array[i].clear ();

	msize = 0;
}


template <typename T>
float HashArray<T>::max_load_factor () {

	return maxloadfactor;
}


template <typename T>
void HashArray<T>::max_load_factor (float f) {

	maxloadfactor = f;
}


template <typename T>
void HashArray<T>::rehash () {

	int new_bcount{};
	if (bcount == 8)
		new_bcount = 64;
	else if (bcount == 64)
		new_bcount = 512;
	else
		new_bcount = bcount * 2;

	List<T>* new_array = new (std::nothrow) List<T>[new_bcount];
	if (new_array == nullptr)
		throw gexception (gexception::MemAlloc);

	List<T>* tmp = array;
	array = new_array;
	size_t ntmp = bcount;
	bcount = new_bcount;

	for (size_t i{}; i < ntmp; i++) {

		size_t s = tmp[i].size ();
		for (size_t j{}; j < s; j++) {
			size_t key = hasher (tmp[i].back()) % bcount;
			array[key].splice_e2e (tmp[i]);
		}
	}

	delete[] tmp;
}


template <typename T>
class HashArray<T>::iterator {

public:

	iterator ();
	iterator (const iterator&);
	iterator& operator= (const iterator&);
	~iterator ();

	iterator& operator++ ();

	bool operator!= (const iterator&) const;

	T& operator* ();

	T* operator-> ();

private:

	friend iterator HashArray<T>::begin (void);
	friend iterator HashArray<T>::end (void);

	List<T>* array{};
	size_t nbucket{};
	size_t bcount{};
	List<T>::iterator it;
};


template <typename T>
HashArray<T>::iterator::iterator () {

}


template <typename T>
HashArray<T>::iterator::iterator (const iterator& iterator) {

	nbucket = iterator.nbucket;
	bcount = iterator.bcount;
	it = iterator.it;
}


template <typename T>
typename HashArray<T>::iterator& HashArray<T>::iterator::operator= (const iterator& iterator) {

	if (this == &iterator)
		return (*this);

	nbucket = iterator.nbucket;
	bcount = iterator.bcount;
	it = iterator.it;

	return (*this);
}


template <typename T>
typename HashArray<T>::iterator& HashArray<T>::iterator::operator++ () {

	++it;
	if (!(it != array[nbucket].end ())) {
		
		nbucket++;
		if (nbucket == bcount)
			return (*this);
		else {

			while (nbucket < bcount) {
				
				if (!array[nbucket].empty ()) {

					it = array[nbucket].begin ();
					break;
				}
				else {
					nbucket++;
				}
			}
		}
	} 
	return (*this);
}


template <typename T>
bool HashArray<T>::iterator::operator!= (const iterator& iterator) const {

	if (it != iterator.it)
		return true;
	else
		return false;
}


template <typename T>
T& HashArray<T>::iterator::operator* () {

	return (*it);
}


template <typename T>
T* HashArray<T>::iterator::operator-> () {

	return (&(*it));
}


template <typename T>
typename HashArray<T>::iterator HashArray<T>::begin (void) {

	iterator res{};
	res.array = HashArray<T>::array;
	res.bcount = HashArray<T>::bcount;

	while (array[res.nbucket].empty () && res.nbucket < res.bcount)
		res.nbucket++;

	if (res.nbucket < res.bcount)
		res.it = array[res.nbucket].begin ();
	else
		res.it = array[0].end ();

	return res;
}


template <typename T>
typename HashArray<T>::iterator HashArray<T>::end (void) {

	iterator res{};
	res.nbucket = bcount;
	res.it = array[0].end ();
	return res;
}


template <typename T>
HashArray<T>::iterator::~iterator () {
}


#endif
