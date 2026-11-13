#ifndef _DEQUEL_
#define _DEQUEL_

#include <format>
#include <iostream>
#include <initializer_list>

#include "gexception.h"


template <typename T>
class Deque {

public:

	Deque () = default;
	Deque (std::initializer_list<T>);
	Deque (const Deque&);
	Deque (Deque&&) noexcept;
	Deque& operator= (const Deque&);
	Deque& operator= (Deque&&) noexcept;
	~Deque ();

	template <typename U>
	void push_front (U&&);
	template <typename U>
	void push_back (U&&);

	void pop_front ();
	void pop_back ();

	T& front ();
	T& back ();

	bool empty () const;

	size_t size () const;

	class iterator;

	iterator begin ();
	iterator end ();

private:

	static const uint8_t bsize{128};

	void copy (const Deque&);

	void clear ();

	struct Element {

		char data[bsize * sizeof (T)];
		Element* r{};
		Element* l{};
	};

	size_t msize{};
	Element* pfront{};
	Element* pback{};
	uint8_t nfront{1};
	uint8_t nback{1};

	Element* res{};
};


template <typename T>
Deque<T>::Deque (std::initializer_list<T> l) {

	for (auto& o : l)
		push_back(o);
}


template <typename T>
void Deque<T>::copy (const Deque& o) {

	if (o.pfront != nullptr) {

		Element* dst{};
		Element* src{o.pfront};
		Element* ldst{};
		do {
			dst = new(std::nothrow) Element;
			if (dst == nullptr)
				throw gexception (gexception::MemAlloc);
			if (src->l == nullptr)
				pfront = dst;

			int be = src->l == nullptr ? o.nfront : 0;
			int en = src->r == nullptr ? o.nback : bsize - 1;
			for (int i{be}; i <= en; i++)
				new (dst->data + i * sizeof (T)) T (reinterpret_cast<T*>(src->data)[i]);

			if (ldst != nullptr) {
				ldst->r = dst;
				dst->l = ldst;
			}
			ldst = dst;

			src = src->r;
		} while (src != nullptr);

		pback = dst;
		msize = o.msize;
		nfront = o.nfront;
		nback = o.nback;
	}
}


template <typename T>
void Deque<T>::clear () {

	int en{bsize - 1};
	while (pfront != nullptr) {
		
		if (pfront->r == nullptr)
			en = nback;

		for (int i{nfront}; i <= en; i++) {
			reinterpret_cast<T*>(pfront->data)[i].~T ();
			msize--;
		}
		nfront = 0;

		Element* e{pfront};
		pfront = pfront->r;
		delete e;
	}

	while (res != nullptr) {
	
		Element* e = res;
		res = res->r;
		delete e;
	}
	msize = 0;
	nfront = 0;
	nback = 0;
}


template <typename T>
Deque<T>::Deque (const Deque& o) {

	copy(o);
}


template <typename T>
Deque<T>::Deque (Deque&& o) noexcept {

	pfront = o.pfront;
	o.pfront = nullptr;
	pback = o.pback;
	o.pback = nullptr;

	msize = o.msize;
	o.msize = 0;
	nfront = o.nfront;
	o.nfront = 0;
	nback = o.nback;
	o.nfront = 0;

	res = nullptr;
	while (o.res != nullptr) {
		
		Element* e = o.res;
		o.res = o.res->r;
		delete e;
	}
}


template <typename T>
Deque<T>& Deque<T>::operator= (const Deque& o) {

	if (this == &o)
		return *this;

	clear();
	copy(o);

	return *this;
}


template <typename T>
Deque<T>& Deque<T>::operator= (Deque&& o) noexcept {

	if (this == &o)
		return *this;

	clear();

	pfront = o.pfront;
	o.pfront = nullptr;
	pback = o.pback;
	o.pback = nullptr;

	msize = o.msize;
	o.msize = 0;
	nfront = o.nfront;
	o.nfront = 0;
	nback = o.nback;
	o.nback = 0;

	res = nullptr;
	while (o.res != nullptr) {
		
		Element* e = o.res;
		o.res = o.res->r;
		delete e;
	}

	return *this;
}


template <typename T>
template <typename U>
void Deque<T>::push_front (U&& data) {
	
	if (msize == 0 || msize != 0 && nfront == 0) {

		Element* e{};
		if (res == nullptr) {

			e = new(std::nothrow) Element;
			if (e == nullptr)
				throw gexception(gexception::MemAlloc);
		}
		else {

			e = res;
			e->l = nullptr;
			res = res->r;
		}

		nfront = bsize - 1;
		if (msize == 0) {
			pback = e;
			pback->r = nullptr;
			nback = nfront;
		}
		else {
			pfront->l = e;
			e->r = pfront;
		}

		pfront = e;
	}
	else
		nfront--;

	new (pfront->data + nfront * sizeof (T)) T (std::forward<U> (data));
	msize++;
}


template <typename T>
template <typename U>
void Deque<T>::push_back(U&& data) {
	
	if (msize == 0 || msize != 0 && nback == bsize - 1) {

		Element* e{};
		if (res == nullptr) {

			e = new(std::nothrow) Element;
			if (e == nullptr)
				throw gexception(gexception::MemAlloc);
		}
		else {

			e = res;
			res = res->r;
			e->r = nullptr;
		}

		nback = 0;
		if (msize == 0) {
			pfront = e;
			pfront->l = nullptr;
			nfront = nback;
		}
		else {
			pback->r = e;
			e->l = pback;
		}

		pback = e;
	}
	else
		nback++;

	new (pback->data + nback * sizeof (T)) T (std::forward<U> (data));
	msize++;
}


template <typename T>
void Deque<T>::pop_front () {
	
	if (msize > 0) {

		reinterpret_cast<T*>(pfront->data)[nfront].~T ();

		msize--;
		if (nfront == bsize - 1 || msize == 0) {

			Element* e;

			if (res == nullptr)
				e = nullptr;
			else 
				e = res;			

			res = pfront;
			pfront = pfront->r;
			if (pfront != nullptr)
				pfront->l = nullptr;
			else
				pback = nullptr;
			res->r = e;
			nfront = 0;
		}
		else
			nfront++;
	}
}


template <typename T>
void Deque<T>::pop_back() {

	if (msize > 0) {

		reinterpret_cast<T*>(pback->data)[nback].~T ();

		msize--;
		if (nback == 0 || msize == 0) {

			Element* e;
			if (res == nullptr)
				e = nullptr;
			else 
				e = res;			

			res = pback;
			pback = pback->l;
			if (pback != nullptr)
				pback->r = nullptr;
			else
				pfront = nullptr;
			res->r = e;
			nback = bsize - 1;
		}
		else
			nback--;
	}
}


template <typename T>
T& Deque<T>::front () {
	
	return reinterpret_cast<T*>(pfront->data)[nfront];
}


template <typename T>
T& Deque<T>::back () {
	
	return reinterpret_cast<T*>(pback->data)[nback];
}


template <typename T>
bool Deque<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t Deque<T>::size () const {
	
	return msize;
}


template <typename T>
Deque<T>::~Deque () {
	
	clear();
}


template <typename T>
class Deque<T>::iterator {

public:

	iterator& operator++ ();

	bool operator!= (const iterator&) const;

	T& operator* ();

private:

	Element* c{};
	Element* pback{};
	int idx{};
	int idxb{};

	friend iterator Deque<T>::begin();
	friend iterator Deque<T>::end();
};


template <typename T>
typename Deque<T>::iterator& Deque<T>::iterator::operator++ () {
	
	if (c != nullptr) {

		if (c != pback) {
			if (idx == bsize - 1) {
				c = c->r;
				idx = 0;
			}
			else
				idx++;
		}
		else if (idx < idxb)
			idx++;
		else {
			c = nullptr;
			idx = -1;
		}
	}
	else {
		c = nullptr;
		idx = -1;
	}
	
	return *this;
}


template <typename T>
bool Deque<T>::iterator::operator!= (const iterator& it) const {

	if (c != it.c && idx != it.idx)
		return true;
	else
		return false;
}


template <typename T>
T& Deque<T>::iterator::operator* () {
	
	return reinterpret_cast<T*>(c->data)[idx];
}


template <typename T>
typename Deque<T>::iterator Deque<T>::begin () {

	iterator it{};
	it.c = pfront;
	it.pback = pback;
	it.idx = nfront;
	it.idxb = nback;

	return it;
}


template <typename T>
typename Deque<T>::iterator Deque<T>::end () {

	iterator it{};
	it.c = nullptr;
	it.idx = -1;

	return (it);
}


template <typename T>
std::ostream& operator<< (std::ostream& out, Deque<T>& o) {

	out << "{";
	if (!o.empty ()) {
		for (auto& d : o)
			out << d << ", ";
	}
	out << "\b\b}";

	return out;
}


template <typename T>
struct std::formatter<Deque<T>> : std::formatter<std::string> {

	auto format (Deque<T> o, format_context& ctx) const {

		std::string str = "{";
		if (!o.empty ()) {
			for (auto& d : o)
				str += std::format ("{}, ", d);
		}
		str.resize (str.size () - 1);
		str[str.size () - 1] = '}';

		return formatter<string>::format (std::format ("{}", str), ctx);
	}
};
#endif
