#include <iostream>
using namespace std;

class Point
{
    private:
    int x_;
    int y_;
public:
    Point():x_(0),y_(0){}
    Point(int x,int y):x_(x),y_(y){}
    void Print() const { cout << x_ << ","<<y_<<endl;}
    const Point operator+(const Point& arg)const
    {
        Point pt;
        pt.x_ = this -> x_ + arg.x_;
        pt.y_ = this->y_ + arg.y_;
        return pt;
    }
};
int main()
{
    Point a;
    Point b;
    Point c= a+b;
    Point d = a.operator+(b);
    return 0;
}