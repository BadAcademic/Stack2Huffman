#ifndef _DEQUEF_
#define _DEQUEF_

#include "gexception.h"


template <typename T>
class DequeF {

public:

	DequeF () = default;
	DequeF (const DequeF&) = delete;
	DequeF operator= (const DequeF&) = delete;
	~DequeF ();

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

		T data[bsize];
		Element* r{};
		Element* l{};
	};

	size_t msize{};
	Element* pfront{};
	Element* pback{};
	uint8_t nfront{1};
	uint8_t nback{1};
};


template <typename T>
void DequeF<T>::push_front (const T& data) {
	
	if (msize == 0 || msize != 0 && nfront == 0) {

		Element* e = new(std::nothrow) Element;
		if (e == nullptr)
			throw gexception(gexception::MemAlloc);

		nfront = bsize - 1;
		if (msize == 0) {
			pback = e;
			pback->r = nullptr;
			nback = nfront;
		} else {
			pfront->l = e;
			e->r = pfront;
		}

		pfront = e;
	}
	else
		nfront--;

	pfront->data[nfront] = data;
	msize++;
}


template <typename T>
void DequeF<T>::push_back (const T& data) {
	
	if (msize == 0 || msize != 0 && nback == bsize - 1) {

		Element* e = new(std::nothrow) Element;
		if (e == nullptr)
			throw gexception(gexception::MemAlloc);

		nback = 0;

		if (msize == 0) {
			pfront = e;
			pfront->l = nullptr;
			nfront = nback;
		} else {
			pback->r = e;
			e->l = pback;
		}

		pback = e;
	}
	else
		nback++;

	pback->data[nback] = data;
	msize++;
}


template <typename T>
void DequeF<T>::pop_front () {
	
	if (msize > 0) {

		msize--;
		if (nfront == bsize - 1 || msize == 0) {

			Element* e{pfront};
			pfront = pfront->r;
			if (pfront != nullptr)
				pfront->l = nullptr;
			else
				pback = nullptr;
			delete e;
			nfront = 0;
		}
		else
			nfront++;

		if (msize != 0)
			pfront->l = nullptr;
	}
}


template <typename T>
void DequeF<T>::pop_back () {
	
	if (msize > 0) {
		msize--;
		if (nback == 0 || msize == 0) {

			Element* e{pback};
			pback = pback->l;
			if (pback != nullptr)
				pback->r = nullptr;
			else
				pfront = nullptr;
			delete e;
			nback = bsize - 1;
		}
		else
			nback--;
	}
}


template <typename T>
T& DequeF<T>::front () {
	
	return pfront->data[nfront];
}


template <typename T>
T& DequeF<T>::back () {
	
	return pback->data[nback];
}


template <typename T>
bool DequeF<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t DequeF<T>::size () const {
	
	return msize;
}


template <typename T>
DequeF<T>::~DequeF () {
	
	while (pfront != nullptr) {
		
		Element* e{pfront};
		pfront = pfront->r;
		delete e;
	}
}

#endif
