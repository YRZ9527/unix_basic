#include "iostream"
#include "string"
using namespace std;

// class A 
// {
//     public:
//     A()
//     {
//         cout<<"hello"<<endl;
//     }
//     // A(A &p)
//     // {
//     //     cout<<"copy constructor called"<<endl;
//     // }
// };
class person
{
    public:
    int age;
    string name;
    person(string name, int age) : name(name), age(age){};
//    person(person& p){cout<<"copy called"<<endl;}
    void show();
    person operator+(person& p);
    void operator<<(ostream& cout);
};
void person::show()
{
    cout << "name: " << this->name << "age: " << this->age << endl;
}

person person::operator+(person &p)
{
    person tmp(p);
    tmp.age = this->age + p.age;
    tmp.name = this->name;
    return tmp;
}
void person::operator<<(ostream& cout)
{
    cout<<"name:"<<name<<" \tage:"<<age<<endl;
}
int main() {
    person p1("zhangshan",20);
    person p2("lisi",21);
    person p3 = p1 + p2;
    p1<<cout;
}