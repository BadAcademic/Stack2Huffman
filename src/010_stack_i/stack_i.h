#ifndef _STACKI_
#define _STACKI_

class StackI {

public:

    StackI () = default;
    StackI (const StackI&) = delete;
    StackI operator= (const StackI&) = delete;
    ~StackI ();

    void push (const int&);

    void pop ();

    int& top ();

    bool empty () const;

    size_t size () const;

private:

    struct Element {
        
        explicit Element (const int& data) : data (data) {};

        int data{};
        Element* n{};
    };

    size_t msize{};
    Element* ptop{};
};

#endif
