#ifndef _HASHARRAYMULTI_
#define _HASHARRAYMULTI_

#include <fstream>
#include <iostream>

#include "list.hpp"
#include "stack.hpp"
#include "gexception.h"
#include "ghash.hpp"


template <typename T>
class HashArrayMulti {

public:

	HashArrayMulti ();
	HashArrayMulti (const std::initializer_list<T>&);
	HashArrayMulti (const HashArrayMulti&);
	HashArrayMulti (HashArrayMulti&&) noexcept;
	HashArrayMulti& operator= (const HashArrayMulti&);
	HashArrayMulti& operator= (HashArrayMulti&&) noexcept;
	~HashArrayMulti ();

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

		Item* r{};
		List<T> data{};
	};

	void copy (const HashArrayMulti&);

	void clearAll () noexcept;

	void rehash ();

	Item** array{};

	Stack<Item*> eitems;

	size_t bcount{8};

	size_t msize{};
	size_t musize{};
	float maxloadfactor{1};

	static const size_t cbcount;
	static const float cmaxloadfactor;
};


template <typename T>
const size_t HashArrayMulti<T>::cbcount{8};
template <typename T>
const float HashArrayMulti<T>::cmaxloadfactor{1};


template <typename T>
HashArrayMulti<T>::HashArrayMulti () {

	array = new (std::nothrow) Item * [bcount] ();
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

}


template <typename T>
HashArrayMulti<T>::HashArrayMulti (const std::initializer_list<T>& l) {

	array = new (std::nothrow) Item * [bcount] ();
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (auto& e : l)
		insert (e);
}


template <typename T>
HashArrayMulti<T>::HashArrayMulti (const HashArrayMulti& o) {

	copy (o);
}


template <typename T>
HashArrayMulti<T>::HashArrayMulti (HashArrayMulti&& o) noexcept {

	msize = o.msize;
	o.msize = 0;
	musize = o.musize;
	o.musize = 0;
	bcount = o.bcount;
	o.bcount = cbcount;
	maxloadfactor = o.maxloadfactor;
	o.maxloadfactor = cmaxloadfactor;

	array = o.array;
	o.array = nullptr;
}


template <typename T>
HashArrayMulti<T>& HashArrayMulti<T>::operator= (const HashArrayMulti& o) {

	if (this == &o)
		return *this;

	clearAll ();
	copy (o);

	return *this;
}


template <typename T>
HashArrayMulti<T>& HashArrayMulti<T>::operator= (HashArrayMulti&& o) noexcept {

	if (this == &o)
		return *this;

	clearAll ();

	msize = o.msize;
	o.msize = 0;
	musize = o.musize;
	o.musize = 0;
	bcount = o.bcount;
	o.bcount = cbcount;
	maxloadfactor = o.maxloadfactor;
	o.maxloadfactor = cmaxloadfactor;

	array = o.array;
	o.array = nullptr;

	return *this;
}


template <typename T>
HashArrayMulti<T>::~HashArrayMulti () {

	clearAll ();
}


template <typename T>
void HashArrayMulti<T>::copy (const HashArrayMulti& o) {

	msize = o.msize;
	musize = o.musize;
	bcount = o.bcount;
	maxloadfactor = o.maxloadfactor;

	array = new (std::nothrow) Item * [bcount] ();
	if (array == nullptr)
		throw gexception (gexception::MemAlloc);

	for (size_t i{}; i < bcount; i++) {

		if (o.array[i] != nullptr) {

			Item* sitem{o.array[i]};
			Item* ditem{};
			while (sitem != nullptr) {

				Item* nitem = new (std::nothrow) Item;
				nitem->data = sitem->data;
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
bool HashArrayMulti<T>::insert (U&& data) {

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};
	if (item != nullptr) {
		while (true) {

			if (item->data.front() != data) {

				if (item->r != nullptr)
					item = item->r;
				else
					break;
			}
			else {
				msize++;
				item->data.push_back (std::forward<U> (data));
				return true;
			}
		}
	}

	Item* nitem{};
	if (!eitems.empty ()) {

		nitem = eitems.top ();
		eitems.pop ();
		nitem->r = nullptr;
	}
	else {
		nitem = new (std::nothrow) Item;
		if (nitem == nullptr)
			throw gexception (gexception::MemAlloc);
	}
	nitem->data.push_back (std::forward<U> (data));

	if (array[key] != nullptr)
		item->r = nitem;
	else
		array[key] = nitem;

	msize++;
	musize++;
	if (musize > maxloadfactor * bcount)
		rehash ();

	return true;
}


template <typename T>
template <typename... U>
bool HashArrayMulti<T>::emplace (U&&... args) {

	Item* nitem{};
	bool fres{};
	if (!eitems.empty ()) {

		nitem = eitems.top ();
		nitem->r = nullptr;
		fres = true;
	}
	else {
		nitem = new (std::nothrow) Item;
		if (nitem == nullptr)
			throw gexception (gexception::MemAlloc);
	}
	nitem->data.emplace_back (std::forward<U> (args)...);

	T& data = nitem->data.front ();

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};
	if (item != nullptr) {
		while (true) {

			if (item->data.front () != data) {

				if (item->r != nullptr)
					item = item->r;
				else
					break;
			}
			else {
				msize++;
				item->data.splice_e2e (nitem->data);
				if (!fres)
					delete nitem;
				return true;
			}
		}
	}
	if (fres)
		eitems.pop ();

	if (array[key] != nullptr)
		item->r = nitem;
	else
		array[key] = nitem;

	msize++;
	musize++;
	if (musize > maxloadfactor * bcount)
		rehash ();

	return true;
}


template <typename T>
bool HashArrayMulti<T>::erase (const T& data) noexcept {

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};
	if (item != nullptr) {

		if (item->r == nullptr) {
			if (item->data.front () != data)
				return false;		
			else {
				item->data.pop_front ();
				if (item->data.empty ()) {
					eitems.push (item);
					array[key] = nullptr;
					musize--;
				}
				msize--;
				return true;
			}
		}
		else {

			Item** pitem{array + key};
			while (item != nullptr) {

				if (item->data.front () != data) {

					pitem = &item->r;
					item = item->r;
				}
				else {

					item->data.pop_front ();
					if (item->data.empty ()) {
						*pitem = item->r;
						eitems.push (item);
						musize--;
					}
					msize--;
					return true;
				}
			}
		}
	}
	return false;
}


template <typename T>
T* HashArrayMulti<T>::find (const T& data) const noexcept {

	size_t key = hasher (data) % bcount;

	Item* item{array[key]};

	while (item != nullptr) {

		if (item->data.front () == data)
			return &item->data.front ();
		else
			item = item->r;
	}

	return nullptr;
}


template <typename T>
size_t HashArrayMulti<T>::size () const noexcept {

	return msize;
}


template <typename T>
void HashArrayMulti<T>::print () const noexcept {

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
bool HashArrayMulti<T>::empty () const noexcept {

	return msize == 0 ? true : false;
}


template <typename T>
void HashArrayMulti<T>::clear () noexcept {

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
	musize = 0;
}


template <typename T>
void HashArrayMulti<T>::clearAll () noexcept {

	clear ();

	if (array != nullptr)
		delete[] array;
	array = nullptr;
}


template <typename T>
float HashArrayMulti<T>::max_load_factor () const noexcept {

	return maxloadfactor;
}


template <typename T>
void HashArrayMulti<T>::max_load_factor (float f) const noexcept {

	maxloadfactor = f;
}


template <typename T>
void HashArrayMulti<T>::rehash () {

	int new_bcount{};
	if (bcount == 8)
		new_bcount = 64;
	else if (bcount == 64)
		new_bcount = 512;
	else
		new_bcount = bcount * 2;

	Item** new_array = new (std::nothrow) Item * [new_bcount] ();
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

			size_t key = hasher (titem->data.front ()) % bcount;
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
class HashArrayMulti<T>::iterator {

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

	friend iterator HashArrayMulti<T>::begin (void);
	friend iterator HashArrayMulti<T>::end (void);

	Item** array{};
	size_t nbucket;
	size_t bcount;
	Item* item;
	List<T>::iterator sitem;
};


template <typename T>
HashArrayMulti<T>::iterator::iterator () {

}


template <typename T>
HashArrayMulti<T>::iterator::iterator (const iterator& iterator) {

	nbucket = iterator.nbucket;
	bcount = iterator.bcount;
	item = iterator.item;
}


template <typename T>
typename HashArrayMulti<T>::iterator& HashArrayMulti<T>::iterator::operator= (const iterator& iterator) {

	if (this == &iterator)
		return (*this);

	nbucket = iterator.nbucket;
	bcount = iterator.bcount;
	item = iterator.item;

	return (*this);
}


template <typename T>
typename HashArrayMulti<T>::iterator& HashArrayMulti<T>::iterator::operator++ () {

	++sitem;
	if (sitem != array[nbucket]->data.end ());
	else {

		if (item->r != nullptr)
			item = item->r;

		else if (nbucket < bcount - 1) {

			while (nbucket < bcount - 1) {

				nbucket++;
				if (array[nbucket] != nullptr) {
					item = array[nbucket];
					sitem = item->data.begin ();
					break;
				}
			}
		}
		else
			item = nullptr;
	}

	return (*this);
}


template <typename T>
bool HashArrayMulti<T>::iterator::operator!= (const iterator& iterator) const {

	if (sitem != iterator.sitem)
		return true;
	else
		return false;
}


template <typename T>
T& HashArrayMulti<T>::iterator::operator* () {

	return *sitem;
}


template <typename T>
T* HashArrayMulti<T>::iterator::operator-> () {

	return &*sitem;
}


template <typename T>
typename HashArrayMulti<T>::iterator HashArrayMulti<T>::begin (void) {

	iterator res{};
	res.array = HashArrayMulti<T>::array;
	res.bcount = HashArrayMulti<T>::bcount;

	size_t n{};
	while (array[n] == nullptr && n < bcount)
		n++;

	res.nbucket = n;
	if (n < bcount) {
		res.item = array[n];
		res.sitem = res.item->data.begin ();
	}
	else
		res.item = nullptr;

	return res;
}


template <typename T>
typename HashArrayMulti<T>::iterator HashArrayMulti<T>::end (void) {

	iterator res{};
	res.item = nullptr;
	res.array = nullptr;
	return res;
}


template <typename T>
HashArrayMulti<T>::iterator::~iterator () {
}


#endif
