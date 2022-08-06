#include"iostream"
#include<memory>
#include<vector>

using namespace std;

struct C {
    int m_number;

    C() {
        printf("分配内存!\n");
        m_number = 42;
    }

    ~C() {
        printf("释放内存!\n");
        m_number = -2333333;
    }

    void do_something() {
        printf("我的数字是 %d!\n", m_number);
    }
};

std::vector<std::shared_ptr<C>> objlist;

void func(std::shared_ptr<C> p)
{
  objlist.push_back(std::move(p));
}

int main()
{
  std::shared_ptr<C> p = std::make_shared<C>();
  cout<<"use_count"<<p.use_count()<<endl;

  func(p);
  cout<<"use_count"<<p.use_count()<<endl;
  func(p);
  p->do_something();
  objlist.clear();
  cout<<"use_count"<<p.use_count()<<endl;
  p->do_something();
  return 0;

}
