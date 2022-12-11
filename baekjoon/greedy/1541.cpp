#include <iostream>

// -50 + 30 -20 -40 + 50 +30 - 10 
// -가 나오면 다음이 - 아닐경우에 - 전까지만 괄호.
int ChangeCharToInt(char * buffer, int size)
{
    int result = 0;
    int temp = 0;
    for(int i=0; i<size; i++)
    {
        temp =0;
        temp = buffer[i] - '0';
        for(int j=i; j<size-1; j++) 
        {
            temp *=10;
        }
        result += temp;
    }
    for(int i=0; i<size+1; i++)
    {
        buffer[i] = '\0';
    }
    return result;
}
int main()
{
    int sign = 1;
    char input [100]; //전체배열
    int size = 0; //전체배열 사이즈
    char temp[6] = {'\0'}; //임시배열
    int a=0; //임시배열사이즈
    int result = 0;
    int total =0;
    gets(input);
    for(int i=0;i<100;i++)
    {
        if(input[i]== '\0')
        {
            size = i;
            break;
        }
    }
    for (int i=0; i<size ; i++)
    {
        if(input[i] == '-')
        {
            result = ChangeCharToInt(temp,a);
            result *= sign;
            total += result;
            sign = -1;
            a=0;
        }
       // 50 -40 +30
        else if(input[i] == '+')
        {
            result = ChangeCharToInt(temp,a);
            result *= sign;
            total += result;
            if(sign == -1)sign = -1; //괄호치기 알고리즘
            a=0;
            

        }
        else
        {
            temp[a++] = input[i];
        }
    }
    result = ChangeCharToInt(temp,a);
    result *= sign;
    total += result;

    printf("%d\n",total);
}