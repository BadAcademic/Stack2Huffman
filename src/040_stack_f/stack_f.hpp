#ifndef _STACKF_
#define _STACKF_

#include "gexception.h"


template <typename T>
class StackF {

public:

	StackF () = default;
	StackF (const StackF&) = delete;
	StackF operator= (const StackF&) = delete;
	~StackF ();

	void push (const T&);

	void pop ();

	T& top ();

	bool empty () const;

	size_t size () const;

private:

	static const uint8_t bsize{3};

	struct Element {

		T data[bsize];
		Element* n{};
	};

	size_t msize{};
	Element* ptop{};
	uint8_t ntop{};
};


template <typename T>
void StackF<T>::push (const T& data) {

	if (ntop == 0) {

		Element* e = new(std::nothrow) Element;
		if (e == nullptr)
			throw gexception(gexception::MemAlloc);

		ntop = bsize - 1;

		if (msize != 0)
			e->n = ptop;

		ptop = e;
	} else
		ntop--;

	ptop->data[ntop] = data;
	msize++;
}


template <typename T>
void StackF<T>::pop () {
	
	if (msize > 0) 	{
		
		if (ntop == bsize - 1) {

			Element* e = ptop;
			ptop = ptop->n;
			delete e;
			ntop = 0;
		} else
			ntop++;

		msize--;
	}
}


template <typename T>
T& StackF<T>::top () {
	
	return ptop->data[ntop];
}


template <typename T>
bool StackF<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t StackF<T>::size () const {
	
	return msize;
}


template <typename T>
StackF<T>::~StackF () {
	
	while (ptop != nullptr) 	{
		
		Element* e = ptop;
		ptop = ptop->n;
		delete e;
	}
}

#endif
