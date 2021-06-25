#include <iostream>
using namespace std;

class Clock
{
public:
    int h, m, sec;
    Clock(){};
    Clock(int h, int m, int sec) : h(h), m(m), sec(sec){};

    void setTime()
    {
        cin >> h >> m >> sec;
    }

    void showTime()
    {
        if (h >= 24 || m >= 60 || sec >= 60)
            cout << "illegal time" << endl;
        else
            cout << h << ':' << m << ':' << sec << endl;
    }
};

int main()
{
    Clock clock;
    clock.setTime();
    clock.showTime();
    return 0;
}