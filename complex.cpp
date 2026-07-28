#include <iostream>

class complex 
{
    double re, im;  
public:
    complex(double r, double i) :re{r}, im{i} {}  
    complex(double r) :re{r}, im{0} {}             
    complex() :re{0}, im{0} {}                      
    complex(const complex& z) :re{z.re}, im{z.im} {} 

    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }

    complex& operator+=(complex z)
    {
        re += z.re;
        im += z.im;
        return *this;
    }

    complex& operator-=(complex z)
    {
        re -= z.re;
        im -= z.im;
        return *this;
    }

    complex& operator*=(complex z)
    {
        double new_re = re*z.re - im*z.im;
        double new_im = re*z.im + im*z.re;
        re = new_re;
        im = new_im;
        return *this;
    }

    complex& operator/=(complex z)
    {
        double denom = z.re*z.re + z.im*z.im;
        double new_re = (re*z.re + im*z.im) / denom;
        double new_im = (im*z.re - re*z.im) / denom;
        re = new_re;
        im = new_im;
        return *this;
    }
};

complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; } 
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }

bool operator==(complex a, complex b) { return a.real()==b.real() && a.imag()==b.imag(); }
bool operator!=(complex a, complex b) { return !(a==b); }

void f(complex z)
{
    complex a {2.3};             
    complex b {1/a};
    complex c {a + 2*complex{1,2.3}};
    if (c != b)
        c = -(b/a) + 2*b;

    std::cout << "a = " << a.real() << " + " << a.imag() << "i\n";
    std::cout << "b = " << b.real() << " + " << b.imag() << "i\n";
    std::cout << "c = " << c.real() << " + " << c.imag() << "i\n";
}

int main()
{
    f(complex{1,2});
}