#include "stack_s.h"


void StackS::push (const std::string& data) {
    
    Element* e = new Element(data);

    if (msize > 0)
        e->n = ptop;

    ptop = e;
    msize++;
}


void StackS::pop () {
    
    if (msize > 0) {

        Element* e = ptop;
        ptop = ptop->n;
        delete e;
        msize--;
    }
}


std::string& StackS::top() {
    
    return ptop->data;
}


bool StackS::empty() const {
    
    return ptop == nullptr;
}


size_t StackS::size() const {
    
    return msize;
}


StackS::~StackS() {
    
    while (ptop != nullptr) {

        Element* e = ptop;
        ptop = ptop->n;
        delete e;
    }
}
