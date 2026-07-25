module;
#include <stdexcept>
export module Vector;


export class Vector
{
public:
    Vector(int s);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();
    const double& operator[](int i) const;
    double& operator[](int i);
    int size() const;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
private:
    double* elem;
    int sz;
};

Vector::Vector(int s) : elem{new double[s]}, sz{s} {}
Vector::Vector(const Vector& other) : elem{new double[other.sz]}, sz{other.sz}
{
    for(int i = 0; i!=sz; i++){
        elem[i] = other.elem[i];
    }
}
Vector::Vector(Vector&& other) noexcept : elem{other.elem}, sz{other.sz}
{
    other.elem = nullptr;
    other.sz = 0;
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
int Vector::size() const { return sz; }

Vector& Vector::operator=(const Vector& other)
{
    if(this == &other) return *this;

    delete[] elem;

    elem = new double[other.sz];
    sz = other.sz;

    for(int i = 0; i!=sz; i++){
        elem[i] = other.elem[i];
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if(this == &other) return *this;

    delete[] elem;

    elem = other.elem;
    sz = other.sz;

    other.elem = nullptr;
    other.sz = 0;

    return *this;
}

Vector::~Vector() {delete[] elem;}

export bool operator==(const Vector& v1, const Vector& v2)
{
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i != v1.size(); ++i)
        if (v1[i] != v2[i]) return false;
    return true;
}