#ifndef _MULTISETL_
#define _MULTISETL_

#include <iostream>
#include <initializer_list>

#include "stack.hpp"
#include "red_black_tree_multi.hpp"


template <typename T>
class Multiset : public RedBlackTreeMulti<T> {

public:

    Multiset () = default;
    Multiset (const std::initializer_list<T>&);
    Multiset (const Multiset& o);
    Multiset (Multiset&& o) noexcept;
    Multiset& operator= (const Multiset&);
    Multiset& operator= (Multiset&&) noexcept;
    ~Multiset ();
};


template <typename T>
Multiset<T>::Multiset (const std::initializer_list<T>& l) : RedBlackTreeMulti<T>::RedBlackTreeMulti (l) {

}


template <typename T>
Multiset<T>::Multiset (const Multiset& o) : RedBlackTreeMulti<T>::RedBlackTreeMulti (o) {

}


template <typename T>
Multiset<T>::Multiset (Multiset&& o) noexcept : RedBlackTreeMulti<T>::RedBlackTreeMulti (std::move (o)) {

}


template <typename T>
Multiset<T>& Multiset<T>::operator= (const Multiset& o) {

    if (this == &o)
        return *this;

    RedBlackTreeMulti<T>::operator= (o);    

    return *this;
}


template <typename T>
Multiset<T>& Multiset<T>::operator= (Multiset&& o) noexcept {

    if (this == &o)
        return *this;

    RedBlackTreeMulti<T>::operator= (std::move (o));

    return *this;
}


template <typename T>
Multiset<T>::~Multiset () {

}

#endif
