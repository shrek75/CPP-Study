#include <stdio.h>

int main()
{
    //3 o 4x 5o 6o 7x 8o 9o // 10o 11o 12o 13o 14o// 15o 16o 17o 18o 19o
    int nInput = 0;
    int temp = 0;
    int number = 0;
    int remainderOfFive = 0;
    int quotientOfFive = 0;
    scanf("%d",&nInput);
    temp = nInput;
    
    if(temp >=15)
    {
        quotientOfFive = temp / 5; // 16/5 == 3
        remainderOfFive = temp % 5; // 16%5 == 1
        temp = temp - (quotientOfFive-2)*5; //10-14범위
        number += quotientOfFive -2; // 5kg개수 추가
    }
    if(temp >=10)
    {
        switch(temp)
        {
            case 10:
            number += 2;
            break;
            case 11:
            number += 3;
            break;
            case 12:
            number += 4;
            break;
            case 13:
            number += 3;
            break;
            case 14:
            number += 4;
            break;
        }
    }
    if(temp <10)
    {
        switch(temp)
        {
            case 3:
            number += 1;
            break;
            case 4:
            number = -1;
            break;
            case 5:
            number += 1;
            break;
            case 6:
            number += 2;
            break;
            case 7:
            number = -1;
            break;
            case 8:
            number += 2;
            break;
            case 9:
            number += 3;
            break;
        }
    }
    printf("%d\n",number);
    
    
    
    

    return 0;
}