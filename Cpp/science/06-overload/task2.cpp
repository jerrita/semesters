#include <cmath>
#include <iostream>
using namespace std;
class CFraction
{
private:
  int nume; //  分子
  int deno; //  分母
public:
  CFraction(int nu = 0, int de = 1) : nume(nu), deno(de) {}
  void simplify();

  //输入输出的重载
  friend istream &operator>>(istream &in, CFraction &x);
  friend ostream &operator<<(ostream &out, CFraction x);

  friend CFraction operator+(const CFraction &c1,
                             const CFraction &c2); //两个分数相加，结果要化简
  friend CFraction operator-(const CFraction &c1,
                             const CFraction &c2); //两个分数相减，结果要化简
  friend CFraction operator*(const CFraction &c1,
                             const CFraction &c2); //两个分数相乘，结果要化简
  friend CFraction operator/(const CFraction &c1,
                             const CFraction &c2); //两个分数相除，结果要化简
};

istream &operator>>(istream &in, CFraction &x)
{
  char c;
  in >> x.nume >> c >> x.deno;
  x.simplify();
  return in;
}

ostream &operator<<(ostream &out, CFraction x)
{
  if (x.deno == 1)
    out << x.nume;
  else
    out << x.nume << '/' << x.deno;
  return out;
}

CFraction operator+(const CFraction &c1,
                    const CFraction &c2)
{
  CFraction res;
  res.nume = c1.deno * c2.nume + c1.nume * c2.deno;
  res.deno = c1.deno * c2.deno;
  res.simplify();
  return res;
}

CFraction operator-(const CFraction &c1,
                    const CFraction &c2)
{
  CFraction res;
  res.nume = c1.nume * c2.deno - c1.deno * c2.nume;
  res.deno = c1.deno * c2.deno;
  res.simplify();
  return res;
}

CFraction operator*(const CFraction &c1,
                    const CFraction &c2)
{
  CFraction res;
  res.nume = c1.nume * c2.nume;
  res.deno = c1.deno * c2.deno;
  res.simplify();
  return res;
}

CFraction operator/(const CFraction &c1,
                    const CFraction &c2)
{
  CFraction res;
  res.nume = c2.deno;
  res.deno = c2.nume;
  res = res * c1;
  res.simplify();
  return res;
}

void CFraction::simplify()
{
  for (int i = max(abs(nume), abs(deno)); i >= 2; i--)
  {
    if (nume % i || deno % i)
      continue;
    else
    {
      nume /= i;
      deno /= i;
    }
  }
}

int main()
{
  CFraction x, y, s;
  cout << "Input  x:  ";
  cin >> x;
  cout << "Input  y:  ";
  cin >> y;
  s = x + y;
  cout << "x+y=" << s << endl;
  s = x - y;
  cout << "x-y=" << s << endl;
  s = x * y;
  cout << "x*y=" << s << endl;
  s = x / y;
  cout << "x/y=" << s << endl;
  return 0;
}
