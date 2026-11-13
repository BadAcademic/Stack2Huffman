#ifndef _QUEUEF_
#define _QUEUEF_

#include "gexception.h"


template <typename T>
class QueueF {

public:

	QueueF () = default;
	QueueF (const QueueF&) = delete;
	QueueF operator= (const QueueF&) = delete;
	~QueueF ();

	void push (const T&);

	void pop ();

	T& front ();

	bool empty () const;

	size_t size () const;

private:

	static const uint8_t bsize{128};

	struct Element {

		T data[bsize];
		Element* r{};
	};

	size_t msize{};
	Element* pfront{};
	Element* pback{};
	uint8_t nfront{};
	uint8_t nback{};
};


template <typename T>
void QueueF<T>::push (const T& data) {
	
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

	pback->data[nback] = data;
	msize++;
}


template <typename T>
void QueueF<T>::pop () {
	
	if (msize > 0) {

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
T& QueueF<T>::front () {
	
	return pfront->data[nfront];
}


template <typename T>
bool QueueF<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t QueueF<T>::size () const {
	
	return (msize);
}


template <typename T>
QueueF<T>::~QueueF () {
	
	while (pfront != nullptr) {
		Element* e{pfront};
		pfront = pfront->r;
		delete e;
	}
}

#endif
