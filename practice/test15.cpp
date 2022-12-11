#include <iostream>
using namespace std;
class Equal
{
    public:
    bool operator() (int x, int y)
    {
        return x == y;
    }
};
int main()
{
    Equal cmp;
    if(Equal()(10,20))
    cout << "같다!" << endl;
    if(cmp(10,20))
    cout << "같다!" << endl;
    else
    cout << "다르다!" << endl;
    return 0;
}