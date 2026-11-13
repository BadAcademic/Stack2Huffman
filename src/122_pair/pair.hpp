#ifndef _PAIR1_
#define _PAIR1_

#include <format>
#include <iostream>


template <typename T, typename U>
class Pair {

public:

	Pair () {};

	template <typename V, typename W>
	Pair (V&& first, W&& second) : first (std::forward<V> (first)), second (std::forward<W> (second)) {};

	Pair (const Pair&);
	Pair (Pair&&) noexcept;
	Pair& operator= (const Pair&);
	Pair& operator= (Pair&&) noexcept;

	bool operator< (const Pair<T, U>&) const;
	bool operator!= (const Pair<T, U>&) const;
	bool operator== (const Pair<T, U>&) const;

	T first{};
	U second{};
};


template <typename T, typename U>
Pair<T, U>::Pair (const Pair& o) : first(o.first), second(o.second) {}


template <typename T, typename U>
Pair<T, U>::Pair (Pair&& o) noexcept : first (std::move (o.first)), second (std::move (o.second)) {}


template <typename T, typename U>
Pair<T, U>& Pair<T, U>::operator= (const Pair& o) {

	if (this == &o)
		return *this;

	first = o.first;
	second = o.second;

	return *this;
}


template <typename T, typename U>
Pair<T, U>& Pair<T, U>::operator= (Pair&& o) noexcept {

	if (this == &o)
		return *this;

	first = std::move (o.first);
	second = std::move (o.second);

	return *this;
}


template <typename T, typename U>
bool Pair<T, U>::operator< (const Pair<T, U>& pair) const {
	
	if (first < pair.first)
		return true;
	else
		return false;
}


template <typename T, typename U>
bool Pair<T, U>::operator!= (const Pair<T, U>& pair) const {

	if (first != pair.first)
		return true;
	else
		return false;
}


template <typename T, typename U>
bool Pair<T, U>::operator== (const Pair<T, U>& pair) const {
	
	if (first == pair.first)
		return true;
	else
		return false;
}


template <typename T, typename U>
std::ostream& operator<< (std::ostream& out, Pair<T, U>& pair) {

	out << "("  << pair.first << ", " << pair.second << ")";

	return out;
}


template <typename T, typename U>
struct std::formatter<Pair<T, U>> : std::formatter<std::string> {

	auto format (Pair<T, U> p, format_context& ctx) const {

		return formatter<string>::format (std::format ("({}, {})", p.first, p.second), ctx);
	}
};


template <typename T, typename U>
class std::hash<Pair<T, U>> {
public:

	size_t operator() (const Pair<T, U>& o) const {

		std::hash<T> hasher;
		return 	hasher (o.first);
	}
};


#endif