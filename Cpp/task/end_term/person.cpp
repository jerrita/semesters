#include <iostream>
using namespace std;

class Person
{
public:
    string name;
    char sex;
    int age;
    bool right;

    Person(string name, char sex, int age) : name(name), sex(sex), age(age)
    {
        right = true;
        switch (sex)
        {
        case 'w':
        case 'W':
        case 'm':
        case 'M':
            break;
        default:
            right = false;
        }
        if (age <= 0)
            right = false;
    };

    void show()
    {
        if (right)
            cout << "姓名:" << name << endl
                 << "性别:" << sex << endl
                 << "年龄:" << age << endl;
        else
            cout << "信息错误!" << endl;
    };
};

class Student : public Person
{
public:
    int num;
    double score;
    bool right2;
    Student(int num, string name, char sex, int age, double score) : num(num), score(score), Person(name, sex, age)
    {
        right2 = true;
        if (num <= 0 || score < 0)
            right2 = false;
    };
    void show()
    {

        if (!right2)
        {
            cout << "信息错误!" << endl;
            return;
        }

        cout << "学号:" << num << endl;
        Person::show();
        cout << "成绩:" << score << endl;
    }
};

int main()
{
    string name;
    char sex;
    int age, num;
    double score;
    cin >> num >> name >> sex >> age >> score;
    Person p(name, sex, age);
    p.show();

    if (!p.right)
        return 0;

    cout << endl;
    Student s(num, name, sex, age, score);
    s.show();
    return 0;
}