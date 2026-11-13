#ifndef _VECTORL_
#define _VECTORL_

#include <format>
#include <iostream>
#include <initializer_list>

#include "gexception.h"


template <typename T>
class Vector {

public:

	Vector () = default;
	Vector (const std::initializer_list<T>);
	Vector (const Vector&);
	Vector (Vector&&) noexcept;
	Vector& operator= (const Vector&);
	Vector& operator= (Vector&&) noexcept;
	~Vector ();

	template <typename U>
	void push_back (U&&);

	template <class... U>
	void emplace_back (U&&...);

	void pop_back ();

	T& front ();
	T& back ();

	T* data () const noexcept;

	T* find (const T& data);

	void clear ();
	bool empty () const;

	size_t size () const;
	size_t capacity () const;

	void resize (size_t n);
	void reserve (size_t n);

	T& operator[] (size_t n);

	class iterator;

	iterator begin ();
	iterator end ();

private:

	void copy (const Vector&);

	char* rdata{};
	T* tdata{};
	size_t msize{};
	size_t mcapacity{};
};


template <typename T>
Vector<T>::Vector (std::initializer_list<T> l) {

	if (l.size() > 0) {

		msize = l.size();

		rdata = new(std::nothrow) char[msize * sizeof(T)];
		if (rdata == 0)
			throw gexception(gexception::MemAlloc);
		tdata = reinterpret_cast<T*>(rdata);

		size_t n{0};
		for (auto& o : l) {
			new(tdata + n) T(o);
			n++;
		}
		mcapacity = msize;
	}
}


template <typename T>
void Vector<T>::copy (const Vector& o) {

	msize = o.msize;
	mcapacity = o.mcapacity;

	if (o.mcapacity > 0) {

		rdata = new(std::nothrow) char[o.mcapacity * sizeof(T)];
		if(rdata == 0)
			throw gexception(gexception::MemAlloc);

		tdata = reinterpret_cast<T*>(rdata);
		new(tdata) T[msize];
		for (size_t i{0}; i < msize; i++)
			tdata[i] = o.tdata[i];
	}
}


template <typename T>
void Vector<T>::clear () {

	for (size_t i{0}; i < msize; i++)
		tdata[i].~T();

	if (rdata != nullptr)
		delete[] rdata;

	rdata = nullptr;
	tdata = nullptr;

	msize = 0;
	mcapacity = 0;
}


template <typename T>
Vector<T>::Vector(const Vector& o) {

	copy(o);
}


template <typename T>
Vector<T>::Vector (Vector&& o) noexcept {

	msize = o.msize;
	o.msize = 0;
	mcapacity = o.mcapacity;
	o.mcapacity = 0;
	tdata = o.tdata;
	o.tdata = nullptr;
	rdata = o.rdata;
	o.rdata = nullptr;
}


template <typename T>
Vector<T>& Vector<T>::operator= (const Vector& o) {

	if (this == &o)
		return *this;

	clear();
	copy(o);

	return *this;
}


template <typename T>
Vector<T>& Vector<T>::operator= (Vector&& o) noexcept {

	if (this == &o)
		return *this;

	clear();

	msize = o.msize;
	o.msize = 0;
	mcapacity = o.mcapacity;
	o.mcapacity = 0;
	tdata = o.tdata;
	o.tdata = nullptr;
	rdata = o.rdata;
	o.rdata = nullptr;

	return *this;
}


template <typename T>
template <typename U>
void Vector<T>::push_back (U&& data)
{
	if (msize == mcapacity) {

		char* ordata{rdata};

		if (mcapacity == 0)
			mcapacity = 1;
		else
			mcapacity  *= 2;
		rdata = new(std::nothrow) char[mcapacity * sizeof(T)];
		if(rdata == 0)
			throw gexception(gexception::MemAlloc);
		tdata = reinterpret_cast<T*>(rdata);
		
		memcpy(rdata, ordata, msize * sizeof(T));
		if (ordata != nullptr)
			delete[] ordata;
	}
	new(tdata + msize) T(std::forward<U>(data));
	msize++;
}


template <typename T>
template <typename ...U>
void Vector<T>::emplace_back (U&&... args) {

	if (msize == mcapacity) {

		char* ordata{rdata};

		if (mcapacity == 0)
			mcapacity = 1;
		else
			mcapacity *= 2;
		rdata = new(std::nothrow) char[mcapacity * sizeof(T)];
		if (rdata == 0)
			throw gexception(gexception::MemAlloc);
		tdata = reinterpret_cast<T*>(rdata);

		memcpy(rdata, ordata, msize * sizeof(T));
		if (ordata != nullptr)
			delete[] ordata;
	}
	new(tdata + msize) T(std::forward<U>(args)...);
	msize++;
}


template <typename T>
void Vector<T>::pop_back () {
	
	if (msize > 0) {
		msize--;

		tdata[msize].~T();
	}
}


template <typename T>
T& Vector<T>::front () {
	
	return tdata[0];
}


template <typename T>
T& Vector<T>::back () {
	
	return tdata[msize - 1];
}


template <typename T>
T* Vector<T>::data () const noexcept {

	return tdata;
}


template <typename T>
T* Vector<T>::find (const T& data) {

	for (size_t i{}; i < msize; i++) {
		if (tdata[i] == data)
			return tdata + i;
	}
	return nullptr;
}


template <typename T>
bool Vector<T>::empty () const {
	
	if (msize == 0)
		return true;
	else
		return false;
}


template <typename T>
size_t Vector<T>::size () const {
	
	return msize;
}


template <typename T>
void Vector<T>::resize (size_t n) {

	if (n > msize) {

		if (n > mcapacity) {

			char* tmpRawData{rdata};

			mcapacity = n;
			rdata = new(std::nothrow) char[mcapacity * sizeof(T)];
			if (rdata == 0)
				throw gexception(gexception::MemAlloc);

			memcpy(rdata, tmpRawData, msize * sizeof(T));
			delete[] tmpRawData;
			
			tdata = reinterpret_cast<T*>(rdata);
		}
		new(tdata + msize) T[n - msize];
	}
	else if (n < msize) {

		for (auto i{n}; i < msize; i++)
			tdata[i].~T();
	}
	else
		return;

	msize = n;
}


template <typename T>
void Vector<T>::reserve (size_t n) {

	if (n > mcapacity) {

		char* tmpRawData{rdata};

		mcapacity = n;
		rdata = new(std::nothrow) char[mcapacity * sizeof(T)];
		if(rdata == 0)
			throw gexception(gexception::MemAlloc);

		memcpy(rdata, tmpRawData, msize * sizeof(T));

		delete[] tmpRawData;
		tdata = reinterpret_cast<T*>(rdata);
		mcapacity = n;
	}
}


template <typename T>
size_t Vector<T>::capacity () const {

	return mcapacity;
}


template <typename T>
T& Vector<T>::operator[] (size_t n) {

	return tdata[n];
}


template <typename T>
Vector<T>::~Vector() {
	
	clear();
}


template <typename T>
class Vector<T>::iterator {

public:

	iterator& operator++ ();

	bool operator!= (const iterator&) const;

	T& operator* ();

private:

	size_t idx{};
	size_t size{};
	T* tdata{};

	friend iterator Vector<T>::begin ();
	friend iterator Vector<T>::end ();
};


template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator++ () {
	
	if (idx < size)
		idx++;

	return *this;
}


template <typename T>
bool Vector<T>::iterator::operator!= (const iterator& it) const {
	
	return idx != it.idx ? true : false;
}


template <typename T>
T& Vector<T>::iterator::operator* () {
	
	return tdata[idx];
}


template <typename T>
typename Vector<T>::iterator Vector<T>::begin () {
	
	iterator it{};
	it.idx = 0;
	it.size = msize;
	it.tdata = tdata;

	return it;
}


template <typename T>
typename Vector<T>::iterator Vector<T>::end () {
	
	iterator it{};
	it.idx = msize;

	return it;
}


template <typename T>
bool operator== (const Vector<T>& a, const Vector<T>& b) {

	if (a.size() != b.size())
		return false;

	auto n = a.size();
	for (int i{}; i < n; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}


template <typename T>
std::ostream& operator<< (std::ostream& out, Vector<T>& o) {

	out << "[";
	if (!o.empty ()) {
		for (auto& d : o)
			out << d << ", ";
	}
	out << "\b\b]";

	return out;
}


template <typename T>
struct std::formatter<Vector<T>> : std::formatter<std::string> {

	auto format (Vector<T> o, format_context& ctx) const {

		std::string str = "{";
		if (!o.empty ()) {
			for (auto& d : o)
				str += std::format ("{}, ", d);
		}
		str.resize (str.size () - 1);
		str[str.size () - 1] = '}';

		return formatter<string>::format (std::format ("{}", str), ctx);
	}
};


#endif
