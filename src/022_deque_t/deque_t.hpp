#ifndef _DEQUET_
#define _DEQUET_

#include "gexception.h"


template<typename T> 
class DequeT {

public:

    DequeT () = default;
    DequeT (const DequeT&) = delete;
    DequeT operator= (const DequeT&) = delete;
    ~DequeT ();

    void push_front (const T&);
    void push_back (const T&);

    void pop_front ();
    void pop_back ();

    T& front ();
    T& back ();

    bool empty () const;

    size_t size () const;

private:

    struct Element {

        explicit Element(const T& data) : data(data) {};

        T data{};
        Element* r{};
        Element* l{};
    };

    int msize{};
    Element* pfront{};
    Element* pback{};
};


template<typename T>
void DequeT<T>::push_front (const T& data) {
    
    Element* e = new(std::nothrow) Element(data);
    if (e == nullptr)
        throw gexception(gexception::MemAlloc);

    if (msize > 0) {
        pfront->l = e;
        e->r = pfront;
    }
    else
        pback = e;

    pfront = e;
    msize++;
}


template<typename T>
void DequeT<T>::push_back (const T& data) {
    
    Element* e = new(std::nothrow) Element(data);
    if (e == nullptr)
        throw gexception(gexception::MemAlloc);

    if (msize > 0) {
        pback->r = e;
        e->l = pback;
    }
    else {
        pfront = e;
    }

    pback = e;
    msize++;
}


template<typename T>
void DequeT<T>::pop_front () {
    
    if (msize > 0) {

        msize--;
        Element* e{pfront};
        pfront = pfront->r;
        delete e;

        if (msize == 0)
            pback = nullptr;
        else
            pfront->l = nullptr;
    }
}


template<typename T>
void DequeT<T>::pop_back () {
    
    if (msize > 0) {

        msize--;
        Element* e{pback};
        pback = pback->l;
        delete e;

        if (msize == 0)
            pfront = nullptr;
        else
            pback->r = nullptr;
    }
}


template<typename T>
T& DequeT<T>::front () {

    return pfront->data;
}


template<typename T>
T& DequeT<T>::back () {
    
    return pback->data;
}


template<typename T>
bool DequeT<T>::empty () const {
    
    return pfront == nullptr;
}


template<typename T>
size_t DequeT<T>::size () const {
    
    return (msize);
}


template<typename T>
DequeT<T>::~DequeT () {
    
    while (pfront != nullptr) {

        Element* e = pfront;
        pfront = pfront->r;
        delete e;
    }
}

#endif
