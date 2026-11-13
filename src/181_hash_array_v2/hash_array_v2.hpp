#ifndef _HASHARRAY_
#define _HASHARRAY_

#include <fstream>
#include <iostream>

#include "stack.hpp"
#include "gexception.h"
#include "ghash.hpp"


template <typename T>
class HashArrayV2 {

public:

	HashArrayV2 ();
	HashArrayV2 (const std::initializer_list<T>&);
	HashArrayV2 (const HashArrayV2&);
	HashArrayV2 (HashArrayV2&&) noexcept;
	HashArrayV2& operator= (const HashArrayV2&);
	HashArrayV2& operator= (HashArrayV2&&) noexcept;
	~HashArrayV2 ();

	template <typename U>
	bool insert (U&&);

	template <typename... U>
	bool emplace (U&&... args);

	T* find (const T&) const noexcept;

	bool erase (const T&) noexcept;

	size_t size () const noexcept;

	bool empty () const noexcept;

	void clear () noexcept;

	float max_load_factor () const noexcept;
	void max_load_factor (float) const noexcept;

	void print () const noexcept;

	class iterator;

	iterator begin ();
	iterator end ();

protected:

	std::hash<T> hasher;

private:

	struct Item {

		template <typename U>
		Item (U&& data) : data (std::forward<U> (data)) {};
		template <typename... U>
		Item (U&&... args) : data (std::forward<U> (args)...) {};

		Item* r{};
		T data{};
	};

	void copy (const HashArrayV2&);

	void clearAll () noexcept;

	void rehash ();

	Item** array{};

	Stack<Item*> eitems;

	size_t bcount{8};

	size_t msize{};
	float maxloadfactor{1};

	static const size_t cbcount;
	static const float cmaxloadfactor;
};


template <typename T>
const size_t HashArrayV2<T>::cbcount{8};
template <typename T>
const float HashArrayV2<T>::cmaxloadfactor{1};


template <typename T>
HashArrayV2<T>::HashArrayV2 () {

	array = new (std::nothrow) Item* [bcount]();
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);
	
}


template <typename T>
HashArrayV2<T>::HashArrayV2 (const std::initializer_list<T>& l) {

	array = new (std::nothrow) Item*[bcount]();
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (auto& e : l)
		insert (e);
}


template <typename T>
HashArrayV2<T>::HashArrayV2 (const HashArrayV2& o) {

	copy (o);
}


template <typename T>
HashArrayV2<T>::HashArrayV2 (HashArrayV2&& o) noexcept {

	msize = o.msize;
	o.msize = 0;
	bcount = o.bcount;
	o.bcount = cbcount;
	maxloadfactor = o.maxloadfactor;
	o.maxloadfactor = cmaxloadfactor;

	array = o.array;
	o.array = nullptr;
}


template <typename T>
HashArrayV2<T>& HashArrayV2<T>::operator= (const HashArrayV2& o) {

	if (this == &o)
		return *this;

	clearAll ();
	copy (o);

	return *this;
}


template <typename T>
HashArrayV2<T>& HashArrayV2<T>::operator= (HashArrayV2&& o) noexcept {

	if (this == &o)
		return *this;

	clearAll ();

	msize = o.msize;
	o.msize = 0;
	bcount = o.bcount;
	o.bcount = cbcount;
	maxloadfactor = o.maxloadfactor;
	o.maxloadfactor = cmaxloadfactor;

	array = o.array;
	o.array = nullptr;

	return *this;
}


template <typename T>
HashArrayV2<T>::~HashArrayV2 () {

	clearAll ();
}


template <typename T>
void HashArrayV2<T>::copy (const HashArrayV2& o) {

	msize = o.msize;
	bcount = o.bcount;
	maxloadfactor = o.maxloadfactor;

	array = new (std::nothrow) Item*[bcount]();
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (size_t i{}; i < bcount; i++) {
		
		if (o.array[i] != nullptr) {

			Item* sitem{o.array[i]};
			Item* ditem{};
			while (sitem != nullptr) {

				Item* nitem = new (std::nothrow) Item (sitem->data);
				if (nitem == nullptr)
					throw gexception (gexception::MemAlloc);
				
				if (sitem == o.array[i]) {
					array[i] = nitem;
					ditem = nitem;
				}
				else
					ditem->r = nitem;
				sitem = sitem->r;
			}
		}
	}
}


template <typename T>
template <typename U>
bool HashArrayV2<T>::insert (U&& data) {

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};
	if (item != nullptr) {
		while (true) {

			if (item->data != data) {

				if (item->r != nullptr)
					item = item->r;
				else
					break;
			}
			else
				return false;
		}
	}

	Item* nitem{};
	if (!eitems.empty ()) {

		nitem = eitems.top ();
		eitems.pop ();

		new(&nitem->data) T (std::forward<U> (data));
		nitem->r = nullptr;
	}
	else {
		nitem = new (std::nothrow) Item (std::forward<U> (data));
		if (nitem == nullptr)
			throw gexception (gexception::MemAlloc);
	}

	if (array[key] != nullptr)
		item->r = nitem;
	else
		array[key] = nitem;

	msize++;
	if (msize > maxloadfactor * bcount)
		rehash ();

	return true;
}


template <typename T>
template <typename... U>
bool HashArrayV2<T>::emplace (U&&... args) {

	Item* nitem{};
	bool fres{};
	if (!eitems.empty ()) {

		nitem = eitems.top ();
		eitems.pop ();

		new(&nitem->data) T (std::forward<U> (args)...);
		nitem->r = nullptr;
		fres = true;
	}
	else {
		nitem = new (std::nothrow) Item (std::forward<U> (args)...);
		if (nitem == nullptr)
			throw gexception (gexception::MemAlloc);
	}

	T& data = nitem->data;

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};
	if (item != nullptr) {
		while (true) {

			if (item->data != data) {

				if (item->r != nullptr)
					item = item->r;
				else
					break;
			}
			else {
				if (fres) {
					nitem->data.~T ();
					eitems.push (nitem);
				}
				else
					delete nitem;
				return false;
			}
		}
	}

	if (array[key] != nullptr)
		item->r = nitem;
	else
		array[key] = nitem;

	msize++;
	if (msize > maxloadfactor * bcount)
		rehash ();

	return true;
}


template <typename T>
bool HashArrayV2<T>::erase (const T& data) noexcept {

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};
	if (item != nullptr) {

		if (item->r == nullptr) {
			if (item->data != data)
				return false;
			else {
				item->data.~T ();
				eitems.push (item);
				array[key] = nullptr;
				msize--;
				return true;
			}
		}
		else {

			Item** pitem{array + key};
			while (item != nullptr) {

				if (item->data != data) {

					pitem = &item->r;
					item = item->r;
				}
				else {

					*pitem = item->r;
					item->data.~T ();
					eitems.push (item);
					msize--;
					return true;
				}
			}
		}
	}
	return false;
}


template <typename T>
T* HashArrayV2<T>::find (const T& data) const noexcept {

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};

	while (item != nullptr) {

		if (item->data == data)
			return &item->data;
		else
			item = item->r;
	}
	
	return nullptr;
}


template <typename T>
size_t HashArrayV2<T>::size () const noexcept {

	return msize;
}


template <typename T>
void HashArrayV2<T>::print () const noexcept {

	for (size_t i{}; i < bcount; i++) {

		if (array[i] != nullptr) {

			std::cout << i << ": ";
			Item* item{array[i]};
			while (item != nullptr) {
				std::cout << item->data << " ";
				item = item->r;
			}
			std::cout << "\n";
		}
	}
}


template <typename T>
bool HashArrayV2<T>::empty () const noexcept {

	return msize == 0 ? true : false;
}


template <typename T>
void HashArrayV2<T>::clear () noexcept {

	if (array != nullptr) {
		for (size_t i{}; i < bcount; i++) {

			Item* item{array[i]};
			while (item != nullptr) {
				Item* tmp{item};
				item = item->r;
				delete tmp;
			}
			array[i] = nullptr;
		}
	}
	while (!eitems.empty ()) {
		Item* tmp{eitems.top ()};
		eitems.pop ();
		delete tmp;
	}
	msize = 0;
}


template <typename T>
void HashArrayV2<T>::clearAll () noexcept {

	clear ();

	if (array != nullptr)
		delete[] array;
	array = nullptr;
}


template <typename T>
float HashArrayV2<T>::max_load_factor () const noexcept {

	return maxloadfactor;
}


template <typename T>
void HashArrayV2<T>::max_load_factor (float f) const noexcept {

	maxloadfactor = f;
}


template <typename T>
void HashArrayV2<T>::rehash () {

	int new_bcount{};
	if (bcount == 8)
		new_bcount = 64;
	else if (bcount == 64)
		new_bcount = 512;
	else
		new_bcount = bcount * 2;

	Item** new_array = new (std::nothrow) Item*[new_bcount]();
	if (new_array == nullptr)
		throw gexception (gexception::MemAlloc);

	Item** tmp = array;
	array = new_array;
	size_t ntmp = bcount;
	bcount = new_bcount;

	for (size_t i{}; i < ntmp; i++) {

		Item* item{tmp[i]};
		if (item == nullptr)
			continue;

		while (item != nullptr) {

			Item* titem{item};

			item = item->r;

			size_t key = hasher (titem->data) % bcount;
			if (array[key] != nullptr) {
				Item* nitem{array[key]};
				array[key] = titem;
				titem->r = nitem;
			}
			else {
				array[key] = titem;
				titem->r = nullptr;
			}
		}
	}
	delete[] tmp;
}


template <typename T>
class HashArrayV2<T>::iterator {

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

	friend iterator HashArrayV2<T>::begin (void);
	friend iterator HashArrayV2<T>::end (void);
	
	Item** array{};
	size_t nbucket;
	size_t bcount;
	Item* item;
};


template <typename T>
HashArrayV2<T>::iterator::iterator () {

}


template <typename T>
HashArrayV2<T>::iterator::iterator (const iterator& iterator) {

	nbucket = iterator.nbucket;
	bcount = iterator.bcount;
	item = iterator.item;
}


template <typename T>
typename HashArrayV2<T>::iterator& HashArrayV2<T>::iterator::operator= (const iterator& iterator) {

	if (this == &iterator)
		return (*this);

	nbucket = iterator.nbucket;
	bcount = iterator.bcount;
	item = iterator.item;

	return (*this);
}


template <typename T>
typename HashArrayV2<T>::iterator& HashArrayV2<T>::iterator::operator++ () {

	if (item->r != nullptr)
		item = item->r;

	else if (nbucket < bcount - 1) {
		
		while (nbucket < bcount - 1) {

			nbucket++;
			if (array[nbucket] != nullptr) {
				item = array[nbucket];
				break;
			}
		}
	}
	else
		item = nullptr;

	return (*this);
}


template <typename T>
bool HashArrayV2<T>::iterator::operator!= (const iterator& iterator) const {

	if (item != iterator.item)
		return true;
	else
		return false;
}


template <typename T>
T& HashArrayV2<T>::iterator::operator* () {

	return item->data;
}


template <typename T>
T* HashArrayV2<T>::iterator::operator-> () {

	return &item->data;
}


template <typename T>
typename HashArrayV2<T>::iterator HashArrayV2<T>::begin (void) {

	iterator res{};
	res.array = HashArrayV2<T>::array;
	res.bcount = HashArrayV2<T>::bcount;

	size_t n{};
	while (array[n] == nullptr && n < bcount)
		n++;

	res.nbucket = n;
	if (n < bcount)
		res.item = array[n];
	else
		res.item = nullptr;

	return res;
}


template <typename T>
typename HashArrayV2<T>::iterator HashArrayV2<T>::end (void) {

	iterator res{};
	res.item = nullptr;
	res.array = nullptr;
	return res;
}


template <typename T>
HashArrayV2<T>::iterator::~iterator () {
}


#endif
