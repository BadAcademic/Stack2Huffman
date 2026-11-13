#ifndef _STACKL_
#define _STACKL_

#include "gexception.h"
#include <initializer_list>


template <typename T>
class Stack {

public:

    Stack () = default;
    Stack (std::initializer_list<T>);
    Stack (const Stack&);
    Stack (Stack&&) noexcept;
    Stack& operator= (const Stack&);
    Stack& operator= (Stack&&) noexcept;
    ~Stack ();

    template <typename U>
    void push (U&&);

    void pop ();

    T& top ();

    bool empty () const;

    size_t size () const;

private:

    static const uint8_t bsize{128};

    void copy (const Stack&);

    void clear ();

    struct Element {

        char data[bsize * sizeof (T)];
        Element* n{};
    };

    size_t msize{};
    Element* ptop{};
    uint8_t ntop{};

    Element* res{};
};


template <typename T>
Stack<T>::Stack (std::initializer_list<T> l) {

    for (auto& o : l)
        push(o);
}


template <typename T>
void Stack<T>::copy (const Stack& o) {
    
    if (o.ptop != nullptr) {

        Element* dst{};
        Element* src{o.ptop};
        Element* ldst{};
        bool chunk{true};
        do {
            dst = new(std::nothrow) Element;
            if (dst == nullptr)
                throw gexception (gexception::MemAlloc);
            
            int be{};
            if (chunk) {
                be = o.ntop;
                ptop = dst;
            }
            else
                be = 0;

            for (int i{be}; i < bsize; i++)
                new (dst->data + i * sizeof (T)) T (reinterpret_cast<T*>(src->data)[i]);

            if (ldst != nullptr)
                ldst->n = dst;
            
            ldst = dst;        
            chunk = false;

            src = src->n;
        } while (src != nullptr);

        msize = o.msize;
        ntop = o.ntop;
    }
}


template <typename T>
void Stack<T>::clear () {

    while (ptop != nullptr) {
        
        for (int i{ntop}; i < bsize; i++) {
            reinterpret_cast<T*>(ptop->data)[i].~T ();
            msize--;
        }
        ntop = 0;

        Element* e = ptop;
        ptop = ptop->n;
        delete e;
    }

    while (res != nullptr) {
        
        Element* e = res;
        res = res->n;
        delete e;
    }
    msize = 0;
    ntop = 0;
}


template <typename T>
Stack<T>::Stack (const Stack& o) {

    copy(o);
}


template <typename T>
Stack<T>::Stack (Stack&& o) noexcept {

    ptop = o.ptop;
    o.ptop = nullptr;

    msize = o.msize;
    o.msize = 0;
    ntop = o.ntop;
    o.ntop = 0;

    res = nullptr;
    while (o.res != nullptr) {
        
        Element* e = o.res;
        o.res = o.res->n;
        delete e;
    }
}


template <typename T>
Stack<T>& Stack<T>::operator= (const Stack& o) {

    if (this == &o)
        return *this;

    clear();
    copy(o);

    return *this;
}


template <typename T>
Stack<T>& Stack<T>::operator= (Stack&& o) noexcept {

    if (this == &o)
        return *this;

    clear();

    ptop = o.ptop;
    o.ptop = nullptr;

    msize = o.msize;
    o.msize = 0;
    ntop = o.ntop;
    o.ntop = 0;

    res = nullptr;
    while (o.res != nullptr) {
        
        Element* e = o.res;
        o.res = o.res->n;
        delete e;
    }

    return *this;
}


template <typename T>
template <typename U>
void Stack<T>::push (U&& data) {
    
    if (ntop == 0) {

        Element* e{};
        if (res == nullptr) {

            e = new(std::nothrow) Element;
            if (e == nullptr)
                throw gexception(gexception::MemAlloc);
        }
        else {

            e = res;
            res = res->n;
        }

        ntop = bsize - 1;
        if (msize == 0)
            e->n = nullptr;
        else
            e->n = ptop;

        ptop = e;
    }
    else
        ntop--;

    new (ptop->data + ntop * sizeof (T)) T (std::forward<U> (data));
    msize++;
}


template <typename T>
void Stack<T>::pop () {
    
    if (msize > 0) {

        reinterpret_cast<T*>(ptop->data)[ntop].~T ();

        msize--;
        if (ntop == bsize - 1) {

            if (res == nullptr) {
                res = ptop;
                ptop = ptop->n;
                res->n = nullptr;
            }
            else {
                Element* tmp = res;
                res = ptop;
                ptop = ptop->n;
                res->n = tmp;
            }
            ntop = 0;
        }
        else
            ntop++;
    }
}


template <typename T>
T& Stack<T>::top () {
    
    return reinterpret_cast<T*>(ptop->data)[ntop];
}


template <typename T>
bool Stack<T>::empty () const {
    
    return msize == 0;
}


template <typename T>
size_t Stack<T>::size () const {
    
    return msize;
}


template <typename T>
Stack<T>::~Stack () {
    
    clear();
}

#endif
