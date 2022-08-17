#include"iostream"
#include"vector"
using namespace std;

void test(int &)
{
  cout<<"int const"<<endl;
}

void test(int const&)
{
  cout<<"int const"<<endl;
}

void test(int &&)
{
  cout<<"int &&"<<endl;
}

int main()
{
  int a = 0;
  int *p = &a;
  test(a);
  test(*p);
  test(p[a]);
  test(1);
  test(a + 1);
  test(*p + 1);

  const int b = 3;
  test(b);
  test(b + 1);

}

