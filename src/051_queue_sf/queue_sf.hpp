#ifndef _QUEUESF_
#define _QUEUESF_

#include "gexception.h"


template <typename T>
class QueueSF {

public:

	QueueSF () = default;
	QueueSF (const QueueSF&) = delete;
	QueueSF operator= (const QueueSF&) = delete;
	~QueueSF ();

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

	Element* res{};
};


template <typename T>
void QueueSF<T>::push (const T& data) {
	
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

	new (pback->data + nback * sizeof (T)) T (data);
	msize++;
}


template <typename T>
void QueueSF<T>::pop () {
	
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
T& QueueSF<T>::front () {
	
	return reinterpret_cast<T*>(pfront->data)[nfront];
}


template <typename T>
bool QueueSF<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t QueueSF<T>::size () const {

	return msize;
}


template <typename T>
QueueSF<T>::~QueueSF () {
	
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
