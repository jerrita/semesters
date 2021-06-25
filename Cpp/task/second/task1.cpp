#include <iostream>
#include <string>
using namespace std;

class CPerson
{
public:
  string name;
  int age;

  CPerson(string name, int age) : name(name), age(age){};
  virtual void display()
  {
    cout << "Age:" << age << endl
         << "Name:" << name << endl;
  }
};

class CTeacher : public CPerson
{
public:
  string title;
  string major;
  CTeacher(int age, string name, string major, string title) : CPerson(name, age), title(title), major(major){};

  virtual void display()
  {
    if (age < 26)
      cout << "Input Error!" << endl;
    else
      cout << "Age:" << age << endl
           << "Name:" << name << endl
           << "Major:" << major << endl
           << "Title:" << title << endl;
  }
};

int main()
{
  int age;
  string n, m, t;

  cout << "Input age name major title:" << endl;
  cin >> age >> n >> m >> t;

  CTeacher tt(age, n, m, t);
  CPerson *p = &tt;
  p->display();
}