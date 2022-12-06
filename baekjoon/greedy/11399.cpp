#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n= 0;
    scanf("%d",&n);
    int *pN = (int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pN[i]);
    }
    int nMinIndex = -1;
    int nMin = 1000;
    int nTotal = 0;
    int nTemp = 0;
    int nTotalofTotal = 0;

    for(int i=0;i<n;i++)
    {
        nMin = 1000;
        nMinIndex = i;

        for(int j=i;j<n;j++)
        {
        if(nMin>pN[j])
        {
            nMin = pN[j]; //최소값 저장
            nMinIndex = j; //최솟값이 있는 인덱스 저장
        }     
        }
        nTotal += nMin; 
        nTotalofTotal += nTotal;
        nTemp = pN[i];
        pN[i] = pN[nMinIndex];
        pN[nMinIndex] = nTemp;
    }
    printf("%d\n",nTotalofTotal);

    free(pN);
    return 0;
}