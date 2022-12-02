#include <stdio.h>
int main()
{
    char a[21] = {0};
    scanf("%s",a);

    for(int i=0; i< sizeof(a);i++)
    {
        if(a[i]!='\0')  printf("\'%c\'\n",a[i]);
    }
    return 0;
}