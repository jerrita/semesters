#include <bits/stdc++.h>
using namespace std;

class Fraction
{
public:
    int molecular;
    int denominator;

    friend ostream &operator<<(ostream &os, const Fraction &me)
    {
        Fraction res = me;
        res.reduce();
        if (res.molecular % res.denominator)
            os << res.molecular << '/' << res.denominator;
        else
            os << res.molecular / res.denominator;
        return os;
    }

    void scanf()
    {
        cin >> molecular;
        getchar();
        cin >> denominator;
        reduce();
    }

    void reduce()
    {
        for (int i = 2; i <= sqrt(max(abs(molecular), abs(denominator))); i++)
        {
            if (molecular % i || denominator % i)
                continue;

            molecular /= i;
            denominator /= i;
        }
    }

    Fraction operator+(const Fraction &b)
    {
        Fraction res;
        res.molecular = molecular * b.denominator + b.molecular * denominator;
        res.denominator = denominator * b.denominator;
        res.reduce();
        return res;
    }

    Fraction operator-(const Fraction &b)
    {
        Fraction res;
        res.molecular = molecular * b.denominator - b.molecular * denominator;
        res.denominator = denominator * b.denominator;
        res.reduce();
        return res;
    }

    Fraction operator*(const Fraction &b)
    {
        Fraction res;
        res.molecular = molecular * b.molecular;
        res.denominator = denominator * b.denominator;
        res.reduce();
        return res;
    }

    Fraction operator/(const Fraction &b)
    {
        Fraction reciprocal, res;
        reciprocal.denominator = b.molecular;
        reciprocal.molecular = b.denominator;
        res = *this * reciprocal;
        res.reduce();
        return res;
    }
};

int main()
{
    Fraction x, y;
    cout << "Input x: ";
    x.scanf();
    cout << "Input y: ";
    y.scanf();
    cout << "x+y=" << x + y
         << "\nx-y=" << x - y
         << "\nx*y=" << x * y
         << "\nx/y=" << x / y << endl;
    return 0;
}