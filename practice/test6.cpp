#include <iostream>
#include "CMyString.h"
#include "CMyString.cpp"
using namespace std;
int main()
{
    CMyString data,test;
    data.SetString("Hello");
    test.SetString("World");

    CMyString new_data(data);
    cout <<new_data.GetString()<<endl;

    new_data = test;
    cout << new_data.GetString()<<endl;

    data.Release();
    test.Release();
    new_data.Release();
    return 0;

}