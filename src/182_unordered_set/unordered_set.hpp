#ifndef _UNORDEREDSETL_
#define _UNORDEREDSETL_

#include <initializer_list>

#include "hash_array_v2.hpp"


template <typename T>
class UnorderedSet : public HashArrayV2<T> {

public:

    UnorderedSet () = default;
    UnorderedSet (const std::initializer_list<T>&);
    UnorderedSet (const UnorderedSet& o);
    UnorderedSet (UnorderedSet&& o) noexcept;
    UnorderedSet& operator= (const UnorderedSet&);
    UnorderedSet& operator= (UnorderedSet&&) noexcept;
    ~UnorderedSet ();
};


template <typename T>
UnorderedSet<T>::UnorderedSet (const std::initializer_list<T>& l) : HashArrayV2<T>::HashArrayV2 (l) {

}


template <typename T>
UnorderedSet<T>::UnorderedSet (const UnorderedSet& o) : HashArrayV2<T>::HashArrayV2 (o) {

}


template <typename T>
UnorderedSet<T>::UnorderedSet (UnorderedSet&& o) noexcept : HashArrayV2<T>::HashArrayV2 (std::move (o)) {

}


template <typename T>
UnorderedSet<T>& UnorderedSet<T>::operator= (const UnorderedSet& o) {

    if (this == &o)
        return *this;

    HashArrayV2<T>::operator= (o);

    return *this;
}


template <typename T>
UnorderedSet<T>& UnorderedSet<T>::operator= (UnorderedSet&& o) noexcept {

    if (this == &o)
        return *this;

    HashArrayV2<T>::operator= (std::move (o));

    return *this;
}


template <typename T>
UnorderedSet<T>::~UnorderedSet () {

}

#endif
