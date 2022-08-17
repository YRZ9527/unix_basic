#include"iostream"
#include"vector"
using namespace std;
template<typename T>

std::ostream &operator<<(std::ostream &os, std::vector<T> const &a)
{
  os<<"{";
  for(size_t i = 0; i < a.size(); i++)
  {
    os<<a[i];
    if(i != a.size() - 1)
      os<< ",";
  }
  os<<"}";
  return os;
}

int main()
{
  vector<int> a = {1,4,2,8,5,7};
  cout<<a<<endl;
  
  vector<double> b = {3.14,2.718,0.618};
  cout<<b<<endl;
  return 0;
}
