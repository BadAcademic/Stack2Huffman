#ifndef _QUEUES_
#define _QUEUES_

#include <string>


class QueueS {

public:

    QueueS () = default;
    QueueS (const QueueS&) = delete;
    QueueS operator= (const QueueS&) = delete;
    ~QueueS ();

    void push (const std::string&);

    void pop ();

    std::string& front();

    bool empty () const;

    size_t size () const;

private:

    struct Element {

        explicit Element (const std::string& data) : data(data) {};

        std::string data{};
        Element* r{};
    };

    int msize{};
    Element* pfront{};
    Element* pback{};
};

#endif
