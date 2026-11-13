#ifndef _REDBLACKTREEMULTI_
#define _REDBLACKTREEMULTI_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <initializer_list>

#include "list.hpp"
#include "stack.hpp"
#include "gexception.h"


template <typename T>
class RedBlackTreeMulti {
public:

    RedBlackTreeMulti () = default;
    RedBlackTreeMulti (const std::initializer_list<T>&);
    RedBlackTreeMulti (const RedBlackTreeMulti&);
    RedBlackTreeMulti (RedBlackTreeMulti&&) noexcept;
    RedBlackTreeMulti& operator= (const RedBlackTreeMulti&);
    RedBlackTreeMulti& operator= (RedBlackTreeMulti&&) noexcept;
    ~RedBlackTreeMulti ();

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

protected:

    struct Node {

        Node () = default;
        template <class... U>
        Node (U&&... args) {            
            data.emplace_back (std::forward<U> (args)...);
        }
        template <typename U>
        Node (U&& d) {        
            data.push_back (std::forward<U> (d));
        }

        bool red{true};
        Node* p{};
        Node* l{};
        Node* r{};
        List<T> data{};
    };

    void erase (Node*);

    Node* root{};

private:

    void copy (const RedBlackTreeMulti<T>&);

    void balance (Node*&);
    void balance (Node*&, bool);
    void rotate_left (Node*&, Node*&, Node*&);
    void rotate_right (Node*&, Node*&, Node*&);
    void rotate_left_s (Node*&, Node*&, Node*&);
    void rotate_right_s (Node*&, Node*&, Node*&);

    size_t msize{};
    uint16_t fnum{};
};


template <typename T>
RedBlackTreeMulti<T>::RedBlackTreeMulti (const std::initializer_list<T>& ilist) {

    for (auto& w : ilist)
        insert (w);
}


template <typename T>
RedBlackTreeMulti<T>::RedBlackTreeMulti (const RedBlackTreeMulti& o) {

    copy (o);
}


template <typename T>
RedBlackTreeMulti<T>::RedBlackTreeMulti (RedBlackTreeMulti&& o) noexcept {

    root = o.root;
    o.root = nullptr;

    msize = o.msize;
    o.msize = 0;
}


template <typename T>
RedBlackTreeMulti<T>& RedBlackTreeMulti<T>::operator= (const RedBlackTreeMulti& o) {

    if (this == &o)
        return *this;

    clear ();
    copy (o);

    return *this;
}


template <typename T>
RedBlackTreeMulti<T>& RedBlackTreeMulti<T>::operator= (RedBlackTreeMulti&& o) noexcept {

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
RedBlackTreeMulti<T>::~RedBlackTreeMulti () {

    clear ();
}


template <typename T>
template <typename U>
bool RedBlackTreeMulti<T>::insert (U&& data) {

    Node* c{root};
    bool f{};
    if (c != nullptr) {
        while (true) {

            if (data < c->data.front ()) {

                if (c->l == nullptr) {
                    f = true;
                    break;
                }
                else
                    c = c->l;
            }
            else if (c->data.front () < data) {

                if (c->r == nullptr) {
                    f = true;
                    break;
                }
                else
                    c = c->r;
            }
            else
                break;
        }
    }

    if (f || c == nullptr) {

        Node* n = new (std::nothrow) Node (std::forward<U> (data));
        if (n == nullptr)
            throw gexception (gexception::MemAlloc);

        if (c == nullptr)
            root = n;
        else {
            if (n->data.front () < c->data.front ())
                c->l = n;
            else
                c->r = n;
            n->p = c;
        }

        balance (n);
    }
    else
        c->data.push_back (std::forward<U> (data));

    msize++;

    return true;
}


template <typename T>
template <class... U>
bool RedBlackTreeMulti<T>::emplace (U&&... args) {

    Node* n = new (std::nothrow) Node (std::forward<U> (args)...);
    if (n == nullptr)
        throw gexception (gexception::MemAlloc);
    List<T>& data = n->data;

    Node* c{root};
    bool f{};
    if (c != nullptr) {
        while (true) {

            if (data.front () < c->data.front ()) {

                if (c->l == nullptr) {
                    f = true;
                    break;
                }
                else
                    c = c->l;
            }
            else if (c->data.front () < data.front ()) {

                if (c->r == nullptr) {
                    f = true;
                    break;
                }
                else
                    c = c->r;
            }
            else {
                delete n;
                return false;
            }
        }
    }

    if (f || c == nullptr) {

        if (c == nullptr)
            root = n;
        else {
            if (n->data.front () < c->data.front ())
                c->l = n;
            else
                c->r = n;
            n->p = c;
        }

        balance (n);
    }
    else
        c->data.emplace_back (std::forward<U> (args)...);

    msize++;
    return true;
}


template <typename T>
void RedBlackTreeMulti<T>::balance (Node*& n) {

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
        Node* u; // uncle

        //the parent is a right child of a grandfather
        if (p != g->l) {
            c |= uint8_t{2};
            u = g->l;
        }
        else
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
void RedBlackTreeMulti<T>::rotate_left (Node*& n, Node*& p, Node*& g) {

    g->r = p->l;
    if (g->r != nullptr)
        g->r->p = g;
    p->l = g;
    if (g->p != nullptr) {
        p->p = g->p;
        if (p->data.front() < p->p->data.front ())
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
void RedBlackTreeMulti<T>::rotate_right (Node*& n, Node*& p, Node*& g) {

    g->l = p->r;
    if (g->l != nullptr)
        g->l->p = g;
    p->r = g;
    if (g->p != nullptr) {
        p->p = g->p;
        if (p->data.front () < p->p->data.front ())
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
void RedBlackTreeMulti<T>::rotate_left_s (Node*& n, Node*& p, Node*& g) {

    n->p = g;
    g->l = n;
    p->r = n->l;
    if (p->r != nullptr)
        p->r->p = p;
    p->p = n;
    n->l = p;
}


template <typename T>
void RedBlackTreeMulti<T>::rotate_right_s (Node*& n, Node*& p, Node*& g) {

    n->p = g;
    g->r = n;
    p->l = n->r;
    if (p->l != nullptr)
        p->l->p = p;
    p->p = n;
    n->r = p;
}


template <typename T>
T* RedBlackTreeMulti<T>::find (const T& data) {

    Node* c{root};
    if (c != nullptr) {
        while (true) {

            if (data < c->data.front ()) {

                if (c->l == nullptr)
                    break;
                else
                    c = c->l;
            }
            else if (c->data.front () < data) {

                if (c->r == nullptr)
                    break;
                else
                    c = c->r;
            }
            else {
                return &c->data.front ();
            }
        }
    }
    return nullptr;
}


template <typename T>
bool RedBlackTreeMulti<T>::erase (const T& data) {

    Node* n{root};
    if (n != nullptr) {
        while (true) {

            if (data < n->data.front ()) {

                if (n->l == nullptr)
                    return false;
                else
                    n = n->l;
            }
            else if (n->data.front () < data) {

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

    erase (n);

    return true;
}


template <typename T>
void RedBlackTreeMulti<T>::erase (Node* n) {

    msize--;

    n->data.pop_front ();
    if (!n->data.empty ())
        return;

    if (n->l != nullptr && n->r != nullptr) {

        Node* m = n->r;
        while (m->l != nullptr)
            m = m->l;

        n->data = std::move (m->data);
        n = m;
    }

    Node* p = n->p; // parent

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
        return;
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
        return;
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
                return;
            }
        }
        if (n->l != nullptr) {
            // node has a red child
            if (n->l->red) {
                n->l->red = false;
                delete n;
                return;
            }
        }
        delete n;

        balance (p, left);
    }
}


template <typename T>
void RedBlackTreeMulti<T>::balance (Node*& p, bool left) {

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
void RedBlackTreeMulti<T>::dprint () {

    for (auto& w : *this)
        std::cout << w << "\n";
}


template <typename T>
void RedBlackTreeMulti<T>::pprint (bool color, bool view) {

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
    std::system (("dot.exe " + fname + "dv -Nfontname=helvetica -Gdpi=300 -Tpng > " + fname + "png").c_str ());

    if (view)
        system ((fname + "png").c_str ());   
}


template <typename T>
void RedBlackTreeMulti<T>::clear () {

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
size_t RedBlackTreeMulti<T>::size () {

    return msize;
}


template <typename T>
bool RedBlackTreeMulti<T>::empty () {

    return msize == 0;
}


template <typename T>
void RedBlackTreeMulti<T>::copy (const RedBlackTreeMulti<T>& o) {

    if (o.root == nullptr)
        return;

    Stack<std::pair<Node*, Node*>> nodes;
    nodes.push (std::make_pair (o.root, nullptr));

    while (!nodes.empty ()) {

        Node* sn{nodes.top ().first};

        Node* dn = new (std::nothrow) Node;
        if (dn == nullptr)
            throw gexception (gexception::MemAlloc);
        dn->red = sn->red;
        for (auto& e : sn->data)
            dn->data.push_back (e);

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
class RedBlackTreeMulti<T>::iterator {

public:

    iterator ();
    iterator (const iterator&);
    iterator& operator= (const iterator&);
    ~iterator ();

    iterator& operator++ ();

    bool operator!= (const iterator&);

    T& operator* ();

    T* operator-> ();

private:

    void gotoMinimal (Node*&);

    friend iterator RedBlackTreeMulti<T>::begin (void);
    friend iterator RedBlackTreeMulti<T>::end (void);

    Stack<Node*>* nodes;
    typename List<T>::iterator element;
};


template <typename T>
RedBlackTreeMulti<T>::iterator::iterator () {

    nodes = new Stack<Node*>;
}


template <typename T>
RedBlackTreeMulti<T>::iterator::iterator (const iterator& iterator) {

    nodes = new Stack<Node*>;
    *nodes = *(iterator.nodes);
    element = iterator.element;
}


template <typename T>
typename RedBlackTreeMulti<T>::iterator& RedBlackTreeMulti<T>::iterator::operator= (const iterator& iterator) {

    if (this == &iterator)
        return (*this);

    delete nodes;

    nodes = new Stack<Node*>;
    *nodes = *(iterator.nodes);
    element = iterator.element;

    return (*this);
}


template <typename T>
typename RedBlackTreeMulti<T>::iterator& RedBlackTreeMulti<T>::iterator::operator++ () {

    if (!nodes->empty ()) {

        ++element;
        if (element != nodes->top ()->data.end ())
            return (*this);

        Node* n = nodes->top ();
        nodes->pop ();

        if (n->r != nullptr) 
            gotoMinimal (n->r);
        else if (!nodes->empty ())
            element = nodes->top ()->data.begin ();
    }

    return (*this);
}


template <typename T>
bool RedBlackTreeMulti<T>::iterator::operator!= (const iterator& iterator) {

    if (nodes->empty () || iterator.nodes->empty ()) {
        if (nodes->empty () && iterator.nodes->empty ())
            return false;
        else
            return true;
    }

    if (&(nodes->top ()) != &(iterator.nodes->top ()))
        return true;
    else
        return true;
}


template <typename T>
T& RedBlackTreeMulti<T>::iterator::operator* () {

    return (*element);
}


template <typename T>
T* RedBlackTreeMulti<T>::iterator::operator-> () {

    return (&(*element));
}


template <typename T>
typename RedBlackTreeMulti<T>::iterator RedBlackTreeMulti<T>::begin (void) {

    iterator it{};
    if (root != 0)
        it.gotoMinimal (root);

    return it;
}


template <typename T>
typename RedBlackTreeMulti<T>::iterator RedBlackTreeMulti<T>::end (void) {

    iterator it{};
    return it;
}


template <typename T>
RedBlackTreeMulti<T>::iterator::~iterator () {

    delete nodes;
}


template <typename T>
void RedBlackTreeMulti<T>::iterator::gotoMinimal (Node*& pNode) {

    if (pNode != nullptr)
        nodes->push (pNode);
    else
        return;

    while (nodes->top ()->l != nullptr)
        nodes->push (nodes->top ()->l);

    element = nodes->top ()->data.begin ();
}

#endif
