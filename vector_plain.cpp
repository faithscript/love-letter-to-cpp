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
    int size() const { return sz; }

    ~Vector() { delete[] elem; }

private:
    double* elem;
    int sz;
};  

int main()
{
    //length_error — negative size passed to constructor
    try {
        Vector bad(-27);
    }
    catch (const std::length_error& e) {
        std::cout << e.what() << '\n';
    }

    //out_of_range, valid Vector, bad index
    Vector v(5);
    for (int i = 0; i < v.size(); i++)
        v[i] = i * 1.5;

    try {
        std::cout << v[10] << '\n';
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
    }

    // const version of operator[]
    const Vector& cv = v;
    try {
        std::cout << cv[-1] << '\n';
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
    }

    //bad_alloc — large allocation
    try {
        Vector huge(2'000'000'000);
    }
    catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }
    catch (const std::length_error& e) {
        std::cout << e.what() << '\n';
    }

    std::cout << "Program continues normally after all catches.\n";
}