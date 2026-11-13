#ifndef _SLD_
#define _SLD_

#include<format>
#include<iostream>


class Sld {

private:

    int count{ -1 };
    static const int size{ 1000000 };
    void* p[size];
    void* pa[size];
    size_t b[size];
    size_t ba[size];
    void* pd[size];

public:

    Sld();
    ~Sld();

    void push(void* address, size_t bytes);
    
    void pusha(void* address, size_t bytes);
    
    void pushd(void* address);

    bool pop(void* address);

    bool popa(void* address);

    bool view_addrr{};
};

Sld::Sld() {
    for (int i = 0; i < size; i++) {
        p[i] = nullptr;
        pa[i] = nullptr;
        pd[i] = nullptr;
        b[i] = 0;
        ba[i] = 0;
    }
}

Sld::~Sld() {

    bool success = true;
    for (int i = 0; i < size; i++) {
        if (p[i] != nullptr && b[i] != -1) {
            success = false;
            std::cout << std::format("Memory leak detected: single, address {}, bytes {}\n", p[i], b[i]);
        }
    }
    for (int i = 0; i < size; i++) {
        if (pa[i] != nullptr && ba[i] != -1) {
            success = false;
            std::cout << std::format("Memory leak detected: array, address {}, bytes {}\n", pa[i], ba[i]);
        }
    }
    for (int i = 0; i < size; i++) {
        if (pd[i] != nullptr) {
            success = false;
            std::cout << std::format("Bad call to delete operator: address {}\n", p[i]);
        }
    }
    if (success)
        std::cout << std::format("No memory leaks detected\n");

}

void Sld::push(void* address, size_t bytes) {

    int m = -1;
    for (int i = 0; i < size; i++) {
        if (p[i] == nullptr) {
            m = i;
            break;
        }
    }
    if (m != -1) {
        p[m] = address;
        b[m] = bytes;
    }
}

void Sld::pusha(void* address, size_t bytes) {

    int m = -1;
    for (int i = 0; i < size; i++) {
        if (pa[i] == nullptr) {
            m = i;
            break;
        }
    }
    if (m != -1) {
        pa[m] = address;
        ba[m] = bytes;
    }
}

void Sld::pushd(void* address) {

    int m = -1;
    for (int i = 0; i < size; i++) {
        if (pd[i] == nullptr) {
            m = i;
            break;
        }
    }
    if (m != -1)
        pd[m] = address;
}

bool Sld::pop(void* address) {

    bool success = false;
    for (int i = 0; i < size; i++) {
        if (p[i] == address) {
            p[i] = nullptr;
            b[i] = 0;
            success = true;
            break;
        }
    }
    if (!success) {
        pushd(address);
        return false;
    }
    return true;
}

bool Sld::popa(void* address) {

    bool success = false;
    for (int i = 0; i < size; i++) {
        if (pa[i] == address) {
            pa[i] = nullptr;
            ba[i] = 0;
            success = true;
            break;
        }
    }
    if (!success) {
        pushd(address);
        return false;
    }
    return true;
}


Sld M;

void* operator new (size_t size) throw(std::bad_alloc)
{
    void* p = malloc(size);
    if (M.view_addrr)
        std::cout << p << " 01\n";
    M.push(p, size);
    return p;
}

void* operator new (size_t size, const std::nothrow_t&) throw()
{
    void* p = malloc(size);
    if (M.view_addrr)
        std::cout << p << " 02\n";
    M.push(p, size);
    return p;
}

void* operator new (size_t size, std::align_val_t al) throw(std::bad_alloc)
{
    void* p = malloc (size);
    if (M.view_addrr)
        std::cout << p << " 03\n";
    M.push (p, size);
    return p;
}

void* operator new (size_t size, std::align_val_t al, const std::nothrow_t&) throw()
{
    void* p = malloc (size);
    if (M.view_addrr)
        std::cout << p << " 04\n";
    M.push (p, size);
    return p;
}

void* operator new[](size_t size) throw(std::bad_alloc)
{
    void* p = malloc(size);
    if (M.view_addrr)
        std::cout << p << " 05\n";
    M.pusha(p, size);
    return p;
}

void* operator new[](size_t size, const std::nothrow_t&) throw()
{
    void* p = malloc(size);
    if (M.view_addrr)
        std::cout << p << " 06\n";
    M.pusha(p, size);
    return p;
}

void* operator new[] (size_t size, std::align_val_t al) throw(std::bad_alloc)
{
    void* p = malloc (size);
    if (M.view_addrr)
        std::cout << p << " 07\n";
    M.pusha (p, size);
    return p;
}

void* operator new[] (size_t size, std::align_val_t al, const std::nothrow_t&) throw()
{
    void* p = malloc (size);
    if (M.view_addrr)
        std::cout << p << " 08\n";
    M.pusha (p, size);
    return p;
}

void operator delete (void * p) throw()
{ 
    if (M.view_addrr)
        std::cout << "del: " << p << " 10\n";
    if (M.pop(p))
        free(p);   
}

void operator delete[] (void* p) throw()
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 12\n";
    if (M.popa (p))
        free (p);
}

void operator delete (void* p, std::align_val_t al) noexcept
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 15\n";
    if (M.pop (p))
        free (p);
}

void operator delete[] (void* p, std::align_val_t al) noexcept
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 16\n";
    if (M.popa (p))
        free (p);
}

void operator delete (void* p, std::size_t sz)
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 17\n";
    if (M.pop (p))
        free (p);
}

void operator delete[] (void* p, std::size_t sz) noexcept
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 18\n";
    if (M.popa (p))
        free (p);
}

void operator delete (void* p, std::align_val_t al, std::size_t sz) noexcept
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 19\n";
    if (M.pop (p))
        free (p);
}

void operator delete[] (void* p, std::align_val_t al, std::size_t sz) noexcept
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 20\n";
    if (M.popa (p))
        free (p);
}

void operator delete (void* p, const std::nothrow_t&) throw()
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 11\n";
    if (M.pop(p))
        free(p);
}

void operator delete[](void* p, const std::nothrow_t&) throw()
{
    if (M.view_addrr)
        std::cout << "del: " << p << " 14\n";
    if (M.popa(p))
        free(p);
}

#endif