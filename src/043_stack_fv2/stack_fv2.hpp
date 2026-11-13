#ifndef _STACKF_
#define _STACKF_

#include "gexception.h"


template <typename T>
class StackFv2 {

public:

	StackFv2 () = default;
	StackFv2 (const StackFv2&) = delete;
	StackFv2 operator= (const StackFv2&) = delete;
	~StackFv2 ();

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
};


template <typename T>
void StackFv2<T>::push (const T& data) {

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

	new (ptop->data + ntop * sizeof (T)) T(data);
	msize++;
}


template <typename T>
void StackFv2<T>::pop () {
	
	if (msize > 0) 	{
		
		reinterpret_cast<T*>(ptop->data)[ntop].~T ();

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
T& StackFv2<T>::top () {
	
	return reinterpret_cast<T*>(ptop->data)[ntop];
}


template <typename T>
bool StackFv2<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t StackFv2<T>::size () const {
	
	return msize;
}


template <typename T>
StackFv2<T>::~StackFv2 () {
	
	while (ptop != nullptr) 	{
		
		for (int i{ntop}; i < bsize; i++)
			reinterpret_cast<T*>(ptop->data)[i].~T ();
		ntop = 0;

		Element* e = ptop;
		ptop = ptop->n;
		delete e;
	}
}

#endif
