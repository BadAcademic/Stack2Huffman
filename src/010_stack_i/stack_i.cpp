#include "stack_i.h"


void StackI::push (const int& data) {
    
    Element* e = new Element(data);

    if (msize > 0)
        e->n = ptop;

    ptop = e;
    msize++;
}


void StackI::pop () {

    if (msize > 0) {

        Element* e = ptop;
        ptop = ptop->n;
		delete e;
        msize--;
    }
}


int& StackI::top () {
    
    return ptop->data;
}


bool StackI::empty () const {
    
    return ptop == nullptr;
}


size_t StackI::size () const {

    return msize;
}


StackI::~StackI () {
    
    while (ptop != nullptr) {

        Element* e = ptop;
        ptop = ptop->n;
        delete e;
    }
}
