#ifndef _SETL_
#define _SETL_

#include <initializer_list>

#include "red_black_tree.hpp"


template <typename T>
class Set : public RedBlackTree<T> {

public:

    Set () = default;
    Set (const std::initializer_list<T>&);
    Set (const Set& o);
    Set (Set&& o) noexcept;
    Set& operator= (const Set&);
    Set& operator= (Set&&) noexcept;
    ~Set ();
};


template <typename T>
Set<T>::Set (const std::initializer_list<T>& l) : RedBlackTree<T>::RedBlackTree (l) {

}


template <typename T>
Set<T>::Set (const Set& o) : RedBlackTree<T>::RedBlackTree (o) {

}


template <typename T>
Set<T>::Set (Set&& o) noexcept : RedBlackTree<T>::RedBlackTree (std::move (o)) {

}


template <typename T>
Set<T>& Set<T>::operator= (const Set& o) {

    if (this == &o)
        return *this;

    RedBlackTree<T>::operator= (o);

    return *this;
}


template <typename T>
Set<T>& Set<T>::operator= (Set&& o) noexcept {

    if (this == &o)
        return *this;

    RedBlackTree<T>::operator= (std::move (o));

    return *this;
}


template <typename T>
Set<T>::~Set () {

}

#endif
