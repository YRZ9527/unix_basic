#include"iostream"
using namespace std;

template<typename T>
T twice(T t)
{
  return t * 2;
}

template<typename T>
T sum(std::vector<T> const &arr)
{
  T res = 0;
  for(int i = 0; i < arr.size(); i++)
  {
    res += arr[i];
  }
  return res;
}

std::string twice(std::string t)
{
  return t + t;
}

int main()
{
  std::vector<int> a = {4,3,2,1};
  std::cout<<sum(a)<<endl;
  vector<float> b = {3.14f,2.718f};
  cout<<sum(b)<<endl;
  //cout<<twice(21)<<endl;
  //cout<<twice(3.14f)<<endl;
  //cout<<twice(23.7198)<<endl;
  //cout<<twice("hello")<<endl;
  return 0;
}
