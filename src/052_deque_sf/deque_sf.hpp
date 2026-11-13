#ifndef _DEQUESF_
#define _DEQUESF_

#include "gexception.h"


template <typename T>
class DequeSF {

public:

	DequeSF () = default;
	DequeSF (const DequeSF&) = delete;
	DequeSF operator= (const DequeSF&) = delete;
	~DequeSF ();

	void push_front (const T&);
	void push_back (const T&);

	void pop_front ();
	void pop_back ();

	T& front ();
	T& back ();

	bool empty () const;

	size_t size () const;

private:

	static const uint8_t bsize{128};

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
void DequeSF<T>::push_front (const T& data) {
	
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

	new (pfront->data + nfront * sizeof (T)) T (data);
	msize++;
}


template <typename T>
void DequeSF<T>::push_back (const T& data) {
	
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

	new (pback->data + nback * sizeof (T)) T (data);
	msize++;
}


template <typename T>
void DequeSF<T>::pop_front () {
	
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
void DequeSF<T>::pop_back () {
	
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
T& DequeSF<T>::front () {
	
	return reinterpret_cast<T*>(pfront->data)[nfront];
}


template <typename T>
T& DequeSF<T>::back () {
	
	return reinterpret_cast<T*>(pback->data)[nback];
}


template <typename T>
bool DequeSF<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t DequeSF<T>::size () const {
	
	return msize;
}


template <typename T>
DequeSF<T>::~DequeSF() {

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
}

#endif
