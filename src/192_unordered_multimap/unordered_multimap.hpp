#ifndef _UNORDEREDMULTIMAPL_
#define _UNORDEREDMULTIMAPL_

#include <initializer_list>

#include "pair.hpp"
#include "hash_array_multi.hpp"


template <typename T, typename U>
class UnorderedMultiMap : public HashArrayMulti<Pair<T, U>> {

public:

    UnorderedMultiMap () = default;
    UnorderedMultiMap (const std::initializer_list<Pair<T, U>>&);
    UnorderedMultiMap (const UnorderedMultiMap& o);
    UnorderedMultiMap (UnorderedMultiMap&& o) noexcept;
    UnorderedMultiMap& operator= (const UnorderedMultiMap&);
    UnorderedMultiMap& operator= (UnorderedMultiMap&&) noexcept;
    ~UnorderedMultiMap ();

    template <typename V, typename W>
    bool insert (V&&, W&&);

    Pair<T, U>* find (const T&);

    bool erase (const T&);
};


template <typename T, typename U>
UnorderedMultiMap<T, U>::UnorderedMultiMap (const std::initializer_list<Pair<T, U>>& l) : HashArrayMulti<Pair<T, U>>::HashArrayMulti (l) {

}


template <typename T, typename U>
UnorderedMultiMap<T, U>::UnorderedMultiMap (const UnorderedMultiMap& o) : HashArrayMulti<Pair<T, U>>::HashArrayMulti (o) {

}


template <typename T, typename U>
UnorderedMultiMap<T, U>::UnorderedMultiMap (UnorderedMultiMap&& o) noexcept : HashArrayMulti<Pair<T, U>>::HashArrayMulti (std::move (o)) {

}


template <typename T, typename U>
UnorderedMultiMap<T, U>& UnorderedMultiMap<T, U>::operator= (const UnorderedMultiMap& o) {

    if (this == &o)
        return *this;

    HashArrayMulti<Pair<T, U>>::operator= (o);

    return *this;
}


template <typename T, typename U>
UnorderedMultiMap<T, U>& UnorderedMultiMap<T, U>::operator= (UnorderedMultiMap&& o) noexcept {

    if (this == &o)
        return *this;

    HashArrayMulti<Pair<T, U>>::operator= (std::move (o));

    return *this;
}


template <typename T, typename U>
UnorderedMultiMap<T, U>::~UnorderedMultiMap () {

}


template <typename T, typename U>
template <typename V, typename W>
bool UnorderedMultiMap<T, U>::insert (V&& a, W&& b) {

    Pair<T, U> pair{std::forward<V> (a), std::forward<W> (b)};
    return HashArrayMulti<Pair<T, U>>::insert (std::move (pair));
}


template <typename T, typename U>
Pair<T, U>* UnorderedMultiMap<T, U>::find (const T& key) {

    return HashArrayMulti<Pair<T, U>>::find (Pair<T, U> (key, U ()));
}


template <typename T, typename U>
bool UnorderedMultiMap<T, U>::erase (const T& key) {

    Pair<T, U> pair (key, U ());
    return HashArrayMulti<Pair<T, U>>::erase (pair);
}


#endif