#ifndef _STACKSP_
#define _STACKSP_

#include <memory>


template <class T>
class StackSP {

public:

    StackSP () = default;
    StackSP (const StackSP&) = delete;
    StackSP operator= (const StackSP&) = delete;

    void push (const T&);

    void pop ();

    T& top ();

    bool empty () const;

    size_t size () const;

private:

    struct Element {

        explicit Element(const T& data) : data(data) {};

        T data{};
        std::shared_ptr<Element> n;
    };

    size_t msize{};
    std::shared_ptr<Element> ptop;
};


template <typename T>
void StackSP<T>::push (const T& data) {
    
    std::shared_ptr<Element> e = std::make_shared<Element>(data);

    if (msize > 0)
        e->n = ptop;

    ptop = e;
    msize++;
}


template <typename T>
void StackSP<T>::pop () {
    
    if (msize > 0) {

        ptop = ptop->n;
        msize--;
    }
}


template <typename T>
T& StackSP<T>::top () {
    
    return ptop->data;
}


template <typename T>
bool StackSP<T>::empty () const {
    
    return ptop == nullptr;
}


template <typename T>
size_t StackSP<T>::size () const {
    
    return msize;
}

#endif
