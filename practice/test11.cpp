#include <iostream>
using namespace std;


class Point
{
    private:
    int x_;
    int y_;
    public:
    Point(int x,int y):x_(x),y_(y){}
    void Print() const
    {
        cout << x_ << "," << y_ << endl;
    }
    Point & operator ++()
    {
        x_ ++;
        y_ ++;
        return *this;
    }
    //멤버함수를 이용한 연산자 오버로딩
    const Point operator ++(int)
    {
        Point pt(this->x_,this->y_);
        x_ ++;
        y_ ++;
        return pt;
    }
    int GetX(void) const {return x_;}
    int GetY(void) const {return y_;}
};
//전역함수를 이용한 연산자 오버로딩
const Point operator - (const Point& left, const Point& right)
{
    Point pt(left.GetX() - right.GetX(),left.GetY() - right.GetY());
    return pt;
    
}

int main()
{
    Point a(4,5);
    
    a++.Print();

    
    (++a).Print();

    Point b(3,4);
    Point c(1,1);
    (b-c).Print();
}