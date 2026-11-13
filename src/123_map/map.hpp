#ifndef _MAPL_
#define _MAPL_

#include "pair.hpp"
#include "red_black_tree.hpp"


template <typename T, typename U>
class Map : public RedBlackTree<Pair<T, U>> {

public:

    Map () = default;
    Map (const std::initializer_list<Pair<T, U>>&);
    Map (const Map& o);
    Map (Map&& o) noexcept;
    Map& operator= (const Map&);
    Map& operator= (Map&&) noexcept;
    ~Map ();

    template <typename V, typename W>
    bool insert (V&&, W&&);

    Pair<T, U>* find (const T&);

    bool erase (const T&);
};


template <typename T, typename U>
Map<T, U>::Map (const std::initializer_list<Pair<T, U>>& l) : RedBlackTree<Pair<T, U>>::RedBlackTree (l) {

}


template <typename T, typename U>
Map<T, U>::Map (const Map& o) : RedBlackTree<Pair<T, U>>::RedBlackTree (o) {

}


template <typename T, typename U>
Map<T, U>::Map (Map&& o) noexcept : RedBlackTree<Pair<T, U>>::RedBlackTree (std::move (o)) {

}


template <typename T, typename U>
Map<T, U>& Map<T, U>::operator= (const Map& o) {

    if (this == &o)
        return *this;

    RedBlackTree<Pair<T, U>>::operator= (o);

    return *this;
}


template <typename T, typename U>
Map<T, U>& Map<T, U>::operator= (Map&& o) noexcept {

    if (this == &o)
        return *this;

    RedBlackTree<Pair<T, U>>::operator= (std::move (o));

    return *this;
}


template <typename T, typename U>
Map<T, U>::~Map () {

}


template <typename T, typename U>
template <typename V, typename W>
bool Map<T, U>::insert (V&& a, W&& b) {	

    Pair<T, U> pair {std::forward<V> (a), std::forward<W> (b)};
    return RedBlackTree<Pair<T, U>>::insert (std::move(pair));
}


template <typename T, typename U>
Pair<T, U>* Map<T, U>::find (const T& key) {    
    
    return RedBlackTree<Pair<T, U>>::find (Pair<T, U> (key, U ()));
}


template <typename T, typename U>
bool Map<T, U>::erase (const T& key) {

    Pair<T, U> pair (key, U());
    return RedBlackTree<Pair<T, U>>::erase (pair);
}

#endif