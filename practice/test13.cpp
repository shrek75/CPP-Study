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
    operator int() const
    {
        cout << "operator(int)" << endl;
        return x_ + y_;
    }

};
class PointPtr
{
    Point * p_;

    public:
    PointPtr(Point * ptr):p_(ptr){
        cout << "PointPtr()" << endl;
    }
    ~PointPtr(){
        cout << "~PointPtr()" << endl;
        delete p_;
    }
    Point * operator -> () const {return p_;}
    Point & operator*() const {return *p_;}
};
int main()
{
    PointPtr p1 = new Point(2,3);
    PointPtr p2 = new Point(5,5);
    
    p1->Print();
    (*p2).Print();
    int a = *p2;
    cout << a << endl;
    return 0;
}