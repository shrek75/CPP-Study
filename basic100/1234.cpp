#include <iostream>

int main()
{
    int h,b,c,s;
    scanf("%d %d %d %d",&h,&b,&c,&s);
    long double result = 1024 * 1024;
    result = 1.0 /result /8 *h*b*c*s;
    printf("%.1Lf MB",result);
    
    return 0;
}