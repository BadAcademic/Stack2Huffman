#ifndef _QUEUEF_
#define _QUEUEF_

#include "gexception.h"


template <typename T>
class QueueFv2 {

public:

	QueueFv2 () = default;
	QueueFv2 (const QueueFv2&) = delete;
	QueueFv2 operator= (const QueueFv2&) = delete;
	~QueueFv2 ();

	void push (const T&);

	void pop ();

	T& front ();

	bool empty () const;

	size_t size () const;

private:

	static const uint8_t bsize{128};

	struct Element {

		char data[bsize * sizeof (T)];
		Element* r{};
	};

	size_t msize{};
	Element* pfront{};
	Element* pback{};
	uint8_t nfront{};
	uint8_t nback{};
};


template <typename T>
void QueueFv2<T>::push (const T& data) {
	
	if (msize == 0 || msize != 0 && nback == bsize - 1) {

		Element* e = new(std::nothrow) Element;
		if (e == nullptr)
			throw gexception(gexception::MemAlloc);

		nback = 0;

		if (msize == 0) {
			pfront = e;
			nfront = 0;
		} else 
			pback->r = e;

		pback = e;
	} else
		nback++;

	new (pback->data + nback * sizeof (T)) T (data);
	msize++;
}


template <typename T>
void QueueFv2<T>::pop () {
	
	if (msize > 0) {

		reinterpret_cast<T*>(pfront->data)[nfront].~T ();

		msize--;
		if (nfront == bsize - 1 || msize == 0) {

			Element* e{pfront};
			pfront = pfront->r;
			delete e;
			nfront = 0;
		} else
			nfront++;
	}
}


template <typename T>
T& QueueFv2<T>::front () {
	
	return reinterpret_cast<T*>(pfront->data)[nfront];
}


template <typename T>
bool QueueFv2<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t QueueFv2<T>::size () const {
	
	return (msize);
}


template <typename T>
QueueFv2<T>::~QueueFv2 () {
	
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
}

#endif
