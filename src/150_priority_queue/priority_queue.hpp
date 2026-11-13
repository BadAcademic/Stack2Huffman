#ifndef _PRIORITYQUEUE_
#define _PRIORITYQUEUE_

#include "red_black_tree_multi.hpp"


template <typename T>
class PriorityQueue : public RedBlackTreeMulti<T> {

public:

    PriorityQueue () = default;
    PriorityQueue (const std::initializer_list<T>&);
    PriorityQueue (const PriorityQueue& o);
    PriorityQueue (PriorityQueue&& o) noexcept;
    PriorityQueue& operator= (const PriorityQueue&);
    PriorityQueue& operator= (PriorityQueue&&) noexcept;
    ~PriorityQueue ();

    template <typename U>
    void push (U&&);

    T& front ();

    void pop ();
};


template <typename T>
PriorityQueue<T>::PriorityQueue (const std::initializer_list<T>& l) : RedBlackTreeMulti<T>::RedBlackTreeMulti (l) {

}


template <typename T>
PriorityQueue<T>::PriorityQueue (const PriorityQueue& o) : RedBlackTreeMulti<T>::RedBlackTreeMulti (o) {

}


template <typename T>
PriorityQueue<T>::PriorityQueue (PriorityQueue&& o) noexcept : RedBlackTreeMulti<T>::RedBlackTreeMulti (std::move (o)) {

}


template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator= (const PriorityQueue& o) {

    if (this == &o)
        return *this;

    RedBlackTreeMulti<T>::operator= (o);

    return *this;
}


template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator= (PriorityQueue&& o) noexcept {

    if (this == &o)
        return *this;

    RedBlackTreeMulti<T>::operator= (std::move (o));

    return *this;
}


template <typename T>
PriorityQueue<T>::~PriorityQueue () {

}


template <typename T>
template <typename U>
void PriorityQueue<T>::push (U&& data) {

    RedBlackTreeMulti<T>::insert (std::forward<U>(data));
}


template <typename T>
T& PriorityQueue<T>::front () {

    typename RedBlackTreeMulti<T>::Node* n{RedBlackTreeMulti<T>::root};
    while (n->l != nullptr)
        n = n->l;

    return n->data.front();
}


template <typename T>
void PriorityQueue<T>::pop () {

    typename RedBlackTreeMulti<T>::Node* n{RedBlackTreeMulti<T>::root};
    while (n->l != nullptr)
        n = n->l;

    RedBlackTreeMulti<T>::erase (n);
}

#endif