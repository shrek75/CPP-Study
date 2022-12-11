#include <iostream>

class MyPhoneNumber
{
private:
    int a_;
    char name_[32];
    char &phone_number_; //참조형 멤버는 객체가 생성될 때 반드시 초기화해야한다.
    int & age_;
public:
    MyPhoneNumber(char &x,int &age) :phone_number_(x),age_(age)
    {
        
    }
    MyPhoneNumber(char &x,int &age,int d): MyPhoneNumber(x,age)
    {
        a_ = d;
    }
};



int main()
{
    int age = 30;
    char phone_number[32] = {"01064149722"};
    MyPhoneNumber taeuk(*phone_number,age);
    MyPhoneNumber taeuk2(*phone_number,age,100);

    return 0;
}