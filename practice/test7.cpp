#include <iostream>
using namespace std;

class TestData
{
    public:
    //매개변수가 하나인 생성자는 어떤함수에서 매개변수로 클래스를 받을때 변환생성될 수 있다.
    TestData(int param):data_(param)
    {
        cout << "TestData(int)" << endl;
    }
    TestData(const TestData & rhs):data_(rhs.data_)
    {
        cout << "TestData(const TestData&)" << endl;
    }
    ~TestData()
    {
        cout << "~TestData()" << endl;
    }
    operator int(void) {return data_;}
    private: int data_;
    public:
    int GetData() const
    {
        return data_;
    }
    void SetData(int param){data_ = param;}
};
void TestFunc(TestData param)
{
    cout << "TestFunc() : " << param.GetData() << endl;
    return;
}
void TestFunc2(const TestData &param)
{
    cout << "TestFunc2() : " << param.GetData() << endl;
    return;
}


int main()
{
    //int 자료형에서 TestData자료형으로 변환될 수 있다.
   TestFunc(5);
    //main에서 만들고 주소보내주는거 (이름없는임시객체)
    TestFunc2(10); //TestFunc2(TestData(10));
    cout << static_cast<int>(TestData(20)) << endl;
    return 0;
}