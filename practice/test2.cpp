#include <iostream>

using namespace std;
class MyClass
    {
        public:
        MyClass():data_(10){
            std::cout<<"MyClass()"<<std::endl;
            count_++;
        }
        ~MyClass(){
            std::cout<<"~MyClass()"<<std::endl;
        }
        static int GetData()
        {
            return count_;
        }
        static int asb_;
        int asdf;
        void TestFunc()
        {
            data_ = 123;
        }
        private:
        int data_;
        static int count_ ;
    };
    //MyClass의 정적멤버변수 정의!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int MyClass::count_ = 0;
    int MyClass::asb_ = 0;
int main()
{
    MyClass::asb_ = 0;
   // MyClass::b_ = 10;

   MyClass a;
   cout<<  a.GetData() << endl;
    cout<<  MyClass::GetData() << endl;

    const MyClass & mydata = a;
    mydata.GetData();
   // MyClass a;
   // MyClass::GetData();
   // std::cout<< a.GetData() << std::endl;
    return 0;
}