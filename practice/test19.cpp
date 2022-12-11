#include <iostream>

template <typename T>
void Copy(T* dst,T* src,int size=5)
{
    for(int i=0; i<size;i++)
    {
        dst[i] = src[i];
    }
}

class MyType
{
    private:
    int data_;
    public:
    
    MyType(int a=0):data_(a){}
};

int main()
{
    int arr1[5] = {10,20,30,40,50};
    int arr2[5];
    Copy(arr2,arr1,5);

    MyType myArr1[5] = {10,20,30,40,50};
    MyType myArr2[5];
    Copy(myArr2,myArr1,5);

    return 0;
}

