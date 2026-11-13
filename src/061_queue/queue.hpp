#ifndef _QUEUEL_
#define _QUEUEL_

#include "gexception.h"
#include <initializer_list>


template <typename T>
class Queue {

public:

	Queue () = default;
	Queue (std::initializer_list<T>);
	Queue (const Queue&);
	Queue (Queue&&) noexcept;
	Queue& operator= (const Queue&);
	Queue& operator= (Queue&&) noexcept;
	~Queue ();

	template <typename U>
	void push (U&&);

	void pop ();

	T& front ();

	bool empty () const;

	size_t size () const;

private:

	static const uint8_t bsize{128};

	void copy (const Queue&);

	void clear ();

	struct Element {

		char data[bsize * sizeof (T)];
		Element* r{};
	};
	
	size_t msize{};
	Element* pfront{};
	Element* pback{};
	uint8_t nfront{};
	uint8_t nback{};

	Element* res{};
};


template <typename T>
Queue<T>::Queue (std::initializer_list<T> l) {

	for (auto& o : l)
		push(o);
}


template <typename T>
void Queue<T>::copy (const Queue& o) {

	if (o.pfront != nullptr) {

		Element* dst{};
		Element* src{o.pfront};
		Element* ldst{};
		bool chunk{true};
		do {
			dst = new(std::nothrow) Element;
			if (dst == nullptr)
				throw gexception (gexception::MemAlloc);

			int be{};
			if (chunk) {
				be = o.nfront;
				pfront = dst;
			}
			else
				be = 0;

			int en = src->r == nullptr ? o.nback : bsize - 1;
			for (int i{be}; i <= en; i++)
				new (dst->data + i * sizeof (T)) T (reinterpret_cast<T*>(src->data)[i]);

			if (ldst != nullptr)
				ldst->r = dst;

			ldst = dst;
			chunk = false;

			src = src->r;
		} while (src != nullptr);

		pback = dst;
		msize = o.msize;
		nfront = o.nfront;
		nback = o.nback;
	}
}


template <typename T>
void Queue<T>::clear () {

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
Queue<T>::Queue (const Queue& o) {

	copy(o);
}


template <typename T>
Queue<T>::Queue (Queue&& o) noexcept {

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
Queue<T>& Queue<T>::operator= (const Queue& o) {

	if (this == &o)
		return *this;

	clear();
	copy(o);

	return *this;
}


template <typename T>
Queue<T>& Queue<T>::operator= (Queue&& o) noexcept {

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
void Queue<T>::push(U&& data) {
	
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
			nfront = nback;
		}
		else
			pback->r = e;
		
		pback = e;
	}
	else
		nback++;

	new (pback->data + nback * sizeof (T)) T (std::forward<U>(data));
	msize++;
}


template <typename T>
void Queue<T>::pop () {
	
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
			if (pfront == nullptr)
				pback = nullptr;
			res->r = e;
			nfront = 0;
		}
		else
			nfront++;
	}
}


template <typename T>
T& Queue<T>::front () {
	
	return reinterpret_cast<T*>(pfront->data)[nfront];
}


template <typename T>
bool Queue<T>::empty () const {
	
	if (msize == 0)
		return (true);
	else
		return (false);
}


template <typename T>
size_t Queue<T>::size () const {
	
	return msize;
}


template <typename T>
Queue<T>::~Queue () {
	
	clear();
}

#endif
