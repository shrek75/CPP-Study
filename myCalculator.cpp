#include <cstdio>

int ADD(int x,int y)
{
    return x+y;
}


int main()
{
    char op1 = 0;
    int x=0,y=0;

    int nResult = 0;

    printf("계산식을 입력해주세요:");
    scanf("%d%c%d",&x,&op1,&y);

    switch(op1)
    {
        case '+':
        nResult = x+y;
        break;
        case '-': nResult = x-y;
        break;
        case '*': nResult = x*y;
        break;
        case '/': nResult = x/y;
        break;
    }

    printf("%d",nResult);

    return 0;
}