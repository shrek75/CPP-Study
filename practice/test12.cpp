#include <iostream>
using namespace std;

class Point
{
    int x_;
    int y_;

public:
    Point(int x,int y){x_ = x; y_ =y;}

    void Print() const { cout << x_ << ',' << y_ << endl; }

    int operator[](int idx)
    {
        if(idx == 0)    return x_;
        else if(idx == 1) return y_;
        else throw "이럴 수는 없는거야!";
    }
};

int main()
{
    Point pt(1,2);

    pt.Print();

    cout << pt[0] << ',' << pt[1] << ',' << endl;
}