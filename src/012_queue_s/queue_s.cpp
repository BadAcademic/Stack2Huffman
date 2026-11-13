#include "queue_s.h"


void QueueS::push (const std::string& data) {
    
    Element* e = new Element(data);

    if (msize > 0)
        pback->r = e;
    else
        pfront = e;

    pback = e;
    msize++;
}


void QueueS::pop () {
    
    if (msize > 0) {

        Element* e = pfront;
        pfront = pfront->r;
        delete e;
        msize--;
    }
}


std::string& QueueS::front () {
    
    return pfront->data;
}


bool QueueS::empty () const {
    
    return pfront == nullptr;
}


size_t QueueS::size () const {
    
    return msize;
}


QueueS::~QueueS () {
    
    Element* e;
    while (pfront != nullptr) {

        e = pfront;
        pfront = pfront->r;
        delete e;
    }
}
