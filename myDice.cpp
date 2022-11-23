//
//  main.cpp
//  MyDice
//
//  Created by 김태욱 on 2022/11/19.
// test

/*
    printf("▁▁▁▁▁▁▁\n");
    printf("▎      ▎\n");
    printf("▎      ▎\n");
    printf("▎      ▎\n");
    printf("▔▔▔▔▔▔▔\n");
*/

#include <iostream>
#include <termios.h>
#include <time.h>
#include <stdlib.h> 
#include <unistd.h> //sleep()
#define clean() printf("\033[H\033[J")
#define putchxy(x,y,c) {gotoxy(x,y); putchar(c);}

using namespace std;

enum MAINMENU{
    EXIT = 0,
    START = 1
};

//mac os에서 방향키다름 그리고 27 , 91 후에 나옴 방향키
enum KEYBOARD{
    ESC = 27,
    SPACE = 32,
    UP = 65,
    DOWN = 66,
    RIGHT = 67,
    LEFT = 68,
    Q = 81,
    q = 113,
    W = 87,
    w = 119
};

enum SCOREBOARD{
    Aces = 0,
    Deuces = 1,
    Threes,
    Fours,
    Fives,
    Sixes,
    Choice,
    _4ofakind,
    FullHouse,
    S_Straight,
    L_Straight,
    Yacht = 11,
    SubTotal = 12,
    Total = 13
};



// ANSI escape code 버전 //ncurses는 못쓰겠음
void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

//https://yunsu3042.github.io/devlog/2018/02/17/mac_%EC%BD%98%EC%86%94%EA%B2%8C%EC%9E%84_%EC%86%8C%EC%BD%94%EB%B0%98/
int _getch(void)
{
    int ch;
    struct termios buf;
    struct termios save;
    
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

void PrintMainMenu()
{
    gotoxy(3,1);
    printf("Start\n");
    gotoxy(3,2);
    printf("Exit\n");
}
void PrintUserCursor(int& y)
{
    if (y <= 0)
    {
        y = 0;
    }
    else if (y >= 1)
    {
        y = 1;
    }
 
    gotoxy(1, 1 + y);
    cout << ">";
}
void PrintUserCursor(int& x,int& y)
{
    //xy보정
    if (x<=0) x= 0;
    else if (x>=4) x=4;
    if (y <= 0) y = 0;
    else if (y >= 1)y=1;
 
    gotoxy(6 + 3*x, 22 + y);
    cout << ">";
}
void PrintGameScoreBoard()
{
    gotoxy(4,1); printf("Turn"); gotoxy(14,1); printf("Me"); gotoxy(20,1); printf("AI");
    gotoxy(5,2); printf("/ 12");
    gotoxy(2,4); printf("Aces");
    gotoxy(2,5); printf("Deuces");
    gotoxy(2,6); printf("Threes");
    gotoxy(2,7); printf("Fours");
    gotoxy(2,8); printf("Fives");
    gotoxy(2,9); printf("Sixes");
    gotoxy(2,10); printf("SubTotal"); gotoxy(15,10); printf("/63"); gotoxy(21,10); printf("/63");
    gotoxy(2,11); printf("+35 Bonus");
    gotoxy(2,13); printf("Choice");
    gotoxy(2,14); printf("4 of a kind");
    gotoxy(2,15); printf("Full House");
    gotoxy(2,16); printf("S.Straight");
    gotoxy(2,17); printf("L.Straight");
    gotoxy(2,18); printf("Yacht");
    gotoxy(1,19); printf("-----------------------");
    gotoxy(2,20); printf("Total");
    gotoxy(1,21); printf("***********************");
    gotoxy(1,22); printf("고정");


}
//기록
void PrintPage_1(){}
//주사위고정/해제
void PrintPage_2(int individual_turn){
    gotoxy(1,23);
    printf("리롤\n");
    gotoxy(6,24);
    if(individual_turn==0) printf("Q기록\n");
    else printf("Q기록 W리롤\n");
    printf("남은 횟수: %d\n",individual_turn);
}
//리롤
void PrintPage_3(){
    gotoxy(1,23);
    printf("▁▁▁▁▁▁▁\n");
    printf("▎      ▎\n");
    printf("▎      ▎\n");
    printf("▎      ▎\n");
    printf("▔▔▔▔▔▔▔\n");
}

MAINMENU MainMenu()
{
    int y = 0;
    int nInput = 0;

    while(true)
    {
    clean();
    PrintMainMenu();
    PrintUserCursor(y);
    
    nInput = _getch();

    if(nInput == SPACE)
    switch(y)
    {
            case 0: return START;
            case 1: return EXIT;
    }
    if(nInput == 27)
    {
        nInput = _getch();
        if(nInput == 91)
        {
            nInput = _getch();
            switch(nInput)
            {
                case UP:y--;
                break;

                case DOWN:y++;
                break;
                
                default: break;
            }
        }
        else break;
    }
    
    }
    return EXIT;
}

void RerollDice(int &x_1)
{
    x_1 = rand()%6+1;
}

void PrintDiceModel(int x)
{
    if(x==1) printf("  ⚀");
    else if(x==2) printf("  ⚁");
    else if(x==3) printf("  ⚂");
    else if(x==4) printf("  ⚃");
    else if(x==5) printf("  ⚄");
    else if(x==6) printf("  ⚅");
}
void PrintDiceModel(int *x)//5개출력
{
    for(int i=0;i<5;i++)
    {
        //출력위치
        gotoxy(i+2,24);
        if(x[i]==1) printf("⚀");
    else if(x[i]==2) printf("⚁");
    else if(x[i]==3) printf("⚂");
    else if(x[i]==4) printf("⚃");
    else if(x[i]==5) printf("⚄");
    else if(x[i]==6) printf("⚅");
    }
    gotoxy(7,24);
}
void PrintFixDice(int *dice,bool* fixdice)
{

    for(int i=0;i<5;i++)
    {
        if(fixdice[i])
        { 
            gotoxy(6+i*3,22);
            PrintDiceModel(dice[i]);
        }

    }
}
void PrintRerollDice(int *dice,bool* fixdice)
{
    gotoxy(6,23);
    for(int i=0;i<5;i++)
    {
        gotoxy(6+i*3,23);
        if(!fixdice[i])  PrintDiceModel(dice[i]);
    }
}
void GamePlay()
{
    int nTurn = 1;//턴
    int individual_turn = 3; //3번가능한거
    int myScore[14] = {0}; //점수기록판
    int aIScore[14] = {0};
    int dice[5]; //5개 주사위값
    bool fixdice[5] = {0}; //1고정 0리롤
    int unfix_number = 5; //fix안한개수
    int nPage =3; //보고있는페이지
    int x =0;
    int y = 0;
    int nInput =0;

    while(true){
    clean();
    PrintGameScoreBoard();
    switch(nPage)
    {
        case 1://기록
        {
            //기록하면  변수초기화해줘야함
            //그리고 상대턴으로 넘어가야함

            //12턴 막턴끝나면 겜끝나야함
            int nInput = 0;
            PrintPage_1();
            
        }
        break;
        case 2://주사위고정/해제
        {
            int nInput =0;
            PrintPage_2(individual_turn);
            PrintFixDice(dice,fixdice);
            PrintRerollDice(dice,fixdice);
            PrintUserCursor(x,y);
                  //q기록 w리롤  스페 방향키
            //턴 0이면 리롤못하게해야함
            nInput =_getch();
            switch(nInput)
            {
                case q:
                case Q:
                nPage = 1;
                break;

                case w:
                case W:
                if(individual_turn == 0)    break;
                nPage = 3;
                break;

                case SPACE:
                if(y==0){
                    fixdice[x] = 0;
                }
                else if(y==1){
                    fixdice[x] = 1;
                }
                break;

                case 27:
                {
                    nInput = _getch();
                    if(nInput == 91)
                    {
                        nInput = _getch();
                        switch(nInput)
                        {
                            case UP:
                            y--;
                            break;
                            case DOWN:
                            y++;
                            break;
                            case RIGHT:
                            x++;
                            break;
                            case LEFT:
                            x--;
                            break;
                            default: break;
                        }
                    } 
                }


                break;
                default: break;
            }


        }
        break;
        case 3://리롤
        {
            int nInput =0;
            PrintPage_3();
            //고정된 다이스 프린트함수
            PrintFixDice(dice,fixdice);
            nInput =_getch();
            //왼쪽방향키(2페이지가기)
            if(nInput == 27)
            {
                nInput = _getch();
                if(nInput == 91)
                {
                    nInput = _getch();
                    switch(nInput)
                    {
                        case LEFT:
                        {
                            //개인 첫턴이면 주사위 던지고시작
                            if(individual_turn !=3)   nPage =2;
                            break;
                        }
                        default: break;
                    }
                }
                else break;
            }
            //스페이스
            if(nInput == SPACE)
            {
            for(int i =0;i<5;i++)
            {
                if(!fixdice[i]) RerollDice(dice[i]);
            }
            individual_turn --;
            PrintDiceModel(dice);
            //풀하우스인지 뭔지 이런거 프린트 해주는 함수 넣어야함
            
            //주사위보여주고 3초대기
            sleep(3);

            nPage =2;
            break;
            }
            
            //흔들기기능(없음)

        }
        break;
    }
    
    }

}

int main(void) {
    int nInput;
    srand((unsigned int)time(NULL));

    while(true)
    {
        nInput = MainMenu();
        switch(nInput)
        {
            case START:
            {
                    clean();
                    GamePlay();
            }
            break;
            case EXIT:
            return 0;
        }
    }


    return 0;
}
