#include <stdio.h>
#include <stdlib.h>
int main()
{
    int nStartTime = 0;
    int nExitTime = 0;
    int nCount =0;
    int min = 2147483647;
    int minIndex = 0;
    int n=0;
    scanf("%d",&n);
    int *pszBuffer = (int *)malloc(sizeof(int)*(n*2));
    for(int i=0;i<n;i++)
    scanf("%d %d",&pszBuffer[2*i],&pszBuffer[2*i+1]);
    
    //처음엔 가장 빨리 끝나는거 ex 4시라면
    //그다음은 시작시간이 4이상이고 끝나는시간이 가장빨리끝나는거.
    // 선택한게 시작시간 == 종료시간 이면 또 똑같은회의가 있는지 살펴봐야함 . 똑같은게 3개면 +3개해야해서
    // 무한반복
    while(true)
    {
        //변수초기화
    min = 2147483647;
    minIndex = 0;


    //시작시간 == 종료시각 있는지, 있다면 몇개있는지 살펴보고 그만큼 회의카운트 추가
    for(int i=0;i<n;i++)
    {
    if(nExitTime == pszBuffer[2*i] && nExitTime == pszBuffer[2*i +1])
    {
        nCount ++;
    }
    }
    for(int i=0;i<n;i++)
    {   //시작하는시각이 이전회의 종료시각이상이라면
        if(pszBuffer[2*i]>=nExitTime)
        {
            //시작 != 종료 라면
            if(pszBuffer[2*i] != pszBuffer[2*i+1])
            {
              // 끝나는시각이 가장 빠른거 찾기.
            if(min>pszBuffer[2*i+1])
            { 
                min = pszBuffer[2*i+1];
                minIndex = i;
            } 
            }
        }
    }
    //최소시각이 안바뀌었다면
    if(min == 2147483647) break;
    nStartTime = pszBuffer[2*minIndex];
    nExitTime = pszBuffer[2*minIndex+1];
    nCount++;

    }
    printf("%d\n",nCount);
    free(pszBuffer);
    return 0;
}