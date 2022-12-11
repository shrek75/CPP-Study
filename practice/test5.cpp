#include <iostream>
using namespace std;

class MyData
{
    public:
    MyData(){}
    MyData(int x){
        data_ = new int(x);
    }
    ~MyData()
    {
        delete data_;
    }
    MyData(const MyData & param)
    {
        this -> data_ = new int;
        *(this -> data_) = *param.data_;
    }
    
    MyData & operator=(const MyData& rhs)
    {
        *data_ = *(rhs.data_);
        return *this;
    }
    
    int GetData() const
    {
        return *data_;
    }
    private:
    int *data_;
};

int main()
{
    MyData a(5);
    MyData b(a);
    cout << a.GetData() << endl;
    cout << b.GetData() << endl;

    MyData c(5),d(4);
    c =d;
    
    return 0;
}