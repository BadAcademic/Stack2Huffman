#ifndef _STACKS_
#define _STACKS_

#include <string>


class StackS {

public:

    StackS () = default;
    StackS (const StackS&) = delete;
    StackS operator= (const StackS&) = delete;
    ~StackS ();

    void push (const std::string&);

    void pop ();

    std::string& top ();

    bool empty () const;

    size_t size () const;

private:

    struct Element {

        explicit Element(const std::string& data) : data(data) {};

        std::string data{};
        Element* n{};
    };

    size_t msize{};
    Element* ptop{};
};

#endif
