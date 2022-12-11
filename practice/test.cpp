#include <iostream>
#include "CMyString.h"
#include "CMyString.cpp"
void TestFunc(const CMyString& param){
    std::cout<<param.GetString() <<std::endl;
}
void TestFunc2(const CMyString & param)
{
    std::cout << param[0] << std::endl;
    std::cout << param[param.GetLength() - 1] << std::endl;
}
int main()
{
    CMyString param("HelloWorld");
    std::cout << param << std::endl;
    TestFunc2(param);
    return 0;
}