#ifndef _UNORDEREDMAPL_
#define _UNORDEREDMAPL_

#include <initializer_list>

#include "pair.hpp"
#include "hash_array_v2.hpp"


template <typename T, typename U>
class UnorderedMap : public HashArrayV2<Pair<T, U>> {

public:

    UnorderedMap () = default;
    UnorderedMap (const std::initializer_list<Pair<T, U>>&);
    UnorderedMap (const UnorderedMap& o);
    UnorderedMap (UnorderedMap&& o) noexcept;
    UnorderedMap& operator= (const UnorderedMap&);
    UnorderedMap& operator= (UnorderedMap&&) noexcept;
    ~UnorderedMap ();

    template <typename V, typename W>
    bool insert (V&&, W&&);

    Pair<T, U>* find (const T&);

    bool erase (const T&);
};


template <typename T, typename U>
UnorderedMap<T, U>::UnorderedMap (const std::initializer_list<Pair<T, U>>& l) : HashArrayV2<Pair<T, U>>::HashArrayV2 (l) {

}


template <typename T, typename U>
UnorderedMap<T, U>::UnorderedMap (const UnorderedMap& o) : HashArrayV2<Pair<T, U>>::HashArrayV2 (o) {

}


template <typename T, typename U>
UnorderedMap<T, U>::UnorderedMap (UnorderedMap&& o) noexcept : HashArrayV2<Pair<T, U>>::HashArrayV2 (std::move (o)) {

}


template <typename T, typename U>
UnorderedMap<T, U>& UnorderedMap<T, U>::operator= (const UnorderedMap& o) {

    if (this == &o)
        return *this;

    HashArrayV2<Pair<T, U>>::operator= (o);

    return *this;
}


template <typename T, typename U>
UnorderedMap<T, U>& UnorderedMap<T, U>::operator= (UnorderedMap&& o) noexcept {

    if (this == &o)
        return *this;

    HashArrayV2<Pair<T, U>>::operator= (std::move (o));

    return *this;
}


template <typename T, typename U>
UnorderedMap<T, U>::~UnorderedMap () {

}


template <typename T, typename U>
template <typename V, typename W>
bool UnorderedMap<T, U>::insert (V&& a, W&& b) {

    Pair<T, U> pair{std::forward<V> (a), std::forward<W> (b)};
    return HashArrayV2<Pair<T, U>>::insert (std::move (pair));
}


template <typename T, typename U>
Pair<T, U>* UnorderedMap<T, U>::find (const T& key) {

    return HashArrayV2<Pair<T, U>>::find (Pair<T, U> (key, U ()));
}


template <typename T, typename U>
bool UnorderedMap<T, U>::erase (const T& key) {

    Pair<T, U> pair (key, U ());
    return HashArrayV2<Pair<T, U>>::erase (pair);
}


#endif