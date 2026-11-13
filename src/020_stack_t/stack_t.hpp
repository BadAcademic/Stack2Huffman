#ifndef _STACKT_
#define _STACKT_


template <typename T> 
class StackT {

public:

    StackT () = default;
    StackT (const StackT&) = delete;
    StackT operator= (const StackT&) = delete;
    ~StackT ();

    void push (const T&);

    void pop ();

    T& top ();

    bool empty () const;

    size_t size () const;

private:

    struct Element {

        explicit Element(const T& data) : data(data) {};

        T data{};
        Element* n{};
    };

    size_t msize{};
    Element* ptop{};
};


template <typename T>
void StackT<T>::push (const T& data) {
    
    Element* e = new(std::nothrow) Element(data);

    if (msize > 0)
        e->n = ptop;

    ptop = e;
    msize++;
}


template <typename T1>
void StackT<T1>::pop () {
    
    if (msize > 0) {
        
        Element* e = ptop;
        ptop = ptop->n;
        delete e;
        msize--;
    }
}


template <typename T>
T& StackT<T>::top ()
{
    return ptop->data;
}


template <typename T>
bool StackT<T>::empty () const {
    
    return ptop == nullptr;
}


template <typename T>
size_t StackT<T>::size () const {

    return msize;
}


template <typename T>
StackT<T>::~StackT () {
    
    while (ptop != nullptr) {

        Element* e = ptop;
        ptop = ptop->n;
        delete e;
    }
}

#endif
