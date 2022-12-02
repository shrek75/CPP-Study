#include <stdio.h>
int main()
{
    char a[30]={0};
    scanf("%s",a);
    int abc = 0;
    for(int i =0; i<sizeof(a);i++)
    {
        if(a[i]=='\0')   abc = i;
    }
    int point_index = 0;
    for(int i =0; i<abc;i++)
    {
        if(a[i]=='.')   point_index = i;
    }

    for(int i =0; i<point_index; i++)
    printf("%c",a[i]);
    printf("\n");
    for(int i= point_index+1; i<abc;i++)
    printf("%c",a[i]);
    printf("\n");
    return 0;
}