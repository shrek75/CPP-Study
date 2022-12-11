#include <stdio.h>
int main()
{
    int a, r , n;
    scanf("%d %d %d",&a,&r,&n);
    long long int result = 1;
    for(int i=0; i<n-1 ; i++)
    {
        result *= r;
    }
    result *=a;
    printf("%lld",result);
    return 0;
}