#include <iostream>
#include <memory>

using namespace std;

template<typename T>
T Add(T a,T b){return a+b;}
template<>
char * Add(char * left,char * right)
{
    int len_left = strlen(left);
    int len_right = strlen(right);
    char *result = new char[len_left+len_right+1];

    strcpy(result,left);
    strcpy(result+len_left,right);

    return result;
}

int main()
{
    char a[6] = {"Hello"};
    char b[6] = {"World"};
    cout << Add(a,b) << endl;
    return 0;
}