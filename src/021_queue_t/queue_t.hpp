#ifndef _QUEUET_
#define _QUEUET_


template<typename T>
class QueueT {

public:

    QueueT () = default;
    QueueT (const QueueT&) = delete;
    QueueT operator= (const QueueT&) = delete;
    ~QueueT ();

    void push (const T&);

    void pop ();

    T& front ();

    bool empty () const;

    size_t size () const;

private:

    struct Element {

        explicit Element(const T& data) : data(data) {};

        T data{};
        Element* r{};
    };

    int msize{};
    Element* f{};
    Element* pback{};
};


template<typename T>
void QueueT<T>::push (const T& data) {
    
    Element* e = new(std::nothrow) Element(data);

    if (msize > 0)
        pback->r = e;
    else
        f = e;

    pback = e;
    msize++;
}


template<typename T>
void QueueT<T>::pop () {
    
    if (msize > 0) {

        Element* e = f;
        f = f->r;
        delete e;
        msize--;
    }
}


template<typename T>
T& QueueT<T>::front () {
    
    return f->data;
}


template<typename T>
bool QueueT<T>::empty () const {
    
    return f == nullptr;
}


template<typename T>
size_t QueueT<T>::size () const { 
    
    return msize;
}


template<typename T>
QueueT<T>::~QueueT () {
    
    while (f != nullptr) {

        Element* e = f;
        f = f->r;
        delete e;
    }
}

#endif
