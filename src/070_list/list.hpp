#ifndef _LISTL_
#define _LISTL_

#include <format>
#include <fstream>
#include <initializer_list>

#include "gexception.h"


template <typename T>
class List {

public:

	List () = default;
	List (std::initializer_list<T>);
	List (const List&);
	List (List&&) noexcept;
	List& operator= (const List&);
	List& operator= (List&&) noexcept;
	~List ();

#ifdef _UNIREF_
	template <typename U>
	void push_front (U&&);
	template <typename U>
	void push_back (U&&);
#endif

#ifndef _UNIREF_
	void push_front (T&&);
	void push_front (const T&);
	void push_back (T&&);
	void push_back (const T&);
#endif

	template <class... U>
	void emplace_front (U&&...);
	template <class... U>
	void emplace_back (U&&...);

	void pop_front ();
	void pop_back ();

	void splice_e2e (List&);

	T& front ();
	T& back ();

	T* find (const T&);
	bool erase (const T&);

	bool empty () const;

	void clear ();

	size_t size () const;

	class iterator;

	iterator begin ();
	iterator end ();

private:

	void copy (const List&);

	struct Element {

#ifdef _UNIREF_
		template <typename U>
		explicit Element (U&& data) : data(std::forward<U>(data)) {};
#endif

#ifndef _UNIREF_
		explicit Element (T&& data) : data(std::move(data)) {};
		explicit Element (const T& data) : data(data) {};
#endif

		template <class... U>
		explicit Element (U&&... args) : data (std::forward<U> (args)...) {};

		T data;
		Element* r{};
		Element* l{};
	};

	size_t msize{};
	Element* pfront{};
	Element* pback{};
};


template <typename T>
List<T>::List (std::initializer_list<T> l) {

	for (auto& o : l)
		push_back(o);
}


template <typename T>
void List<T>::copy (const List& o) {

	if (o.pfront != nullptr) {

		Element* dst{};
		Element* src{o.pfront};
		Element* ldst{};
		while (src != nullptr) {

			dst = new(std::nothrow) Element (src->data);
			if (dst == nullptr)
				throw gexception (gexception::MemAlloc);

			if (src->l == nullptr)
				pfront = dst;

			if (ldst != nullptr) {			
				ldst->r = dst;
				dst->l = ldst;
			}
			ldst = dst;
			src = src->r;
		} 
		
		pback = dst;
	}

	msize = o.msize;
}


template <typename T>
void List<T>::clear () {

	while (pfront != nullptr) {
		
		Element* e{pfront};
		pfront = pfront->r;
		delete e;
	}
	pback = nullptr;
	msize = 0;
}


template <typename T>
List<T>::List (const List& o) {

	copy(o);
}


template <typename T>
List<T>::List (List&& o) noexcept {

	pfront = o.pfront;
	o.pfront = nullptr;
	pback = o.pback;
	o.pback = nullptr;

	msize = o.msize;
	o.msize = 0;
}


template <typename T>
List<T>& List<T>::operator= (const List& o) {

	if (this == &o)
		return *this;

	clear();
	copy(o);

	return *this;
}


template <typename T>
List<T>& List<T>::operator= (List&& o) noexcept {

	if (this == &o)
		return *this;

	clear();

	pfront = o.pfront;
	o.pfront = nullptr;
	pback = o.pback;
	o.pback = nullptr;

	msize = o.msize;
	o.msize = 0;

	return *this;
}


#ifdef _UNIREF_
template <typename T>
template <typename U>
void List<T>::push_front (U&& data) {
	
	Element* e = new(std::nothrow) Element(std::forward<U>(data));
	if (e == nullptr)
		throw gexception(gexception::MemAlloc);

	if (msize > 0) {
		pfront->l = e;
		e->r = pfront;
	}
	else {
		pback = e;
	}

	pfront = e;
	msize++;
}


template <typename T>
template <typename U>
void List<T>::push_back (U&& data) {
	
	Element* e = new(std::nothrow) Element(std::forward<U>(data));
	if (e == nullptr)
		throw gexception(gexception::MemAlloc);

	if (msize > 0) {
		pback->r = e;
		e->l = pback;
	}
	else {
		pfront = e;
	}

	pback = e;
	msize++;
}
#endif


#ifndef _UNIREF_
template <typename T>
void List<T>::push_front (T&& data) {
	
	Element* e = new(std::nothrow) Element(std::move(data));
	if (e == nullptr)
		throw gexception(gexception::MemAlloc);

	if (msize > 0) {
		pfront->l = e;
		e->r = pfront;
	}
	else {
		pback = e;
	}

	pfront = e;
	msize++;
}


template <typename T>
void List<T>::push_front (const T& data) {
	
	Element* e = new(std::nothrow) Element(data);
	if (e == nullptr)
		throw gexception(gexception::MemAlloc);

	if (msize > 0) {
		pfront->l = e;
		e->r = pfront;
	}
	else {
		pback = e;
	}

	pfront = e;
	msize++;
}


template <typename T>
void List<T>::push_back (T&& data) {
	
	Element* e = new(std::nothrow) Element(std::move(data));
	if (e == nullptr)
		throw gexception(gexception::MemAlloc);

	if (msize > 0) {
		pback->r = e;
		e->l = pback;
	}
	else {
		pfront = e;
	}

	pback = e;
	msize++;
}


template <typename T>
void List<T>::push_back (const T& data) {
	
	Element* e = new(std::nothrow) Element(data);
	if (e == nullptr)
		throw gexception(gexception::MemAlloc);

	if (msize > 0) {
		pback->r = e;
		e->l = pback;
	}
	else {
		pfront = e;
	}

	pback = e;
	msize++;
}
#endif


template <typename T>
template <class... U>
void List<T>::emplace_front (U&&... args) {

	Element* e = new(std::nothrow) Element (std::forward<U> (args)...);
	if (e == nullptr)
		throw gexception (gexception::MemAlloc);

	if (msize > 0) {
		pfront->l = e;
		e->r = pfront;
	}
	else {
		pback = e;
	}

	pfront = e;
	msize++;
}


template <typename T>
template <class... U>
void List<T>::emplace_back (U&&... args) {

	Element* e = new(std::nothrow) Element (std::forward<U> (args)...);
	if (e == nullptr)
		throw gexception (gexception::MemAlloc);

	if (msize > 0) {
		pback->r = e;
		e->l = pback;
	}
	else {
		pfront = e;
	}

	pback = e;
	msize++;
}


template <typename T>
inline void List<T>::pop_front () {
	
	if (msize > 0) {

		msize--;
		Element* e{pfront};
		pfront = pfront->r;
		delete e;

		if (msize == 0)
			pback = nullptr;
		else
			pfront->l = nullptr;
	}
}


template <typename T>
void List<T>::pop_back () {
	
	if (msize > 0) {

		msize--;
		Element* e{pback};
		pback = pback->l;
		delete e;

		if (msize == 0)
			pfront = nullptr;
		else
			pback->r = nullptr;
	}
}


template <typename T>
T& List<T>::front () {
	
	return pfront->data;
}


template <typename T>
T& List<T>::back () {
	
	return pback->data;
}


template <typename T>
T* List<T>::find (const T& data) {

	Element* e{pfront};
	if (e != nullptr) {
		while (true) {

			if (data != e->data) {

				if (e->r == nullptr)
					break;
				else
					e = e->r;
			}
			else
				return &e->data;			
		}
	}
	return nullptr;
}


template <typename T>
bool List<T>::erase (const T& data) {

	Element* e{pfront};
	if (e != nullptr) {

		while (true) {

			if (data != e->data) {

				if (e->r == nullptr)
					return false;
				else
					e = e->r;
			}
			else
				break;
		}

		uint8_t f{};
		Element*& l{e->l};
		Element*& r{e->r};
		if (l != nullptr)
			f = uint8_t (1);
		if (r != nullptr)
			f = f | uint8_t (2);

		switch (f) {
		case 0:
			pfront = nullptr;
			pback = nullptr;
			break;
		case 1:
			pback = l;
			l->r = nullptr;
			break;
		case 2:
			pfront = r;
			r->l = nullptr;
			break;
		case 3:
			l->r = r;
			r->l = l;
			break;
		}

		delete e;
		msize--;

		return true;
	}
	
	return false;
}


template <typename T>
void List<T>::splice_e2e (List& l) {

	if (l.pback == nullptr)
		return;

	Element* lb = l.pback;
	if (lb->l != nullptr) {
		lb->l->r = nullptr;
		l.pback = lb->l;
	}
	else {
		l.pback = nullptr;
		l.pfront = nullptr;
	}


	if (pback == nullptr) {
		pback = lb;
		pfront = pback;
		lb->l = nullptr;
		lb->r = nullptr;
	}
	else {
		pback->r = lb;
		lb->l = pback;
		pback = lb;
	}
	msize++;

	l.msize--;
}


template <typename T>
bool List<T>::empty () const {
	
	return msize == 0;
}


template <typename T>
size_t List<T>::size () const {
	
	return msize;
}


template <typename T>
List<T>::~List () {
	
	clear();
}


template <typename T>
class List<T>::iterator {

public:

	iterator& operator++ ();

	bool operator!= (const iterator&) const;

	T& operator* ();

private:

	Element* c{};
	Element* pback{};

	friend iterator List<T>::begin ();
	friend iterator List<T>::end ();
};


template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++ () {
	
	if (c != nullptr)
		c = c->r;

	return *this;
}


template <typename T>
bool List<T>::iterator::operator!= (const iterator& it) const {
	
	return c != it.c ? true : false;
}


template <typename T>
T& List<T>::iterator::operator* () {
	
	return c->data;
}


template <typename T>
typename List<T>::iterator List<T>::begin () {
	
	iterator it{};
	it.c = pfront;
	it.pback = pback;

	return it;
}


template <typename T>
typename List<T>::iterator List<T>::end () {
	
	iterator it{};
	it.c = nullptr;

	return it;
}


template <typename T>
std::ostream& operator<< (std::ostream& out, List<T>& o) {

	out << "{";
	if (!o.empty()) {
		for (auto& d : o)
			out << d << ", ";
	}
	out << "\b\b}";

	return out;
}


template <typename T>
struct std::formatter<List<T>> : std::formatter<std::string> {

	auto format (List<T> o, format_context& ctx) const {

		std::string str = "{";
		if (!o.empty ()) {
			for (auto& d : o)
				str += std::format ("{}, ", d);
		}
		str.resize (str.size () - 1);
		str[str.size() - 1] = '}';

		return formatter<string>::format (std::format ("{}", str), ctx);
	}
};


#endif
