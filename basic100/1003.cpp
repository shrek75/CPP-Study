#include <iostream>
#include <string.h>
int GetPlus(int &x,int &y)
{
    return x+y;
}

template <typename T>
int Swap(T &x,T &y)
{
    T temp = x;
    x = y;
    y = temp;

    return 0;
}
class MyClass
{
    public:
    MyClass(int age,const char * name)
    {
        age_ = age; 
        strcpy(name_,name);
    }
    private:
    int age_;
    char name_[32];

    public:
    void Print(void)
    {
        std::cout << age_ << " " << name_ << std::endl;
    }
};

int main()
{
    MyClass taeuk(24,"김태욱");
    taeuk.Print();
    return 0;
}