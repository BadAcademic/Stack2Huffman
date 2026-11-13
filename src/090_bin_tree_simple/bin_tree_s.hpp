#ifndef _BINTREES_
#define _BINTREES_

#include <iostream>
#include <initializer_list>

#include "stack.hpp"
#include "gexception.h"


template <typename T>
class BinTreeS {

public:

    BinTreeS () = default;
    BinTreeS (const std::initializer_list<T>&);
    BinTreeS (const BinTreeS&) = delete;
    BinTreeS& operator= (const BinTreeS&) = delete;
    ~BinTreeS ();

    template <typename U>
    bool insert (U&&);

    T* find(const T&);

    void dprint ();

    void pprint ();

    void clear ();

private:

    struct Node {
        
        template <typename U>
        Node (U&& data) : data (std::forward<U>(data)) {}

        Node* l{};
        Node* r{};
        T data{};
    };

    Node* root{};
};


template <typename T>
BinTreeS<T>::BinTreeS (const std::initializer_list<T>& l) {

    for (auto& d : l)
        insert (d);
}


template <typename T>
template <typename U>
bool BinTreeS<T>::insert (U&& data) {

    Node* c{root};
    if (c != nullptr) {
        while (true) {

            if (data < c->data) {

                if (c->l == nullptr)
                    break;
                else
                    c = c->l;
            }
            else if (c->data < data) {

                if (c->r == nullptr)
                    break;
                else
                    c = c->r;
            }
            else
                return false;
        }
    }

    Node* n = new (std::nothrow) Node (std::forward<U> (data));
    if (n == nullptr)
        throw gexception (gexception::MemAlloc);

    if (c == nullptr)
        root = n;
    else {
        if (n->data < c->data)
            c->l = n;
        else
            c->r = n;
    }

    return true;
}


template <typename T>
T* BinTreeS<T>::find (const T& data) {

    Node* c{root};

    while (c != nullptr) {

        if (data < c->data)
            c = c->l;
        else if (c->data < data)
            c = c->r;
        else
            return &c->data;
    }
    return nullptr;
}


template <typename T>
void BinTreeS<T>::dprint () {

    Stack<Node*> nodes;
    nodes.push (root);

    while (!nodes.empty ()) {

        Node* c{nodes.top ()};
        std::cout << c->data << "\n";
        nodes.pop ();

        if (c->l != nullptr)
            nodes.push (c->l);
        if (c->r != nullptr)
            nodes.push (c->r);
    }
}


template <typename T>
void BinTreeS<T>::pprint () {

    Stack<Node*> nodes;
    if (root != nullptr)
        nodes.push (root);
    else
        return;

    std::cout << "digraph tree {\n";

    while (!nodes.empty ()) {

        Node* c{nodes.top ()};
        nodes.pop ();

        if (c->l != nullptr) {

            nodes.push (c->l);
            std::cout << std::format("\"{}\" -> \"{}\" [label = L];\n", c->data, c->l->data);
        }
        if (c->r != nullptr) {

            nodes.push (c->r);
            std::cout << std::format("\"{}\" -> \"{}\" [label = R];\n", c->data, c->r->data);
        }
    }
    std::cout << "}";
}


template <typename T>
void BinTreeS<T>::clear () {
    
    Stack<Node*> nodes;
    if (root != nullptr)
        nodes.push (root);
    else
        return;

    while (!nodes.empty ()) {

        Node* c{nodes.top ()};
        nodes.pop ();
        if (c->l != nullptr)
            nodes.push (c->l);
        if (c->r != nullptr)
            nodes.push (c->r);

        delete c;
    }
    root = nullptr;
}


template <typename T>
BinTreeS<T>::~BinTreeS () {
    
    clear ();
}

#endif