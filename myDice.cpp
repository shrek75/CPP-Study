//
//  
//  MyDice
//  yacht게임 모작연습
//  Created by 김태욱 on 2022/11/19.
// 


#include <iostream>
#include <termios.h>
#include <time.h>
#include <stdlib.h> 
#include <unistd.h> //sleep()
#include <sstream>
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
    Aces = 1,
    Deuces = 2,
    Threes,
    Fours,
    Fives,
    Sixes,
    Choice,
    _4ofakind,
    FullHouse,
    S_Straight,
    L_Straight,
    Yacht = 12,
    _35bonus = 13,
    SubTotal = 14,
    Total = 15
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
    gotoxy(3,5);
    printf("방향키와 \'space\'키\n");
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
//기록용 커서
void PrintUserCursor2(int& y)
{
    if (y <= 0)
    {
        y = 0;
    }
    else if (y >= 11)
    {
        y = 11;
    }
    if(y<=5) gotoxy(1, 4 + y);
    else gotoxy(1, 4 + y + 3);
    cout << ">";
    gotoxy(1,1);
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
    if(individual_turn != 0)printf("리롤\n");
    gotoxy(1,25);
    if(individual_turn==0) printf("Q.기록\n");
    else printf("Q.기록 W.리롤\n");
    printf("남은 횟수    >> %d <<\n",individual_turn);
}
//리롤
void PrintPage_3(){
    gotoxy(1,23);
    printf("▁▁▁▁▁▁▁\n");
    printf("▎      ▎ \'<-\'  뒤로가기\n");
    printf("▎      ▎ \'space\' 흔들기\n");
    printf("▎      ▎ \'W\'    던지기!\n");
    printf("▔▔▔▔▔▔▔\n");
}
//흔들기 판 테스트
void PrintPage_3test(){
    gotoxy(1,23);
    printf("▁▁▁▁▁▁▁\n");
    printf("\\      \\ \'<-\'  뒤로가기\n");
    printf("\\      \\ \'space\' 흔들기\n");
    printf("\\      \\ \'W\'    던지기!\n");
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

//주사위 출력형태 버전추가
void PrintDiceModel(int x,int version = 1)
{
    switch(version)
    {
    case 1:
    if(x==1) printf("  ⚀");
    else if(x==2) printf("  ⚁");
    else if(x==3) printf("  ⚂");
    else if(x==4) printf("  ⚃");
    else if(x==5) printf("  ⚄");
    else if(x==6) printf("  ⚅");
    break;

    case 2:
    if(x==1) printf("⚀");
    else if(x==2) printf("⚁");
    else if(x==3) printf("⚂");
    else if(x==4) printf("⚃");
    else if(x==5) printf("⚄");
    else if(x==6) printf("⚅");
    break;

    default:
    break;
    }

    

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
//리롤 목록에 출력하는 리롤주사위
void PrintRerollDice(int *dice,bool* fixdice)
{
    
    for(int i=0;i<5;i++)
    {
        gotoxy(6+i*3,23);
        if(!fixdice[i])  PrintDiceModel(dice[i]);
    }
    gotoxy(19,23); //커서가 마지막주사위 가려서 넣음;
}
//리롤할때 출력하는 리롤 주사위
void PrintRerollDiceGame(int *dice,bool* fixdice)
{
    
    for(int i=0;i<5;i++)
    {
        gotoxy(2+i,24);
        if(!fixdice[i])  PrintDiceModel(dice[i],2);
    }
    gotoxy(2+5,24); //커서가 마지막주사위 가려서 넣음;
}
int ScoreAlgorithm(int *dice, int mode)
{
    int n[6] = {0}; //123456 각개수체크
    int exist[6] = {0}; //123456 존재하면 1 아니면 0
    for(int i=0;i<5;i++)
    {
        n[(dice[i]-1)]++; //개수체크배열에 저장
        exist[(dice[i]-1)] = 1; // 존재체크배열에 1로 존재한다고 저장.
    }


    switch(mode)
    {
        case Aces: return 1 * n[0];
        case Deuces: return 2 * n[1];
        case Threes: return 3 * n[2];
        case Fours: return 4 * n[3];
        case Fives: return 5 * n[4];
        case Sixes: return 6 * n[5];

        case Choice:
        return dice[0]+dice[1]+dice[2]+dice[3]+dice[4];

        case _4ofakind:
        for(int i=0;i<5;i++)
        {   //4개이상
            if(n[i]>=4) return dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
        }
        return 0;

        case FullHouse:
        for(int i=0;i<5;i++)
        {
        //같은거 3개
        if(n[i]==3)
        {
            for(int j=0;j<5; j++)
            {
                if(n[j]==2) return dice[0]+dice[1]+dice[2]+dice[3]+dice[4]; 
            }
        }
        return 0;
        }

        case S_Straight:
    {
    std::ostringstream os;
    for (int i: exist) {
        os << i;
    }
    std::string str(os.str());
    
    if(str.find("1111")!= string::npos)
    {
        return 15;
    }
    return 0;
    }

        case L_Straight:
    {
    std::ostringstream os;
    for (int i: exist) {
        os << i;
    }
    std::string str(os.str());
    
    if(str.find("11111")!= string::npos)
    {
        return 30;
    }
    return 0;
    }

        case Yacht:
        for(int i=0;i<5;i++)
        {   
            if(n[i]==5) return 50;
        }
        return 0;

        default:
        return 0;
    }
}
int YachtAlgorithm(int *dice)
{
    int n[6] = {0};
    int exist[6] = {0};
    for(int i=0;i<5;i++)
    {
        n[(dice[i]-1)]++; //개수체크배열에 저장
        exist[(dice[i]-1)] = 1; // 존재체크배열에 1로 존재한다고 저장.
    }

    //fullhouse/4ofakind/yacht
    for(int i=0;i<5;i++)
    {
        //같은거 3개이상
        if(n[i]>=3)
        {
            //4개이상
            if(n[i]>=4)
            {
                if(n[i]==5) return Yacht; 
                else return _4ofakind; 
            }

            //3개
            for(int j=0;j<5; j++)
            {
                if(n[j]==2) return FullHouse; 
            }
            return 0; //아무것도아님
        }
    }
    //straight
    std::ostringstream os;
    for (int i: exist) {
        os << i;
    }
    std::string str(os.str());
    
    if(str.find("1111")!= string::npos)
    {
        if(str.find("11111")!= string::npos) return L_Straight;
        else return S_Straight;
    }
    
 
    return 0;
            
}


//풀하우스 같은거 출력하는 함수
void PrintAlgorithm(int *dice)
{
    //4개같음    3개같음+2개 연달아4개     연달아5개   5개같음 
    //4ofakind fullhouse s.straight l.straight yacht
    gotoxy(10,24);
    switch(YachtAlgorithm(dice))
    {
        case _4ofakind:
        printf("4 OF A KIND! <<<<<"); break;
        case FullHouse:
        printf("FULL HOUSE! <<<<<"); break;
        case S_Straight:
        printf("SMALL STRAIGHT! <<<<<"); break;
        case L_Straight:
        printf("LARGE STRAIGHT! <<<<<"); break;
        case Yacht:
        printf("!!!YACHT!!! <<<<<"); break;
        default: break;
    }
    

}
void GamePlay()
{
    int nTurn = 1;//턴
    int individual_turn = 3; //3번가능한거
    int myScore[15] = {0}; //점수기록판
    int aIScore[15] = {0};
    int dice[5]; //5개 주사위값
    bool fixdice[5] = {0}; //1고정 0리롤
    int unfix_number = 5; //fix안한개수
    int nPage =3; //보고있는페이지
    int x =0;
    int y = 0;
    int nInput =0;
    for(int i =0;i<5;i++)
    {
        if(!fixdice[i]) RerollDice(dice[i]);
    }

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
            //방향키 위아래로할때마다 기록할수 있는 점수 나와야함
            // 이미기록되어있는 점수가있으면 그게 나와야함(혹은 이미나와있음)
            int nInput = 0;
            PrintPage_1();
            PrintFixDice(dice,fixdice);
            PrintUserCursor2(y);
            nInput =_getch();
            //왼쪽방향키(2페이지가기) 위아래 커서옮기기
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
                            nPage =2;
                            break;
                        }

                        case UP: y--;
                        break;
                        case DOWN: y++;
                        break;
                        default: break;
                    }
                }
                else break;
            }

            //스페이스(결정)
            if(nInput == SPACE)
            {

            }
        }
        break;

        case 2://주사위고정/해제
        {

            if(individual_turn == 0)
            {
                for(int i =0; i<5; i++)
                {
                    fixdice[i] = 1;
                    
                }
                x =0;
                y =0;
            }
            int nInput =0;
            PrintPage_2(individual_turn);
            PrintFixDice(dice,fixdice);
            PrintRerollDice(dice,fixdice);
            PrintAlgorithm(dice);
            PrintUserCursor(x,y);
                  //q기록 w리롤  스페 방향키
            //턴 0이면 리롤못하게해야함 o
            //턴 0이면 리롤인 주사위 다 고정으로 이동시키고 다시화면 출력후 // 다했음
            // 주사위 결과(풀하우스) 출력후 ( 리롤칸에 하면될듯) q키빼고 다른키는 안먹히게 해야함(이건햇음)
            nInput =_getch();
            switch(nInput)
            {
                case q:
                case Q:
                y=0;
                nPage = 1;
                break;

                case w:
                case W:
                if(individual_turn == 0)    break;
                nPage = 3;
                break;

                case SPACE:
                if(individual_turn == 0)    break;

                if(y==0){
                    fixdice[x] = 0;
                }
                else if(y==1){
                    fixdice[x] = 1;
                }
                break;

                case 27:
                {
                    if(individual_turn == 0)    break;
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
            PrintRerollDiceGame(dice,fixdice);
            gotoxy(2,25);
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
            //w 던지기
            if(nInput == w || nInput == W)
            {
            for(int i =0;i<5;i++)
            {
                if(!fixdice[i]) RerollDice(dice[i]);
            }
            individual_turn --;

            //출력대기모션
            PrintPage_3test();
            gotoxy(2,24); printf("★☆★☆★\n");
            sleep(1);
            PrintPage_3();
            gotoxy(2,24); printf("☆★☆★☆\n");
            sleep(1);
            PrintPage_3test();
            gotoxy(2,24); printf("★☆★☆★\n");
            sleep(1);
            PrintPage_3();
            PrintRerollDiceGame(dice,fixdice);
            gotoxy(2,26); printf("!   !\n");
            sleep(2);

            nPage =2;
            break;
            }

            //스페이스 (흔들기) ( 미완성)
            if(nInput == SPACE)
            {
            for(int i =0;i<5;i++)
            {
                if(!fixdice[i]) RerollDice(dice[i]);
            }
            
            //흔들기 효과 넣으면 좋을듯 그래서 넣었스비다
            PrintPage_3test();
            gotoxy(2,24); printf("!!!!!\n");
            sleep(1);

            nPage =3;
            break;
            }
            
            

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
