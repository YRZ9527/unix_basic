#include"iostream"
#include <memory>
#include <vector>
using namespace std;

struct C{
  int m_number;
  C()
  {
    std::cout<<"分配内存"<<endl;
    m_number = 42;
  }
  ~C()
  {
    std::cout<<"释放内存"<<endl;
    m_number = -23333;
  }

  void do_something()
  {
    std::cout<<"我的数字是"<<m_number<<endl;
  }
};

std::vector<std::unique_ptr<C>> objlist;

void func(std::unique_ptr<C> p)
{
  objlist.push_back(std::move(p));
}

int main()
{
  std::unique_ptr<C> p = std::make_unique<C>();
  C *raw_p = p.get();
  func(std::move(p));
  raw_p->do_something();
  objlist.clear();

  raw_p->do_something();
  return 0;
}
