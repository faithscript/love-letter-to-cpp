#include <iostream> 

class Vector 
{
public: 
    Vector(int s) : elem{new double[s]}, sz{s} {}

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
    
    const double& Vector::operator[](int i) const
    {
        if (i < 0 || i >= sz)
            throw std::out_of_range("Vector::operator[] const: index out of range");
        return elem[i];
    }

    double& Vector::operator[](int i)
    {
        if (i < 0 || i >= sz)
            throw std::out_of_range("Vector::operator[]: index out of range");
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
    Vector v(5);
    for (int i = 0; i < v.size(); i++)
        v[i] = i * 1.5;

    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << '\n';
}