#ifndef _MAPL_
#define _MAPL_

#include "pair.hpp"
#include "red_black_tree_multi.hpp"


template <typename T, typename U>
class Multimap : public RedBlackTreeMulti<Pair<T, U>> {

public:

    Multimap () = default;
    Multimap (const std::initializer_list<Pair<T, U>>&);
    Multimap (const Multimap& o);
    Multimap (Multimap&& o) noexcept;
    Multimap& operator= (const Multimap&);
    Multimap& operator= (Multimap&&) noexcept;
    ~Multimap ();

    template <typename V, typename W>
    bool insert (V&&, W&&);

    template <typename V>
    Pair<T, U>* find (V&&);

    template <typename V>
    bool erase (V&&);
};


template <typename T, typename U>
Multimap<T, U>::Multimap (const std::initializer_list<Pair<T, U>>& l) : RedBlackTreeMulti<Pair<T, U>>::RedBlackTreeMulti (l) {

}


template <typename T, typename U>
Multimap<T, U>::Multimap (const Multimap& o) : RedBlackTreeMulti<Pair<T, U>>::RedBlackTreeMulti (o) {

}


template <typename T, typename U>
Multimap<T, U>::Multimap (Multimap&& o) noexcept : RedBlackTreeMulti<Pair<T, U>>::RedBlackTreeMulti (std::move (o)) {

}


template <typename T, typename U>
Multimap<T, U>& Multimap<T, U>::operator= (const Multimap& o) {

    if (this == &o)
        return *this;

    RedBlackTreeMulti<Pair<T, U>>::operator= (o);

    return *this;
}


template <typename T, typename U>
Multimap<T, U>& Multimap<T, U>::operator= (Multimap&& o) noexcept {

    if (this == &o)
        return *this;

    RedBlackTreeMulti<Pair<T, U>>::operator= (std::move (o));

    return *this;
}


template <typename T, typename U>
Multimap<T, U>::~Multimap () {

}


template <typename T, typename U>
template <typename V, typename W>
bool Multimap<T, U>::insert (V&& a, W&& b) {	

    Pair<T, U> pair {std::forward<V> (a), std::forward<W> (b)};
    return RedBlackTreeMulti<Pair<T, U>>::insert (std::move(pair));
}


template <typename T, typename U>
template <typename V>
Pair<T, U>* Multimap<T, U>::find (V&& key) {    
    
    return RedBlackTreeMulti<Pair<T, U>>::find (Pair<T, U> (std::forward<V> (key), U ()));
}


template <typename T, typename U>
template <typename V>
bool Multimap<T, U>::erase (V&& key) {

    Pair<T, U> pair (std::forward<V>(key), U());
    return RedBlackTreeMulti<Pair<T, U>>::erase (pair);
}

#endif