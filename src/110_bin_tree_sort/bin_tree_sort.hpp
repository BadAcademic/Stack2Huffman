#ifndef _BINTREESORT_
#define _BINTREESORT_

#include <iostream>
#include <initializer_list>

#include "stack.hpp"
#include "gexception.h"


template <typename T>
class BinTreeSort {
public:

    BinTreeSort () = default;
    BinTreeSort (const std::initializer_list<T>&);
    BinTreeSort (const BinTreeSort&);
    BinTreeSort (BinTreeSort&&) noexcept;
    BinTreeSort& operator= (const BinTreeSort&);
    BinTreeSort& operator= (BinTreeSort&&) noexcept;
    ~BinTreeSort ();

    template <typename U>
    bool insert (U&&);

    template <class... U>
    bool emplace (U&&...);

    T* find (const T&);

    bool erase (const T&);

    void dprint ();

    void pprint ();

    void clear ();

    size_t size ();

    bool empty ();

    class iterator;

    iterator begin ();
    iterator end ();

private:

    struct Node {

        template <class... U>
        Node (U&&... args) : data (std::forward<U> (args)...) {}

        template <typename U>
        Node (U&& data) : data (std::forward<U>(data)) {}
        
        Node* p{};
        Node* l{};
        Node* r{};
        T data{};
    };

    void copy (const BinTreeSort<T>&);

    Node* root{};
    size_t msize{};
};


template <typename T>
BinTreeSort<T>::BinTreeSort (const std::initializer_list<T>& ilist) {

    for (auto& w : ilist)
        insert (w);
}


template <typename T>
BinTreeSort<T>::BinTreeSort (const BinTreeSort& o) {

    copy(o);
}


template <typename T>
BinTreeSort<T>::BinTreeSort (BinTreeSort&& o) noexcept {

    root = o.root;
    o.root = nullptr;

    msize = o.msize;
    o.msize = 0;
}


template <typename T>
BinTreeSort<T>& BinTreeSort<T>::operator= (const BinTreeSort& o) {

    if (this == &o)
        return *this;

    clear();
    copy(o);

    return *this;
}


template <typename T>
BinTreeSort<T>& BinTreeSort<T>::operator= (BinTreeSort&& o) noexcept {

    if (this == &o)
        return *this;

    clear();

    root = o.root;
    o.root = nullptr;

    msize = o.msize;
    o.msize = 0;
        
    return *this;
}


template <typename T>
BinTreeSort<T>::~BinTreeSort () {

    clear();
}


template <typename T>
template <typename U>
bool BinTreeSort<T>::insert (U&& data) {

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
            } else
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
        n->p = c;
    }
    msize++;

    return true;
}


template <typename T>
template <class... U>
bool BinTreeSort<T>::emplace (U&&... args) {

    Node* n = new (std::nothrow) Node (std::forward<U> (args)...);
    if (n == nullptr)
        throw gexception (gexception::MemAlloc);
    T& data{n->data};

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
            else {
                delete n;
                return false;
            }
        }
    }

    if (c == nullptr)
        root = n;
    else {
        if (n->data < c->data)
            c->l = n;
        else
            c->r = n;
        n->p = c;
    }
    msize++;

    return true;
}


template <typename T>
T* BinTreeSort<T>::find (const T& data) {

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
bool BinTreeSort<T>::erase (const T& data) {

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
               break;            
        }
    }

    if (c == nullptr)
        return false;
    else
        msize--;

    Node*& p{c->p};
    Node*& l{c->l};
    Node*& r{c->r};

    // cs on the left & on hte right
    if (l != nullptr && r != nullptr) {

        // find minimum
        Node* m{r};
        while (m->l != nullptr)
            m = m->l;

        if (m->r == nullptr) {
            if (m->data < m->p->data)
                m->p->l = nullptr;
            else
                m->p->r = nullptr;
        } else {
            if (m->data < m->p->data)
                m->p->l = m->r;
            else
                m->p->r = m->r;
            m->r->p = m->p;
        }

        c->data = std::move (m->data);

        delete m;
        return true;
    }
    // c on the left 
    if (l != nullptr && r == nullptr) {

        if (p != nullptr) {
            if (data < p->data)
                p->l = c->l;
            else
                p->r = c->l;
            c->l->p = p;
        }
        else {
            root = c->l;
            root->p = nullptr;
        }

        delete c;
        return true;
    }
    // c on the right
    if (l == nullptr && r != nullptr) {

        if (p != nullptr) {
            if (data < p->data)
                p->l = c->r;
            else
                p->r = c->r;
            c->r->p = p;
        }
        else {
            root = c->r;
            root->p = nullptr;
        }

        delete c;
        return true;
    }
    // leaf & only root
    if (l == nullptr && r == nullptr) {

        if (p != nullptr) {

            if (data < p->data)
                p->l = nullptr;
            else
                p->r = nullptr;
        }
        else {
            root = nullptr;
        }

        delete c;
        return true;
    }
}


template <typename T>
void BinTreeSort<T>::dprint () {
    
    for (auto& w : *this)
        std::cout << w << "\n";
}


template <typename T>
void BinTreeSort<T>::pprint () {
    
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
void BinTreeSort<T>::clear () {

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
    msize = 0;
}


template <typename T>
size_t BinTreeSort<T>::size () {

    return msize;
}


template <typename T>
bool BinTreeSort<T>::empty () {

    return msize == 0;
}


template <typename T>
void BinTreeSort<T>::copy (const BinTreeSort<T>& o) {

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
    msize = o.msize;
}


template <typename T>
class BinTreeSort<T>::iterator {

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

    void gotoMinimal (Node*&);

    friend iterator BinTreeSort<T>::begin (void);
    friend iterator BinTreeSort<T>::end (void);

    Stack<Node*>* nodes;
};


template <typename T>
BinTreeSort<T>::iterator::iterator () {
    
    nodes = new Stack<Node*>;
}


template <typename T>
BinTreeSort<T>::iterator::iterator (const iterator& iterator) {
    
    nodes = new Stack<Node*>;
    *nodes = *(iterator.nodes);
}


template <typename T>
typename BinTreeSort<T>::iterator& BinTreeSort<T>::iterator::operator= (const iterator& iterator) {
    
    if (this == &iterator)
        return (*this);

    delete nodes;

    nodes = new Stack<Node*>;
    *nodes = *(iterator.nodes);

    return (*this);
}


template <typename T>
typename BinTreeSort<T>::iterator& BinTreeSort<T>::iterator::operator++ () {
    
    if (!nodes->empty ()) {
        
        Node* node = nodes->top ();
        nodes->pop ();

        if (node->r != nullptr)
            gotoMinimal (node->r);
    }

    return (*this);
}


template <typename T>
bool BinTreeSort<T>::iterator::operator!= (const iterator& iterator) const {
    
    if (nodes->empty () || iterator.nodes->empty ()) {
        if (nodes->empty () && iterator.nodes->empty ())
            return false;
        else
            return true;
    }

    if (&(nodes->top ()) != &(iterator.nodes->top ()))
        return true;
    else
        return false;
}


template <typename T>
T& BinTreeSort<T>::iterator::operator* () {
    
    return nodes->top ()->data;
}


template <typename T>
T* BinTreeSort<T>::iterator::operator-> () {
    
    return &(nodes->top ()->data);
}


template <typename T>
typename BinTreeSort<T>::iterator BinTreeSort<T>::begin (void) {
    
    iterator it{};
    if (root != 0)
        it.gotoMinimal (root);

    return it;
}


template <typename T>
typename BinTreeSort<T>::iterator BinTreeSort<T>::end (void) {
    
    iterator it{};
    return it;
}


template <typename T>
BinTreeSort<T>::iterator::~iterator () {
    
    delete nodes;
}


template <typename T>
void BinTreeSort<T>::iterator::gotoMinimal (Node*& node) {

    if (node != nullptr)
        nodes->push (node);
    else
        return;

    while (nodes->top ()->l != nullptr)
        nodes->push (nodes->top ()->l);
}

#endif
