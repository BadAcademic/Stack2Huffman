#ifndef _STACKSF_
#define _STACKSF_

#include "gexception.h"


template <typename T>
class StackSF {

public:

	StackSF () = default;
	StackSF (const StackSF&) = delete;
	StackSF operator= (const StackSF&) = delete;
	~StackSF ();

	void push (const T&);

	void pop ();

	T& top ();

	bool empty () const;

	size_t size () const;

private:

	static const uint8_t bsize{128};

	struct Element {

		char data[bsize * sizeof (T)];
		Element* n{};
	};

	size_t msize{};
	Element* ptop{};
	uint8_t ntop{};

	Element* res{};
};


template <typename T>
void StackSF<T>::push (const T& data) {
	
	if (ntop == 0) {

		Element* e{};
		if (res == nullptr) {

			e = new(std::nothrow) Element;
			if (e == nullptr)
				throw gexception(gexception::MemAlloc);
		} else {

			e = res;
			res = res->n;
		}

		ntop = bsize - 1;
		if (msize == 0)
			e->n = nullptr;
		else
			e->n = ptop;

		ptop = e;
	}
	else
		ntop--;

	new (ptop->data + ntop * sizeof (T)) T (data);
	msize++;
}


template <typename T>
void StackSF<T>::pop () {
	
	if (msize > 0) {

		reinterpret_cast<T*>(ptop->data)[ntop].~T ();

		msize--;
		if (ntop == bsize - 1) {
			
			if (res == nullptr) {
				res = ptop;
				ptop = ptop->n;
				res->n = nullptr;
			}
			else {
				Element* tmp = res;
				res = ptop;
				ptop = ptop->n;
				res->n = tmp;
			}
			ntop = 0;
		} else
			ntop++;
	}
}


template <typename T>
T& StackSF<T>::top () {
	
	return reinterpret_cast<T*>(ptop->data)[ntop];
}


template <typename T>
bool StackSF<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t StackSF<T>::size () const {
	
	return msize;
}


template <typename T>
StackSF<T>::~StackSF () {
	
	while (ptop != nullptr) {
		
		for (int i{ntop}; i < bsize; i++)
			reinterpret_cast<T*>(ptop->data)[i].~T ();
		ntop = 0;

		Element* e = ptop;
		ptop = ptop->n;
		delete e;
	}

	while (res != nullptr) {
		
		Element* e = res;
		res = res->n;
		delete e;
	}
}

#endif
