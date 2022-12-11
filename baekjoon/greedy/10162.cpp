#include <iostream>
using namespace std;
int main()
{
    int t =0;
    scanf("%d",&t);

    int a,b,c =0;
    if(t % 10 != 0)
    {
        
        cout << -1 << endl;
        return 0;
    }
    a = t/300;
    t = t%300;
    b = t/60;
    t = t%60;
    c = t/10;

    cout << a <<" "<<b<<" "<<c << endl;
    return 0;

}