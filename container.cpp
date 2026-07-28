#include "vector_implementation.h"
#include <list>
#include <stdexcept>
#include <iostream>

class Container 
{
public:
    virtual double& operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() {}
};

class Vector_container : public Container 
{
public:
    Vector_container(int s) : v(s) {}
    ~Vector_container() {}

    double& operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }
private:
    Vector v;
};

class List_container : public Container 
{
public:
    List_container() {}
    List_container(std::initializer_list<double> il) : ld{il} {}
    ~List_container() {}

    double& operator[](int i) override;
    int size() const override { return ld.size(); }
private:
    std::list<double> ld;
};

double& List_container::operator[](int i)
{
    for (auto& x : ld) {
        if (i==0) return x;
        --i;
    }
    throw std::out_of_range{"List container"};
}

void use(Container& c)
{
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        std::cout << c[i] << '\n';
}

int main()
{
    Vector_container vc(5);
    for (int i = 0; i != vc.size(); ++i)
        vc[i] = i * 1.1;
    use(vc);

    List_container lc = {1, 2, 3, 4, 5};
    use(lc);
}