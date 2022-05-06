#include "iostream"
using namespace std;

class person
{
public:
    person(string name, int age);
//    person(person &p);
    void show();
    person operator+(person &p);
    friend person operator-(person &p1, person &p2);

private:
    string name;
    int age;
};
// person::person(person& p){
// 	this->age = p.age;
// 	this->name = p.name;
// }
person::person(string name, int age)
{
    this->age = age;
    this->name = name;
}
person person::operator+(person &p)
{
    person tmp(p);
    tmp.age = this->age + p.age;
    tmp.name = this->name;
    return tmp;
}
person operator-(person &p1, person &p2)
    {
        person tmp(p1);
        tmp.age = p1.age - p2.age;
        tmp.name = p1.name;
        return tmp;
    }

void person::show()
{
    cout << "name: " << this->name << "age: " << this->age << endl;
}
int main()
{
    person p1("zhangsan", 25);
    person p2("lisi", 11);
    person p3 = p1 + p2;
    p3.show();
    return 0;
}