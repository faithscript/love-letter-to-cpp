#pragma once
#include <iostream>
#include <stdexcept>  
#include <new>

class Vector 
{
public: 
    Vector(int s)
    {
        if (s < 0){
            throw std::length_error{"Vector()"};
        }
        elem = new double[s];
        sz = s;
    }

    Vector::Vector(std::initializer_list<double> lst)   
        : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
    {
        std::copy(lst.begin(), lst.end(), elem);  
    }

    Vector(const Vector& other) : elem{new double[other.sz]}, sz{other.sz} 
    {
        for(int i = 0; i != sz; i++){
            elem[i] = other.elem[i];
        }
    }

    Vector(Vector&& other) noexcept : elem{other.elem}, sz{other.sz}
    {
        other.elem = nullptr;
        other.sz = 0;
    }


    Vector& operator=(const Vector& other)
    {
        if(this == &other) { return *this; }

        delete[] elem;
        elem = new double[other.sz];
        sz = other.sz;

        for(int i = 0; i != sz; i++){
            elem[i] = other.elem[i];
        }

        return *this;      
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if(this == &other) return *this;

        delete[] elem;
        elem = other.elem;
        sz = other.sz;

        other.elem = nullptr;
        other.sz = 0;

        return *this;
    }
    
    const double& operator[](int i) const
    {
        if (i < 0 || i >= sz) {
            throw std::out_of_range("operator[] const");
        }
        return elem[i];
    }

    double& operator[](int i)
    {
        if (i < 0 || i >= sz) {
            throw std::out_of_range("operator[]");
        }
        return elem[i];
    }
    void push_back(double d)
    {
        double* new_elem = new double[sz + 1];   

        for (int i = 0; i != sz; ++i)            
            new_elem[i] = elem[i];

        new_elem[sz] = d;                        

        delete[] elem;                          
        elem = new_elem;                           
        ++sz;                                     
    }
    int size() const { return sz; }

    ~Vector() { delete[] elem; }

private:
    double* elem;
    int sz;
};  
