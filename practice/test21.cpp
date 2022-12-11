#include <iostream>
#include <functional>
using namespace std;
int main()
{
    cout << less<int>()(10,20) << endl;
    cout << less<int>()(20,20) << endl;
    cout << less<int>()(20,10) << endl;

    cout << not2(less<int>())(10,20) << endl;
    cout << not2(less<int>())(20,20) << endl;
    cout << not2(less<int>())(20,10) << endl;

    
}