
#include <iostream>
#include <stdlib.h>
using namespace std;

class CTime
{
public:
    int h, m, s;
    CTime(int h, int m, int s) : h(h), m(m), s(s)
    {
        if (s >= 60 || m >= 60 || h >= 24)
        {
            cout << "Input Error!" << endl;
            exit(0);
        }
    };

    void showTime()
    {
        cout << h << ':' << m << ':' << s << endl;
    }

    CTime &operator++()
    {
        s += 1;
        if (s == 60)
            m += 1, s = 0;
        if (m == 60)
            h += 1, m = 0;
        if (h == 24)
            h = 0;
        return *this;
    }
};

int main()
{
    int h, m, s;
    cout << "Input  hour  minute  second:" << endl;
    cin >> h >> m >> s;
    CTime t(h, m, s);
    cout << "Before++:";
    t.showTime();
    ++t;
    cout << "After++:";
    t.showTime();
}
