#ifndef _REDBLACKTREE_
#define _REDBLACKTREE_

#include <format>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <initializer_list>

#include "stack.hpp"
#include "gexception.h"


template <typename T>
class RedBlackTree {
public:

    RedBlackTree () = default;
    RedBlackTree (const std::initializer_list<T>&);
    RedBlackTree (const RedBlackTree&);
    RedBlackTree (RedBlackTree&&) noexcept;
    RedBlackTree& operator= (const RedBlackTree&);
    RedBlackTree& operator= (RedBlackTree&&) noexcept;
    ~RedBlackTree ();

    template <typename U>
    bool insert (U&&);

    template <class... U>
    bool emplace (U&&...);

    T* find (const T&);

    bool erase (const T&);

    void dprint ();

    void pprint (bool color = false, bool view = false);

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
        Node (U&& data) : data (std::forward<U> (data)) {}

        bool red{true};
        Node* p{};
        Node* l{};
        Node* r{};
        T data{};
    };

    void copy (const RedBlackTree<T>&);

    void balance (Node*&);
    void balance (Node*&, bool);
    void rotate_left (Node*&, Node*&, Node*&);
    void rotate_right (Node*&, Node*&, Node*&);
    void rotate_left_s (Node*&, Node*&, Node*&);
    void rotate_right_s (Node*&, Node*&, Node*&);

    Node* root{};
    size_t msize{};

    uint16_t fnum{};
};


template <typename T>
RedBlackTree<T>::RedBlackTree (const std::initializer_list<T>& ilist) {

    for (auto& w : ilist)
        insert (w);
}


template <typename T>
RedBlackTree<T>::RedBlackTree (const RedBlackTree& o) {

    copy (o);
}


template <typename T>
RedBlackTree<T>::RedBlackTree (RedBlackTree&& o) noexcept {

    root = o.root;
    o.root = nullptr;

    msize = o.msize;
    o.msize = 0;
}


template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator= (const RedBlackTree& o) {

    if (this == &o)
        return *this;

    clear ();
    copy (o);

    return *this;
}


template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator= (RedBlackTree&& o) noexcept {

    if (this == &o)
        return *this;

    clear ();

    root = o.root;
    o.root = nullptr;

    msize = o.msize;
    o.msize = 0;

    return *this;
}


template <typename T>
RedBlackTree<T>::~RedBlackTree () {

    clear ();
}


template <typename T>
template <typename U>
bool RedBlackTree<T>::insert (U&& data) {

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
        n->p = c;
    }

    balance (n);
    msize++;
    return true;
}


template <typename T>
template <class... U>
bool RedBlackTree<T>::emplace (U&&... args) {

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

    balance (n);
    msize++;
    return true;
}


template <typename T>
void RedBlackTree<T>::balance (Node*& n) {

    // node is the root
    if (n->p == nullptr)
        n->red = false;
    //the parent is red
    else if (n->p->red) {

        if (n->p->p == nullptr) {
            n->p->red = false;
            return;
        }      

        uint8_t c{};
        Node* p{n->p}; // parent

        //node is a right child
        if (n != p->l)
            c = 1;

        Node* g{p->p}; // grandfather
        Node* u{}; // uncle

        //the parent is a right child of a grandfather
        if (p != g->l) {
            c |= uint8_t{2};
            u = g->l;
        } else
            u = g->r;

        // the uncle is red
        if (u != nullptr && u->red) {
            p->red = false;
            u->red = false;
            g->red = true;
            balance (g);
        }
        // the uncle is black
        else {
            switch (c) {
            // the node is a left child & the parent is a left child
            case 0:
                rotate_right (n, p, g);
                g->red = true;
                p->red = false;
                break;
            // the node is a right child & the parent is a left child
            case 1:
                rotate_left_s (n, p, g);
                rotate_right (p, n, g);
                g->red = true;
                n->red = false;
                break;
            // the node is a left child & the parent is a right child
            case 2:
                rotate_right_s (n, p, g);
                rotate_left (p, n, g);
                g->red = true;
                n->red = false;
                break;
            // the node is a right child & the parent is a right child
            case 3:
                rotate_left (n, p, g);
                g->red = true;
                p->red = false;
            }
        }
    }
}


template <typename T>
void RedBlackTree<T>::rotate_left (Node*& n, Node*& p, Node*& g) {

    g->r = p->l;
    if (g->r != nullptr)
        g->r->p = g;
    p->l = g;
    if (g->p != nullptr) {
        p->p = g->p;
        if (p->data < p->p->data)
            p->p->l = p;
        else
            p->p->r = p;
    }
    else {
        p->p = nullptr;
        root = p;
    }
    g->p = p;
}


template <typename T>
void RedBlackTree<T>::rotate_right (Node*& n, Node*& p, Node*& g) {

    g->l = p->r;
    if (g->l != nullptr)
        g->l->p = g;
    p->r = g;
    if (g->p != nullptr) {
        p->p = g->p;
        if (p->data < p->p->data)
            p->p->l = p;
        else
            p->p->r = p;
    }
    else {
        p->p = nullptr;
        root = p;
    }
    g->p = p;
}


template <typename T>
void RedBlackTree<T>::rotate_left_s (Node*& n, Node*& p, Node*& g) {

    n->p = g;
    g->l = n;
    p->r = n->l;
    if (p->r != nullptr)
        p->r->p = p;
    p->p = n;
    n->l = p;
}


template <typename T>
void RedBlackTree<T>::rotate_right_s (Node*& n, Node*& p, Node*& g) {

    n->p = g;
    g->r = n;
    p->l = n->r;
    if (p->l != nullptr)
        p->l->p = p;
    p->p = n;
    n->r = p;
}


template <typename T>
T* RedBlackTree<T>::find (const T& data) {

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
                return &c->data;
            }
        }
    }
    return nullptr;
}


template <typename T>
bool RedBlackTree<T>::erase (const T& data) {

    Node* n{root};
    if (n != nullptr) {
        while (true) {

            if (data < n->data) {

                if (n->l == nullptr)
                    return false;
                else
                    n = n->l;
            }
            else if (n->data < data) {

                if (n->r == nullptr)
                    return false;
                else
                    n = n->r;
            }
            else
                break;
        }
    }
    else
        return false;
    msize--;

    if (n->l != nullptr && n->r != nullptr) {

        Node* m{n->r};
        while (m->l != nullptr)
            m = m->l;

        n->data = std::move (m->data);
        n = m;
    }

    Node* p{n->p}; // parent

    // the node is root
    if (p == nullptr) {
        if (n->l != nullptr) {
            root = n->l;
            n->l->p = nullptr;
        }
        else if (n->r != nullptr) {
            root = n->r;
            n->r->p = nullptr;
        }
        else
            root = nullptr;
        if (root != nullptr)
            root->red = false;
        delete n;
        return true;
    }

    bool left{true};
    if (n != p->l)
        left = false;

    // the node is red (both siblings are null)
    if (n->red) {
        if (left)
            p->l = nullptr;
        else
            p->r = nullptr;
        delete n;
        return true;
    }
    // the node is black
    else {
        if (left) {
            if (n->l == nullptr && n->r == nullptr) 
                p->l = nullptr;
            else if (n->r != nullptr) {
                p->l = n->r;
                n->r->p = p;
            }
            else {
                p->l = n->l;
                n->l->p = p;
            }
        }
        else {
            if (n->l == nullptr && n->r == nullptr)
                p->r = nullptr;
            else if (n->r != nullptr) {
                p->r = n->r;
                n->r->p = p;
            }
            else {
                p->r = n->l;
                n->l->p = p;
            }
        }

        if (n->r != nullptr) {
            // node has a red child
            if (n->r->red) {
                n->r->red = false;
                delete n;
                return true;
            }
        }
        if (n->l != nullptr) {
            // node has a red child
            if (n->l->red) {
                n->l->red = false;
                delete n;
                return true;
            }
        }
        delete n;

        balance (p, left);
    }
}


template <typename T>
void RedBlackTree<T>::balance (Node*& p, bool left) {

    // case 1
    if (p == nullptr)
        return;

    Node* s{};
    Node* sl{};
    Node* sr{};

    // the node is the left child
    if (left) {

        s = p->r;
        sl = s->l;
        sr = s->r;

        // case 2: the brother is red
        if (s->red) {
            s->red = false;
            p->red = true;
            rotate_left (sr, s, p);
            s = sl;
            sl = s->l;
            sr = s->r;
        }
        // the brother becomes black
    }
    else {

        s = p->l;
        sl = s->l;
        sr = s->r;

        // case 2: the brother is red
        if (s->red) {
            s->red = false;
            p->red = true;
            rotate_right (sl, s, p);
            s = sr;
            sl = s->l;
            sr = s->r;
        }
        // the brother becomes black
    }

    // colors of siblings
    bool slb{true};
    if (sl != nullptr) {
        if (sl->red)
            slb = false;
    }
    bool srb{true};
    if (sr != nullptr) {
        if (sr->red)
            srb = false;
    }

    if (slb && sl != nullptr)
        std::cout << "";
    if (srb && sr != nullptr)
        std::cout << "";

    // case 3: siblings are black
    if (!p->red && slb && srb) {
        s->red = true;
        bool lft{true};
        if (p->p != nullptr) {
            if (p == p->p->r)
                lft = false;
        }
        balance (p->p, lft);
    }

    // case 4
    if (p->red && slb && srb) {
        s->red = true;
        p->red = false;
    }

    if (left) {

        // case 5
        if (!slb && srb) {
            rotate_right_s (sl, s, p);
            s->red = true;
            sl->red = false;
            s = sl;
            sl = s->l;
            sr = s->r;
            slb = true;
            if (sl != nullptr) {
                if (sl->red)
                    slb = false;
            }
            srb = false;
            if (sr != nullptr) {
                if (sr->red)
                    srb = false;
            }
        }

        // case 6
        if (!srb) {
            rotate_left (sr, s, p);
            s->red = p->red;
            p->red = false;
            sr->red = false;
        }
    }
    // the node is the right child
    else {

        // case 5
        if (!srb && slb) {
            rotate_left_s (sr, s, p);
            s->red = true;
            sr->red = false;
            s = sr;
            sl = s->l;
            sr = s->r;
            slb = true;
            if (sl != nullptr) {
                if (sl->red)
                    slb = false;
            }
            srb = false;
            if (sr != nullptr) {
                if (sr->red)
                    srb = false;
            }
        }

        // case 6
        if (!slb) {
            rotate_right (sl, s, p);
            s->red = p->red;
            p->red = false;
            sl->red = false;
        }
    }
}


template <typename T>
void RedBlackTree<T>::dprint () {

    for (auto& w : *this)
        std::cout << w << "\n";
}


template <typename T>
void RedBlackTree<T>::pprint (bool color, bool view) {

    Stack<Node*> nodes;
    if (root != nullptr)
        nodes.push (root);
    else
        return;

    std::string fname = std::format ("{:0>3}rbtree.", ++fnum);

    std::ofstream out (fname + "dv");
    if (!out)
        throw gexception (gexception::OpenFile);

    out << "digraph tree {\n";
    if (color)
        out << "node[style = \"filled\"]\n";
    while (!nodes.empty ()) {

        Node* c{nodes.top ()};
        nodes.pop ();

        std::string ccolor;
        if (c->red)
            ccolor = "red";
        else
            ccolor = "black";
        if (color)
            out << std::format ("\"{}\" [fillcolor={} fontcolor=white];\n", c->data, ccolor);
        if (c->l != nullptr) {

            nodes.push (c->l);
            out << std::format ("\"{}\" -> \"{}\" [label = L];\n", c->data, c->l->data);
        }
        if (c->r != nullptr) {

            nodes.push (c->r);
            out << std::format ("\"{}\" -> \"{}\" [label = R];\n", c->data, c->r->data);
        }
    }
    out << "}";
    out.close ();
    std::system (("dot.exe " + fname + "dv -Tpng > " + fname + "png").c_str ());

    if (view)
        system ((fname + "png").c_str ());
}


template <typename T>
void RedBlackTree<T>::clear () {

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
    msize = 0;
}


template <typename T>
size_t RedBlackTree<T>::size () {

    return msize;
}


template <typename T>
bool RedBlackTree<T>::empty () {

    return msize == 0;
}


template <typename T>
void RedBlackTree<T>::copy (const RedBlackTree<T>& o) {

    if (o.root == nullptr)
        return;

    Stack<std::pair<Node*, Node*>> nodes;
    nodes.push (std::make_pair (o.root, nullptr));

    while (!nodes.empty ()) {

        Node* sn{nodes.top ().first};

        Node* dn = new (std::nothrow) Node (sn->data);
        if (dn == nullptr)
            throw gexception (gexception::MemAlloc);
        dn->red = sn->red;

        if (sn->p != nullptr) {

            Node* odn{nodes.top ().second};
            if (sn == sn->p->l)
                odn->l = dn;
            else
                odn->r = dn;
            dn->p = odn;
        }
        else
            root = dn;

        nodes.pop ();

        if (sn->l != nullptr)
            nodes.push (std::make_pair (sn->l, dn));
        if (sn->r != nullptr)
            nodes.push (std::make_pair (sn->r, dn));
    }
    msize = o.msize;
}


template <typename T>
class RedBlackTree<T>::iterator {

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

    friend iterator RedBlackTree<T>::begin (void);
    friend iterator RedBlackTree<T>::end (void);

    Stack<Node*>* nodes;
};


template <typename T>
RedBlackTree<T>::iterator::iterator () {

    nodes = new Stack<Node*>;
}


template <typename T>
RedBlackTree<T>::iterator::iterator (const iterator& iterator) {

    nodes = new Stack<Node*>;
    *nodes = *(iterator.nodes);
}


template <typename T>
typename RedBlackTree<T>::iterator& RedBlackTree<T>::iterator::operator= (const iterator& iterator) {

    if (this == &iterator)
        return (*this);

    delete nodes;

    nodes = new Stack<Node*>;
    *nodes = *(iterator.nodes);

    return (*this);
}


template <typename T>
typename RedBlackTree<T>::iterator& RedBlackTree<T>::iterator::operator++ () {

    if (!nodes->empty ()) {

        Node* node = nodes->top ();
        nodes->pop ();

        if (node->r != nullptr)
            gotoMinimal (node->r);
    }

    return (*this);
}


template <typename T>
bool RedBlackTree<T>::iterator::operator!= (const iterator& iterator) const {

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
T& RedBlackTree<T>::iterator::operator* () {

    return nodes->top ()->data;
}


template <typename T>
T* RedBlackTree<T>::iterator::operator-> () {

    return &(nodes->top ()->data);
}


template <typename T>
typename RedBlackTree<T>::iterator RedBlackTree<T>::begin (void) {

    iterator it{};
    if (root != 0)
        it.gotoMinimal (root);

    return it;
}


template <typename T>
typename RedBlackTree<T>::iterator RedBlackTree<T>::end (void) {

    iterator it{};
    return it;
}


template <typename T>
RedBlackTree<T>::iterator::~iterator () {

    delete nodes;
}


template <typename T>
void RedBlackTree<T>::iterator::gotoMinimal (Node*& node) {

    if (node != nullptr)
        nodes->push (node);
    else
        return;

    while (nodes->top ()->l != nullptr)
        nodes->push (nodes->top ()->l);
}

#endif
