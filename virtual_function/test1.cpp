#include"iostream"
using namespace std;

class people
{
    public:
    people(string name, int age) : name(name), age(age){};
    void display();
    protected:
    string name;
    int age;

};
void people::display()
{
    cout<<"name: "<<this->name<<" age: "<<this->age<<endl;
}

class teacher : public people{
    private:
    int salary;
    public:
    teacher(string name, int age,int salary):people(name, age){this->salary=salary;}
    void display();
};

// teacher::teacher(string name,int age,int salary):people(name,age){
//     this->salary = salary;
// }

void teacher::display()
{
    cout << "name: " << name << "\tage: " << age << "\t是个教师，收入为:" << salary << endl;

}
int main()
{

    people p("张三",24);
    people &rp = p;

   
    teacher t("wuzhibo",43,13231);
    teacher &rt = t;
   // t.display();
   rp.display();
   rt.display();
   rp = rt;
   rp.display();


    return 0;
}