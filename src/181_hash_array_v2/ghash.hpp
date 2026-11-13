#ifndef _GHASH_
#define _GHASH_

#include <string>
#include "pair.hpp"

template <typename T>
class ghash : public std::hash<T> {

public:

	template <typename U>
	size_t operator () (const T& o)  const {

		return 1;// std::hash<T>::operator (o.first);
	}


};

#endif