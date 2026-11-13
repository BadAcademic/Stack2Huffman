#ifndef _BINTREES_
#define _BINTREES_

#include <iostream>
#include <initializer_list>

#include "stack.hpp"
#include "gexception.h"


template <typename T>
class BinTree {

public:

    BinTree () = default;
    BinTree (const std::initializer_list<T>&);
    BinTree (const BinTree&);
    BinTree (BinTree&&) noexcept;
    BinTree& operator= (const BinTree&);
    BinTree& operator= (BinTree&&) noexcept;
    ~BinTree ();

    template <typename U>
    bool insert (U&&);

    T* find (const T&);

    void dprint ();

    void pprint ();

    void clear ();

    class iterator;

    iterator begin ();
    iterator end ();

private:

    void copy (const BinTree<T>&);

    struct Node {

        template <typename U>
        Node (U&& data) : data(std::forward<U>(data)) {}

        Node* l{};
        Node* r{};
        T data{};
    };

    Node* root{};
};


template <typename T>
BinTree<T>::BinTree (const std::initializer_list<T>& l) {

    for (auto& d : l)
        insert(d);
}


template <typename T>
void BinTree<T>::copy (const BinTree<T>& o) {

    if (o.root == nullptr)
        return;

    Stack<std::pair<Node*, Node**>> nodes;
    nodes.push (std::make_pair (o.root, nullptr));

    while (!nodes.empty ()) {

        Node* sn{nodes.top ().first};

        Node* dn = new (std::nothrow) Node (sn->data);
        if (dn == nullptr)
            throw gexception (gexception::MemAlloc);

        Node** c{nodes.top ().second};
        if (c != nullptr)
            *c = dn;        
        else
            root = dn;
        
        nodes.pop ();

        if (sn->l != nullptr)
            nodes.push (std::make_pair (sn->l, &dn->l));
        if (sn->r != nullptr)
            nodes.push (std::make_pair (sn->r, &dn->r));
    }
}


template <typename T>
BinTree<T>::BinTree (const BinTree& o) {

    copy(o);
}


template <typename T>
BinTree<T>::BinTree (BinTree&& o) noexcept {

    root = o.root;
    o.root = nullptr;
}


template <typename T>
BinTree<T>& BinTree<T>::operator= (const BinTree& o) {

    if (this == &o)
        return *this;

    clear();
    copy(o);

    return *this;
}


template <typename T>
BinTree<T>& BinTree<T>::operator= (BinTree&& o) noexcept {

    if (this == &o)
        return *this;

    clear();

    root = o.root;
    o.root = nullptr;

    return *this;
}


template <typename T>
BinTree<T>::~BinTree () {

    clear();
}


template <typename T>
template <typename U>
bool BinTree<T>::insert (U&& data) {

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
T* BinTree<T>::find (const T& data) {

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
void BinTree<T>::dprint () {

    Stack<Node*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {

        Node* c{nodes.top ()};
        std::cout << c->data << "\n";
        nodes.pop();

        if (c->l != nullptr)
            nodes.push(c->l);
        if (c->r != nullptr)
            nodes.push(c->r);
    }
}


template <typename T>
void BinTree<T>::pprint () {

    Stack<Node*> nodes;
    if (root != nullptr)
        nodes.push(root);
    else
        return;

    std::cout << "digraph tree {\n";

    while (!nodes.empty()) {

        Node* c{nodes.top ()};
        nodes.pop();

        if (c->l != nullptr) {

            nodes.push(c->l);
            std::cout << std::format("\"{}\" -> \"{}\" [label = L];\n", c->data, c->l->data);
        }
        if (c->r != nullptr) {

            nodes.push(c->r);
            std::cout << std::format("\"{}\" -> \"{}\" [label = R];\n", c->data, c->r->data);
        }
    }
    std::cout << "}";
}


template <typename T>
void BinTree<T>::clear () {

    Stack<Node*> nodes;
    if (root != nullptr)
        nodes.push(root);
    else
        return;

    while (!nodes.empty()) {

        Node* c{nodes.top ()};
        nodes.pop();
        if (c->l != nullptr)
            nodes.push(c->l);
        if (c->r != nullptr)
            nodes.push(c->r);

        delete c;
    }
    root = nullptr;
}


template <typename T>
class BinTree<T>::iterator {

public:

    iterator ();
    iterator (const iterator&);
    iterator& operator= (const iterator&);
    ~iterator ();

    iterator& operator++ ();

    bool operator!= (const iterator&) const;

    T& operator* ();

    T* operator-> ();

private:

    Stack<Node*>* pNodes;

    friend iterator BinTree<T>::begin ();
    friend iterator BinTree<T>::end ();
};


template <typename T>
BinTree<T>::iterator::iterator (void) {
    
    pNodes = new Stack<Node*>;
}


template <typename T>
BinTree<T>::iterator::iterator (const iterator& iterator) {
    
    pNodes = new Stack<Node*>;
    *pNodes = *(iterator.pNodes);
}


template <typename T>
typename BinTree<T>::iterator& BinTree<T>::iterator::operator= (const iterator& iterator) {

    if (this == &iterator)
        return (*this);

    delete pNodes;

    pNodes = new Stack<Node*>;
    *pNodes = *(iterator.pNodes);

    return (*this);
}


template <typename T>
typename BinTree<T>::iterator& BinTree<T>::iterator::operator++ () {
    
    if (!pNodes->empty ()) {
        
        Node* node = pNodes->top ();
        pNodes->pop ();

        if (node->l != nullptr)
            pNodes->push (node->l);
        if (node->r != nullptr)
            pNodes->push (node->r);
    }

    return (*this);
}


template <typename T>
bool BinTree<T>::iterator::operator!= (const iterator& iterator) const {
    
    if (pNodes->empty () || iterator.pNodes->empty ()) {
        if (pNodes->empty () && iterator.pNodes->empty ())
            return false;
        else
            return true;
    }

    if (&(pNodes->top ()) != &(iterator.pNodes->top ()))
        return true;
    else
        return false;
}


template <typename T>
T& BinTree<T>::iterator::operator* (void) {
    
    return pNodes->top ()->data;
}


template <typename T>
T* BinTree<T>::iterator::operator-> () {
    
    return &(pNodes->top ()->data);
}


template <typename T>
typename BinTree<T>::iterator BinTree<T>::begin (void) {
    
    iterator it{};
    if (root != nullptr)
        it.pNodes->push (root);

    return it;
}


template <typename T>
typename BinTree<T>::iterator BinTree<T>::end (void) {

    iterator it{};
    return it;
}


template <typename T>
BinTree<T>::iterator::~iterator (void) {
    
    delete pNodes;
}

#endif