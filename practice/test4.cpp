#include <iostream>
using namespace std;

class MyData
{
    public:
    MyData() {cout<<"MyData()"<<endl;}
    //복사생성자 : 매개변수로 자기클래스 주소(참조자)받음
    MyData(const MyData &rhs):data_(rhs.data_)
    {
        cout<< "MyData(const MyData &)" << endl;
    }
    
    int GetData(void) const {return data_;}
    void SetData(int param)
    {
        data_ = param;
    }
    private:
    int data_;
};

int main()
{
    MyData a;
    a.SetData(10);
    TestFunc(a);
    cout<< a.GetData() <<endl;
    return 0;
}