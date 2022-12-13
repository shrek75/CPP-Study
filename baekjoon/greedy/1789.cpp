//서로다른 자연수 n개의 합 s
// n의 최대개수
/*
s==1 1
s==2 2
s==3 1 2
s==4 1 3
s==5 1 4
s==6 1 2 3
s==7 1 2 4
*/
//n(n+1)/2 
#include <iostream>

int main()
{
    long long int result = 0;
    long long int s = 0;
    scanf("%lld",&s);
    for(long long int i=1;i<=400000;i++)
    {
        if(i*(i+1)/2 > s)
        {
            result = i-1;
            break;
        }
    }
    std::cout << result << std::endl;
    return 0;
    

}