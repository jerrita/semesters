#include <iostream>
#include <cmath>
using namespace std;

class Shape
{
public:
    virtual void area() = 0;
};

class Triangle : virtual public Shape
{
public:
    double a, b, c;
    Triangle(double a, double b, double c) : a(a), b(b), c(c){};
    void area()
    {
        double p = (a + b + c) / 2.0;
        cout << "三角形面积为" << sqrt(p * (p - a) * (p - b) * (p - c)) << endl;
    }
};

class Circle : virtual public Shape
{
public:
    double r;
    Circle(double r) : r(r){};
    void area()
    {
        cout << "园面积为" << 3.14 * r * r << endl;
    }
};

int main()
{
    Shape *ps;
    float a, b, c, r;
    cin >> a >> b >> c;
    Triangle tt(a, b, c);
    cin >> r;
    Circle cc(r);
    ps = &tt;
    ps->area();
    ps = &cc;
    ps->area();
    return 0;
}