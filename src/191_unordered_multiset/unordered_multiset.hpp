#ifndef _UNORDEREDMULTISETL_
#define _UNORDEREDMULTISETL_

#include <initializer_list>

#include "hash_array_multi.hpp"


template <typename T>
class UnorderedMultiSet : public HashArrayMulti<T> {

public:

    UnorderedMultiSet () = default;
    UnorderedMultiSet (const std::initializer_list<T>&);
    UnorderedMultiSet (const UnorderedMultiSet& o);
    UnorderedMultiSet (UnorderedMultiSet&& o) noexcept;
    UnorderedMultiSet& operator= (const UnorderedMultiSet&);
    UnorderedMultiSet& operator= (UnorderedMultiSet&&) noexcept;
    ~UnorderedMultiSet ();
};


template <typename T>
UnorderedMultiSet<T>::UnorderedMultiSet (const std::initializer_list<T>& l) : HashArrayMulti<T>::HashArrayMulti (l) {

}


template <typename T>
UnorderedMultiSet<T>::UnorderedMultiSet (const UnorderedMultiSet& o) : HashArrayMulti<T>::HashArrayMulti (o) {

}


template <typename T>
UnorderedMultiSet<T>::UnorderedMultiSet (UnorderedMultiSet&& o) noexcept : HashArrayMulti<T>::HashArrayMulti (std::move (o)) {

}


template <typename T>
UnorderedMultiSet<T>& UnorderedMultiSet<T>::operator= (const UnorderedMultiSet& o) {

    if (this == &o)
        return *this;

    HashArrayMulti<T>::operator= (o);

    return *this;
}


template <typename T>
UnorderedMultiSet<T>& UnorderedMultiSet<T>::operator= (UnorderedMultiSet&& o) noexcept {

    if (this == &o)
        return *this;

    HashArrayMulti<T>::operator= (std::move (o));

    return *this;
}


template <typename T>
UnorderedMultiSet<T>::~UnorderedMultiSet () {

}

#endif
