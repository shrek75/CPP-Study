#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Array
{
    T *buf_;
    int size_;
    int capacity_;

    public:
    explicit Array(int cap = 100):buf_(0),size_(0),capacity_(cap)
    {
        buf_ = new T[capacity_];
    }
    ~Array(){delete[] buf_;}
    
    void Add(T data)
    {
        buf_[size_++] = data;
    }
    T operator[](int idx) const
    {
        return buf_[idx];
    }
    int GetSize() const
    {
        return size_;
    }
};

int main ()
{
    Array<int> arr;
    arr.Add(10);
    arr.Add(20);
    arr.Add(30);
    Array<char *> arr2;
    arr2.Add("Hello");
    arr2.Add("Mother");
    arr2.Add("Fother");
    Array<string> arr3;
    arr3.Add("Hello");
    arr3.Add("Mother");
    arr3.Add("Fother");
    for(int i=0;i<arr3.GetSize();i++)
    {
        cout << arr3[i] <<endl;
    }
    return 0;
}