#include <iostream>

template <typename T = int , int nSize=0>
T TestFunc(T x, T y)
{
  //  if(nSize == 0) return NULL;
    return x+y;
}
int main()
{
    TestFunc< >(1,2);
    return 0;
}