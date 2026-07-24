#include <iostream> 

class Vector 
{
public: 
    Vector(int s) : elem{new double[s]}, sz{s} {}

    // Copy Constructor
    Vector(const Vector& other) : elem{new double[other.sz]}, sz{other.sz} 
    {
        for(int i = 0; i != sz; i++){
            elem[i] = other.elem[i];
        }
    }


    // Copy Assignment
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

    const double& operator[](int i) { return elem[i]; }

    const int size() { return sz; }

    ~Vector() { delete[] elem; }

private:
    double* elem;
    int sz;
};  

