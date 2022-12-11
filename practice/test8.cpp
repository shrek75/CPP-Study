#include <iostream>
using namespace std;

class MyClass{
    public:
    MyClass(){cout << "MyClass()"<<endl;}
    MyClass(const MyClass& rhs)
    {
        data_ = rhs.data_;
//        *pdata_ = *(rhs.pdata_);
        cout << "MyClass(const MyClass &)"<<endl;
    }
    MyClass(const MyClass && rhs)
    {
        data_ = rhs.data_;
    //    pdata_ = rhs.pdata_;
        cout << "MyClass(const MyClass &&)"<<endl;
    }
    MyClass(int param)
    {
        data_ = param;
        cout << "MyClass(int)"<<endl;
    }
    ~MyClass() {cout << "~MyClass()"<<endl;}
    int GetData(void) const
{
        return data_;
    }
    void SetData(int a)
    {
        data_ = a;
    }
    
    MyClass& operator= (const MyClass& a)
    {
        data_ = a.data_;
    //    *pdata_ = *(a.pdata_);
        cout << "operator == &" << endl;
        return *this;
    
    }
    MyClass& operator= (const MyClass&& a)
    {
        data_ = a.data_;
  //      pdata_ = a.pdata_;
        cout << "operator == &&" << endl;
        return *this;
    }
    private:
    int data_ = 0;
    int *pdata_;
};
void TestFunc(const MyClass & param)
{
    cout << "TestFunc()"<<endl;
}
MyClass TestFunc2(void)
{
    cout << "TestFunc2()"<<endl;
    MyClass a;
    return a;
}
MyClass TestFunc3(int param)
{
    MyClass a;
    a.SetData(param);

    return a;
}
int main()
{
    MyClass a;
    a = TestFunc3(20);
    MyClass b(a);
    return 0;
    
}