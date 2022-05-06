#include "iostream"
#include "string"
using namespace std;

class base
{
public:
    virtual void display() 
    {
        cout<<"\n"<<endl;
    }
};

class child : public base
{
public:
    void display()
    {
        cout << "hello" << endl;
    }
};
class people
{
protected:
    string name;
    int age;

public:
    people(string name, int age) : name(name), age(age){};
    virtual void display();
};

void people::display()
{
    cout << "name: " << this->name << " age: " << this->age << endl;
}

class teacher : public people
{
private:
    int salary;

public:
    teacher(string name, int age, int salary) : people(name, age) { this->salary = salary; }
    void display();
};

void teacher::display()
{
    cout << "name: " << name << "\tage: " << age << "\t是个教师，收入为:" << salary << endl;
}
int main()
{

    people p("张三", 24);
    base Ba;
    child Ch;


    p.display();
    teacher t("wuzhibo", 43, 13231);
    t.display();
    cout << "sizeof(Ba):" << sizeof(Ba) << endl;
    cout << "sizeof(Ch):" << sizeof(Ch) << endl;

    return 0;
}
