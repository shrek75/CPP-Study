#include <stdio.h>
#include <stdlib.h>
int main()
{
    int nWant = 1;
    int nCount = 0;
    int n,k;
    scanf("%d %d",&n,&k);
    int *price = (int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
    scanf("%d",&price[i]);
    }
    for(int i=n-1;i>=0;i--)
    {
        nCount += k/price[i];
        k %= price[i];
    }

    printf("%d",nCount);


    free(price);
    return 0;
}