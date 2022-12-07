//
//
//  MyDice.cpp
//  yacht게임 모작연습(vs AI완성!)
//  yacht copy practice

//  Created by shrek75(freshine0@gmail.com)김태욱 on 2022/11/19.

//               2022/12/06
//               - aI가 스트레이트 너무하려고함 수정해야함. 그리고 너무멍청함. 그리고 버그가있는지는 나도 모르겠음.
//               - vs aI 고수만들기 ( 고급알고리즘 구현) 
//               - 이름 로그인 넣어서 점수 기록하기
//               - Windows에서도 되게하기 (몇개만 수정하면되는데 귀찮네...)


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
    START = 1, //로컬2p
    START_AI =2,
    START_AI_REMAKE =3
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

enum SCOREBOARD : int{
    TURN = 0,
    Aces = 1,
    Deuces = 2,
    Threes =3,
    Fours =4,
    Fives =5,
    Sixes=6,
    Choice=7,
    _4ofakind=8,
    FullHouse=9,
    S_Straight=10,
    L_Straight=11,
    Yacht = 12,
    _35bonus = 13,
    SubTotal = 14,
    Total = 15,
    //기록여부
    OX_Aces = 16,
    OX_Deuces = 17,
    OX_Threes=18,
    OX_Fours=19,
    OX_Fives=20,
    OX_Sixes=21,
    OX_Choice=22,
    OX__4ofakind=23,
    OX_FullHouse=24,
    OX_S_Straight=25,
    OX_L_Straight=26,
    OX_Yacht=27
    
};



// ANSI escape code 버전 //ncurses는 못쓰겠음
void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

//https://yunsu3042.github.io/devlog/2018/02/17
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
    printf(" 로컬2P\n");
    gotoxy(3,4);
    printf("Exit\n");
    gotoxy(3,2);
    printf("vs AI(초급)\n");
    gotoxy(3,3);
    printf("vs AI(중급)(미완성)\n");
    gotoxy(3,7);
    printf("방향키와 \'space\'키\n");
}
//초기화면
void PrintUserCursor(int& y)
{
    if (y <= 0)
    {
        y = 0;
    }
    else if (y >= 3)
    {
        y = 3;
    }
 
    gotoxy(1, 1 + y);
    cout << ">";
}
//주사위 고를때 커서
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
void PrintGameScoreBoard(int *score_p1,int *score_p2)
{
    gotoxy(4,1); printf("Turn"); gotoxy(14,1); printf("P1"); gotoxy(20,1); printf("P2");
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
    //점수출력1
    for(int i =0; i<12; i++)
    {
        //기록이 되어있다면
        if(score_p1[i+1+15]!=0)
        {
            if(i<=5) gotoxy(14,i+4);
            else gotoxy(14,i+4+3);
            printf("%d",score_p1[i+1]);
        }
        if(score_p2[i+1+15]!=0)
        {
            if(i<=5) gotoxy(20,i+4);
            else gotoxy(20,i+4+3);
            printf("%d",score_p2[i+1]);
        }
    }
    //점수출력2 서브토탈 토탈
    gotoxy(13,10); printf("%d",score_p1[SubTotal]);
    gotoxy(19,10); printf("%d",score_p2[SubTotal]);
    gotoxy(14,20); printf("%d",score_p1[Total]);
    gotoxy(20,20); printf("%d",score_p2[Total]);
    // 점수출력3 보너스
    if(score_p1[_35bonus]!= 0)  {
    gotoxy(14,11); 
    printf("%d",score_p1[_35bonus]);}
    if(score_p2[_35bonus]!= 0)  {
    gotoxy(20,11); 
    printf("%d",score_p2[_35bonus]);}

    //누구차례인지 표시
    if(score_p1[TURN]!=score_p2[TURN])
    {
        gotoxy(13,1);printf(">");
        gotoxy(16,1);printf("<");
    }
    else{
        gotoxy(19,1);printf(">");
        gotoxy(22,1);printf("<");
    }
    //턴표시
    gotoxy(2,2);
    printf("%02d",score_p1[TURN]);

    gotoxy(1,1);
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
            case 1: return START_AI;
            case 2: return START_AI_REMAKE;
            case 3: return EXIT;
            default: return EXIT;
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
void RerollDiceAll(int *dice,bool *fixdice)
{
    for(int i=0; i<5; i++)
    {
        if(!fixdice[i]) RerollDice(dice[i]);
    }
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
//리롤할때 게임판에 출력하는 리롤 주사위
void PrintRerollDiceGame(int *dice,bool* fixdice)
{
    
    for(int i=0;i<5;i++)
    {
        gotoxy(2+i,24);
        if(!fixdice[i])  PrintDiceModel(dice[i],2);
    }
    gotoxy(2+5,24); //커서가 마지막주사위 가려서 넣음;
}

//리롤출력대기모션
void PrintRerollDiceWaiting(int *dice,bool* fixdice)
{
                //리롤출력대기모션
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
}
//mode : 어떤 항목의 점수 반환할지
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
        for(int i=0;i<6;i++)
        {   //4개이상
            if(n[i]>=4) return dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
        }
        return 0;

        case FullHouse:
        for(int i=0;i<6;i++)
        {
        //같은거 3개
        if(n[i]==3)
        {
            for(int j=0;j<6; j++)
            {
                if(n[j]==2) return dice[0]+dice[1]+dice[2]+dice[3]+dice[4]; 
            }
        }
        }
        return 0;
        

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
        for(int i=0;i<6;i++)
        {   
            if(n[i]==5) return 50;
        }
        return 0;

        default:
        return 0;
    }
}
// 풀하우스 이런거 알려주는거
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
    for(int i=0;i<6;i++)
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
            for(int j=0;j<6; j++)
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
//기록용 임시점수 출력함수 // printusercursor함수 다음에 호출되어야함
void PrintReportTempScore(int *dice,int y,int whoseturn)
{
    int x =14;
    if(whoseturn == -1) x = 20;
    if(y<=5) gotoxy(x,y+4);
    else if(y>=6) gotoxy(x,y+4+3);
    printf("%d ",ScoreAlgorithm(dice,y+1));
}
//원하는수만 고정 나머지 다 고정푸는 함수
void FixWantNumber(int* dice,bool* fixdice,int want)
{
    for(int i=0;i<5;i++)
    {
        if(dice[i]== want) fixdice[i] = 1;
        else fixdice[i] = 0;
    }
}
//원하는 수 하나 고정시킬건데 예를들어 원하는수가 1일때 1이 여러개면 그중에 한개만 고정시킴(이미 고정이였는이 아닌지는 상관안함)
void FixWantNumberJustOne(int *dice,bool *fixdice,int want)
{
    for(int i =0 ;i<5;i++)
    {
        if(dice[i]==want)
        {
            fixdice[i] = 1;
            break;
        }
    }
}
//배열 총합
int TheTotalOfNumber(int *szBuffer,int buffersize=5)
{
    int nTotal = 0;
    for(int i=0; i<buffersize;i++)
    {
        nTotal += szBuffer[i];
    }
    return nTotal;
}
//배열에서 원하는 수의 '갯수'를 반환하는 함수
int TheNumberOfNumbers(int* szbuffer,int want,int buffersize =5)
{
    int n = 0;
    for(int i=0; i<buffersize; i++)
    {
        if(szbuffer[i] == want) n++;
    }
    return n;
       
}
//배열에서 가장많은 '수'를 반환하는함수 //모드0 : 개수가같으면 더 큰수반환 모드1: 작은수반환
int TheMostNumber(int * szbuffer,int buffersize=5,int mode = 0)
{
    int temp = 0;
    int max = 0; //가장많은숫자 인덱스는 -1하면됨
    int n[6] = {0};
    for(int i=0; i<buffersize;i++)
    {
        n[szbuffer[i]-1]++;
    }

    //젤 많은거 기록해두기
    for(int i=0; i<6;i++)
    {
        if(temp<=n[i])
        {
            temp = n[i];
            max = i+1;
        }
    }

    for(int i=0; i<buffersize;i++)
    {
        // 젤많은게 중복될수 있으니까 한번더 반복문
        if(n[max-1]==n[i])
        {
            //같은거발견했다면
            if((max-1)!=i)
            {
                if(mode ==0) return max;
                if(mode ==1) return i+1;
            }
            else if((max-1)==i) return max;
        }
    }
    return 0;
}
//배열에서 가장큰수반환
int TheBiggestNumber(int *szBuffer,int nSize = 5)
{
    int nMax = 0;
    for(int i =0; i<nSize; i++)
    {
        if(szBuffer[i]>nMax) nMax = szBuffer[i];
    }

    return nMax;
}
int AI_DecideAlgorithmMode(int * aIscore)
{
//mode 1: 대충설명하면 아랫판보다 윗판이 우선순위 높음. (보너스점수 위함)(왠만하면 항상 mode1)
//mode 2: choice랑 straight빼고 다했을때 mode2로 함.

//임시로 mode1 고정해두겠음. mode2 미완성
return 1;
/*
    if(aIscore[OX_Aces] == 0) return 1;
    if(aIscore[OX_Deuces] == 0) return 1;
    if(aIscore[OX_Threes] == 0) return 1;
    if(aIscore[OX_Fours] == 0) return 1;
    if(aIscore[OX_Fives] == 0) return 1;
    if(aIscore[OX_Sixes] == 0) return 1;
    if(aIscore[OX__4ofakind] == 0) return 1;
    if(aIscore[OX_Yacht] == 0) return 1;
    if(aIscore[OX_FullHouse] == 0) return 1;
    return 2;
*/
}
//각보고있는거 반환 기록해야하면 ox 각보고있는거면 1-12
int AI_DecideAlgorithm(int * dice,bool * fixdice,int individual_turn,int * aIscore)
{
//알고리즘 정하기(상황판단하기) 
//알아야할거 : 주사위던지기횟수,턴, 내가기록한거, 상대점수(이건너무어려울듯)
//반환해야할거 : 각보고있는거(ex. s.straight)
//원하는거 떳으면 각보고잇는거에 기록해야할위치 저장
//이미 기록한거는 노리면 안됨!!!!!!!!!!!!!!!!!!!!!

//mode 1: 대충설명하면 아랫판보다 윗판이 우선순위 높음. (보너스점수 위함)(왠만하면 항상 mode1)
//mode 2: choice랑 straight빼고 다했을때 mode2로 함.
int mode = AI_DecideAlgorithmMode(aIscore);
switch(mode)
{
case 1: //일반알고리즘 시작
{
//0순위. 뭐라도 떴다면?
int wow = YachtAlgorithm(dice);
if(wow >= _4ofakind && wow <= Yacht)
{
    //0-1. 턴이 안남았다면
    if(individual_turn == 0)
    {
        switch(wow)
        {
            case Yacht:
            {//기록안했으면 하고 했으면 4ofkind로 넘어감
                if(aIscore[OX_Yacht]==0) return OX_Yacht;
            }
            case _4ofakind:
            {
                //4ofkind 기록했다면
                if(aIscore[OX__4ofakind]==1) 
                {
                    int want = TheMostNumber(dice);
                    if(aIscore[Total+want]==1)break;//윗판의 그숫자도 기록했다면 넘어가
                    else return Total+want; //아니라면 기록해라
                }
                //4ofkind 기록안했다면
                else
                {
                    int want = TheMostNumber(dice);
                    if(want == 1 || want == 2) //1이나 2로 4ofkind라면
                    {
                        if(aIscore[Total+want]==1) //윗판의 그숫자는 기록했다면
                        break;
                        else return Total+want;//아니라면 기록해라
                    }
                    //3-6으로 4ofakind라면
                    else return OX__4ofakind;
                }
            }break;

            case FullHouse:
            {
                if(aIscore[OX_FullHouse]==1) break;
                else return OX_FullHouse;
            }break;

            //기록 안하면 s_straight로 넘어감
            case L_Straight:
            {
                if(aIscore[OX_L_Straight]==0) return OX_L_Straight;
            }
            case S_Straight:
            {
                if(aIscore[OX_S_Straight]==1) break;
                else return OX_S_Straight;
            }break;


            default: break;
        }
    }

    //0-2. 턴이 남았다면
    else if(individual_turn>0)
    {
        switch(wow)
        {
            //return 안하면 4ofakind로 넘어감
            case Yacht:
            {
                if(aIscore[OX_Yacht]==1);//4ofakind로 넘어감
                else return OX_Yacht;
            }
            case _4ofakind:
            {
                //yacht 기록했다면
                if(aIscore[OX_Yacht]==1) 
                {
                    //4ofkind기록했다면
                    if(aIscore[OX__4ofakind]==1)
                    {
                        int want = TheMostNumber(dice);
                        if(aIscore[Total+want]==1)//윗판 그숫자도 기록했다면
                        break;
                        else return want;
                    }
                    //4ofkind 기록안했다면
                    else
                    {
                    int want = TheMostNumber(dice);
                    if(want == 1 || want == 2) //1이나 2로 4ofkind라면
                    {
                        if(aIscore[Total+want]==1) //윗판의 그숫자는 기록했다면
                        break;
                        else return want;//아니라면 
                    }
                    //3-6으로 4ofakind라면
                    else return _4ofakind;
                    }
                }
                //yacht 기록안했다면
                else
                {
                    return Yacht;
                }
            }break;

            case FullHouse:
            {
                if(aIscore[OX_FullHouse]==1) break;
                else return OX_FullHouse; //바로기록
            }break;

            //return 안하면 s_straight로 넘어감
            case L_Straight:
            {
                if(aIscore[OX_L_Straight]==1)
                {
                    if(aIscore[OX_S_Straight]==0) return OX_S_Straight;
                    else break;
                }
                else return OX_L_Straight;
            }
            case S_Straight:
            {
                if(aIscore[OX_S_Straight]==1)
                {
                    if(aIscore[OX_L_Straight]==0)
                    return L_Straight; 
                    else break;
                }
                else return S_Straight;
            }break;

            default: break;
        }
    }
}

//암것도 안뜨고 or 떴는데 이미 기록된곳이어서 return을 못했으면
{

if(individual_turn == 0)
//암것도 안뜨고(ex fullhouse), 턴이 없다면!!!
/*
아무것도 아니고 같은거 3개면 그거 그냥 박기
근데 그거 썼으면 우선순위대로 박아야지..

아무것도아니고 같은거 2개이하면 우선순위가
젤위에서 아래로가됨.(1에서6) 아니면 턴 >=7일때 걍yacht에 박기
아니면 choice안썼을때 합좀높으면 거기박기 (21이상)
위에거 다썼으면 남는거 박아야지머..
*/
{
    int want = TheMostNumber(dice);
    int nwant = TheNumberOfNumbers(dice,want);

    //같은거 3개이상
    if(nwant >= 3)
    {   //3개이상인거 안썼다면
        if(aIscore[Total+want]==0)  return Total+want;
    }
    //같은거 2개이하 or 3개이상 썼으면 걍 대충박아라
    {   //choice 안썼다면
         if(aIscore[OX_Choice]==0)
         {
            //총합 21이상
            if(TheTotalOfNumber(dice)>=21)  return OX_Choice;
         }
         //yacht 안썼다면
         if(aIscore[OX_Yacht]==0)
         {
             //턴7이상
            if(aIscore[TURN]>=7)  return OX_Yacht;
         }
         //순서대로박기
         for(int i=1; i<=12 ; i++)
         {
            if(aIscore[Total+i]==0) return Total+i;
         }
     }
}
else
{
// 암것도 안떴는데 턴이 남아있다면

//1.스트레이트 느낌세게왔다면?
//1-1 스몰스트레이트남아있으면
if(aIscore[OX_S_Straight] == 0)
{
        int n[6] = {0};
        int index = 0;
        for(int i=0;i<5;i++)
        {
            n[(dice[i]-1)]++; //개수체크배열에 저장
        }
        //1 2 1 0 0 1
        std::ostringstream os;
        for (int i: n) {
        if(i>0) os << 1;
        else os << 0;
        }
        std::string str(os.str());

            //연속3개 ex 123
            if(str.find("111") != string::npos) return S_Straight;
            //한칸 떨어진 3개 //1 0 2 1 0 1
            else if(str.find("1011")!= string::npos) return S_Straight;
            else if(str.find("1101")!= string::npos) return S_Straight;
            
}
//1-2 스몰없고 라지만있으면
if(aIscore[OX_S_Straight] == 1 && aIscore[OX_L_Straight] == 0)
{
        int n[6] = {0};
        int index = 0;
        for(int i=0;i<5;i++)
        {
            n[(dice[i]-1)]++; //개수체크배열에 저장
        }
        //1 2 1 0 0 1
        std::ostringstream os;
        for (int i: n) {
        if(i>0) os << 1;
        else os << 0;
        }
        std::string str(os.str());

            if(str.find("1111") != string::npos) return L_Straight;
            //한칸 떨어진 4개
            else if(str.find("10111")!= string::npos) return L_Straight;
            else if(str.find("11011")!= string::npos) return L_Straight;
            else if(str.find("11101")!= string::npos) return L_Straight;
}
int want = TheMostNumber(dice);
int nwant = TheNumberOfNumbers(dice,want);
switch(nwant)
{
//2. 같은거 3개이상떴을때 어떻게할지 (4,5는 안나옴)
case 3:
{
    //윗판
    if(aIscore[Total+want]==0)  return want;
    //윗판썼으면
    else
    {
        if(aIscore[OX__4ofakind]==0||aIscore[OX_Yacht]==0) return _4ofakind;
        if(aIscore[OX_FullHouse]==0) return FullHouse;
    }
}
//3. 투페어일때 어떻게할지
//4. 원페어일때 어떻게할지
case 2:
{
int wantmin = TheMostNumber(dice,5,1);
//투페어
if(want != wantmin)
{
    //나만의공식 3*작은수>=2*큰수 - true면 풀하각보기 false 중복각보기
    if(aIscore[OX_FullHouse ==0])
    {
        if(3*wantmin >= 2*want) return FullHouse;
    }
    //풀하각 못보고 중복각일때 
    //윗판안썼으면
    if(aIscore[Total+want]==0)  return want;
    //윗판썼으면
    else
    {
        if(aIscore[OX__4ofakind]==0||aIscore[OX_Yacht]==0) return _4ofakind;
    }

}
//원페어
else
{   //윗판안썼으면
    if(aIscore[Total+want]==0)  return want;
    //윗판썼으면
    else
    {   //스트레이트 둘다 썼다
        if(aIscore[OX_S_Straight] == 1 && aIscore[OX_L_Straight]==1)
        {   //4ofkind yacht 둘다썼다
            if(aIscore[OX__4ofakind] == 1 && aIscore[OX_Yacht]==1); //넘어가
            //아니다
            else return _4ofakind;
        }
        //스트레이트 남았다면
        else ; //넘어가
    }
}
}
//5. 같은것이 하나도없을때 혹은 위에서 결정나지않았을때
{

    //스트레이트 둘다 썼다면 어쩔수없이 걍 하나 집고가
    if(aIscore[OX_S_Straight] == 1 && aIscore[OX_L_Straight]==1)
    {
        //초이스안썼으면 초이스써라
        if(aIscore[OX_Choice]==0)
         {
            //총합 21이상
            if(TheTotalOfNumber(dice)>=21)  return Choice;
         }

        //내주사위중에 456 있고 (fours/fives/sixes)중에 안쓴거 있다면
        if(TheNumberOfNumbers(dice,6) >0 && aIscore[OX_Sixes] == 0) return Sixes;
        if(TheNumberOfNumbers(dice,5) >0 && aIscore[OX_Fives] == 0) return Fives;
        if(TheNumberOfNumbers(dice,4) >0 && aIscore[OX_Fours] == 0) return Fours;
        // four five sixes안쓴거 없다면
        if(TheNumberOfNumbers(dice,6) >0) return _4ofakind;
        if(TheNumberOfNumbers(dice,5) >0) return _4ofakind;
        if(TheNumberOfNumbers(dice,4) >0) return _4ofakind;


        // 456 없다면 다시던져라
        return -1;
    }
    else//스트레이트 남았다면
    {
        if(aIscore[OX_S_Straight] == 0) return S_Straight;
        if(aIscore[OX_L_Straight] == 0) return L_Straight;
    }
}
return -1; //이렇게하면 오류안생기나 싶어서 임시로넣음
break;

default:
return -1; //이렇게하면 오류안생기나 싶어서 임시로넣음
break;
}
}
}
}
break;
case 2:
break;
}

return -1; //걍다시던져라
}


void AI_FixDice(int * dice,bool * fixdice,int angle,bool& oX_report)
{
    FixWantNumber(dice,fixdice,-1); //일단 주사위 고정 다풀고.

    //기록을 해야하는 상황이라면( 턴0 or yacht같은거 떠서)
    if(angle >= OX_Aces && angle <= OX_Yacht)
    {
        for(int i=0;i<5;i++) fixdice[i] = 1; //다 고정
        oX_report = true;
        return;
    }
    //각보는거에따라 고정주사위 정하기
    switch(angle)
    {
        //ace deuce three four five six
        {
        case Aces:
        case Deuces:
        case Threes:
        case Fours:
        case Fives:
        case Sixes:
        
            int want = 0;
            if(angle == Aces) want = 1;
            else if(angle == Deuces) want = 2;
            else if(angle == Threes) want = 3;
            else if(angle == Fours) want = 4;
            else if(angle == Fives) want = 5;
            else if(angle == Sixes) want = 6;

            FixWantNumber(dice,fixdice,want);
            break;
        }
        //Choice
        case Choice: //456만 들고감
            for(int i=0;i<5;i++)
            {
                if(dice[i]>=4)   fixdice[i] = 1;
                else fixdice[i] = 0;
            }
            break;

    
        
        //FullHouse
        case FullHouse:
        {
            int nwant = 0;
            int want = TheMostNumber(dice);
            nwant = TheNumberOfNumbers(dice,want);

            //같은눈이 3개이상
            if(nwant >=3)
            {
                FixWantNumber(dice,fixdice,want);
                if(nwant >=4)//혹시 4개이상
                {
                    for(int i=0; i<5;i++)
                    {
                        if(dice[i]==want)
                        {
                        fixdice[i] = 0;
                        nwant --;
                        }
                        if(nwant == 3)break;
                    }
                }         
            }
            //같은눈이 2개
            else if(nwant ==2)
            {
                int want2 = TheMostNumber(dice,5,1);

                //2개 2개
                if(want != want2)
                {
                    for(int i=0;i<5;i++)
                    {
                        if(dice[i] == want || dice[i] == want2) fixdice[i] = 1;
                        else fixdice[i] = 0;
                    }
                }
                //그냥 2개
                else
                {
                    FixWantNumber(dice,fixdice,want);
                }
            }
            // 눈이 다다름
            else
            {
                FixWantNumber(dice,fixdice,want);
            }
        }
        break;

        //Straight 아 그냥 두개 같이 묶어서할래 별로안좋은 알고리즘
        case S_Straight:
        case L_Straight:
        {
        int n[6] = {0};
        int index = 0;
        for(int i=0;i<5;i++)
        {
            n[(dice[i]-1)]++; //개수체크배열에 저장
        }

        //1 2 1 0 0 1
        std::ostringstream os;
        for (int i: n) {
        if(i>0) os << 1;
        else os << 0;
        }
        std::string str(os.str());
            //l_straight용
            // 2개 분리시켜서 10111 11011 11101 추가해야함
            if(str.find("1111") != string::npos)
            {
                index = str.find("1111") + 1;
                FixWantNumberJustOne(dice,fixdice,index);
                FixWantNumberJustOne(dice,fixdice,index+1);
                FixWantNumberJustOne(dice,fixdice,index+2);
                FixWantNumberJustOne(dice,fixdice,index+3);
            }

            //연속3개 ex 123
            else if(str.find("111") != string::npos)
            {
                index = str.find("111") + 1;
                FixWantNumberJustOne(dice,fixdice,index);
                FixWantNumberJustOne(dice,fixdice,index+1);
                FixWantNumberJustOne(dice,fixdice,index+2);
            }
            //한칸 떨어진 3개 //1 0 2 1 0 1
            else if(str.find("1011")!= string::npos)
            {
                index = str.find("1011") + 1;
                FixWantNumberJustOne(dice,fixdice,index);
                FixWantNumberJustOne(dice,fixdice,index+2);
                FixWantNumberJustOne(dice,fixdice,index+3);
            }
            else if(str.find("1101")!= string::npos)
            {
                index = str.find("1101") + 1;
                FixWantNumberJustOne(dice,fixdice,index);
                FixWantNumberJustOne(dice,fixdice,index+1);
                FixWantNumberJustOne(dice,fixdice,index+3);
            }

            //한칸떨어진2개 붙은2개
            else if(str.find("11")!= string::npos)
            {
                index = str.find("11") + 1;
                FixWantNumberJustOne(dice,fixdice,index);
                FixWantNumberJustOne(dice,fixdice,index);
            }
            else if(str.find("101")!= string::npos)
            {
                index = str.find("101") + 1;
                FixWantNumberJustOne(dice,fixdice,index);
                FixWantNumberJustOne(dice,fixdice,index+2);
            }

            else{
            //default
            ;
            }
        

        }
        break;

        //yacht,4ofakind
        case _4ofakind:
        case Yacht:
        {
            int want = TheMostNumber(dice);
            FixWantNumber(dice,fixdice,want);
        }
        break;

        //다시던지기
        default:
        {
            ;
        }
        break;
    }
}

    

void GamePlay(MAINMENU mode)
{   
    MAINMENU gamemode = mode;
    int whoseturn = 1; //1 p1턴 -1 p2턴
    int individual_turn = 3; //3번가능한거
    int myScore[32] = {0}; //점수기록판
    int aIScore[32] = {0};
    int dice[5]; //5개 주사위값
    bool fixdice[5] = {0}; //1고정 0리롤
    int nPage =3; //보고있는페이지
    int x =0;
    int y = 0;
    int nInput =0;
    RerollDiceAll(dice,fixdice);
    myScore[TURN]++;

    while(true){
    clean();
    switch(nPage)
    {
        case 1://기록
        {
            //기록하면  변수초기화해줘야함
            //그리고 상대턴으로 넘어가야함
            //12턴 막턴끝나면 겜끝나야함
            //방향키 위아래로할때마다 기록할수 있는 점수 나와야함
            // 이미기록되어있는 점수가있으면 그게 나와야함(혹은 이미나와있음) 점수기록판을 덮어씌우면 되겟다
            int nInput = 0;
            PrintPage_1();
            PrintFixDice(dice,fixdice);
            PrintUserCursor2(y);
            PrintReportTempScore(dice,y,whoseturn);
            // 여기에 printgamescoreboard 함수 와야됨 점수 기록된버전으로.
            PrintGameScoreBoard(myScore,aIScore);
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
                //기록
                if(whoseturn == 1){
                if(myScore[y+1+15] != 0) break; //기록되어있으면 못하게
                {
                myScore[y+1+15] = 1; //기록여부
                myScore[y+1] = ScoreAlgorithm(dice,y+1); //점수저장
                myScore[Total] += myScore[y+1]; //토탈에도 갱신
                if(y>=0 && y<=5)
                myScore[SubTotal] += myScore[y+1]; //서브토탈도 갱신
                if(myScore[SubTotal]>=63){
                    if(myScore[_35bonus] != 35)
                 {
                    myScore[_35bonus] = 35;
                    myScore[Total] += 35;
                 }
                } //보너스체크
                }
                }
                else
                {
                if(aIScore[y+1+15] != 0) break;
                aIScore[y+1+15] = 1;
                aIScore[y+1] = ScoreAlgorithm(dice,y+1);
                aIScore[Total] += aIScore[y+1]; //토탈에도 갱신
                if(y>=0 && y<=5)
                aIScore[SubTotal] += aIScore[y+1];
                if(aIScore[SubTotal]>=63){
                    if(aIScore[_35bonus] != 35)
                 {
                    aIScore[_35bonus] = 35;
                    aIScore[Total] += 35;
                 }
                } //보너스체크
                }
                
                

                //턴 끝나서 상대턴을 위해 변수 초기화
                individual_turn = 3;
                x=0;
                y=0;
                for(int i =0;i<5;i++)
                {
                    fixdice[i] = 0;
                }       
                RerollDiceAll(dice,fixdice);
                //차례 넘겨주기
                whoseturn *= -1;
                if(myScore[TURN]>aIScore[TURN]) aIScore[TURN]++;
                else myScore[TURN]++;
                //게임끝내는조건
                if(myScore[TURN]>12)
                {
                    nPage =-1; //결과창
                    break;
                }

                if(gamemode == START) nPage = 3;
                if(gamemode == START_AI) nPage = 5;
                break;
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
            PrintGameScoreBoard(myScore,aIScore);
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
            PrintGameScoreBoard(myScore,aIScore);
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
            RerollDiceAll(dice,fixdice);
            individual_turn --;

            PrintRerollDiceWaiting(dice,fixdice);

            nPage =2;
            break;
            }

            //스페이스 (흔들기) ( 미완성) 버그있음 흔들기하고 돌아가기해서 그걸로 기록가능함
            if(nInput == SPACE) 
            {
            break;   //버그있어서 브레이크 걸어둠
            RerollDiceAll(dice,fixdice);
            
            //흔들기 효과 넣으면 좋을듯 그래서 넣었스비다
            PrintPage_3test();
            gotoxy(2,24); printf("!!!!!\n");
            sleep(1);

            nPage =3;
            break;
            }
            
            

        }
        break;
        case -1://결과임시 나중에 더 예쁘게합시다
        gotoxy(1,1);
        printf("게임끝!\n");
        printf("p1점수:%d\np2점수:%d\n",myScore[Total],aIScore[Total]);
        sleep(5);

        case 5://AI초급 작동
        //첫번째던지기 -> 알고a(고정하기) -> 두번째던지기 ->알고b(고정하기) -> 세번째던지기 -> 알고b(기록하기)
        {
            bool oX_report = false; //기록해야할지 말아야할지
            int angle; //각보고있는거

            while(true)//던지는과정
            {
            if(oX_report) break; //기록해야하면 while 탈출
            RerollDiceAll(dice,fixdice);
            individual_turn --;
            {//리롤페이지(3) 출력
            clean();
            PrintPage_3();
            PrintFixDice(dice,fixdice);
            PrintRerollDiceGame(dice,fixdice);
            PrintGameScoreBoard(myScore,aIScore);
            sleep(1);
            PrintRerollDiceWaiting(dice,fixdice);
            }
            {//고정페이지(2)출력
            clean();
            PrintPage_2(individual_turn);
            PrintFixDice(dice,fixdice);
            PrintRerollDice(dice,fixdice);
            PrintAlgorithm(dice);
            PrintGameScoreBoard(myScore,aIScore);
            }
            angle = (int)(AI_DecideAlgorithm(dice,fixdice,individual_turn,aIScore)); //알고리즘 정하기(상황판단하기) 바로기록해야할수도 /  
            //알아야할거 : 주사위던지기횟수,턴(점수표에있음), 내가기록한거, 상대점수(이건너무어려울듯)
            //반환해야할거 : 각보고있는거(ex. s.straight)  턴0이면 기록해야할위치(12개중에)를 각보고잇는거에 저장
            //원하는거 떳으면 각보고잇는거에 기록해야할위치 저장
            AI_FixDice(dice,fixdice,angle,oX_report); //알고리즘에따라 주사위 고정시키기 //매개변수에 위에함수 반환값들어가면될듯
            //기록해야하는지 던져야하는지 알려야하기때문에 ox_report 참조자로 받아.
            {
            //다시한번 고정페이지(2)출력
            sleep(3);
            clean();
            PrintPage_2(individual_turn);
            PrintFixDice(dice,fixdice);
            PrintRerollDice(dice,fixdice);
            PrintAlgorithm(dice);
            PrintGameScoreBoard(myScore,aIScore);
            }
            }


            //기록
            {//기록페이지(1)
            clean();
            PrintPage_1();
            PrintFixDice(dice,fixdice);
            PrintGameScoreBoard(myScore,aIScore);
            }

            //기록하는함수 변수초기화 등
            {
                //기록
                if(whoseturn == 1){
                if(myScore[y+1+15] != 0) break; //기록되어있으면 못하게
                {
                myScore[y+1+15] = 1; //기록여부
                myScore[y+1] = ScoreAlgorithm(dice,y+1); //점수저장
                myScore[Total] += myScore[y+1]; //토탈에도 갱신
                if(y>=0 && y<=5)
                myScore[SubTotal] += myScore[y+1]; //서브토탈도 갱신
                if(myScore[SubTotal]>=63){
                    if(myScore[_35bonus] != 35)
                 {
                    myScore[_35bonus] = 35;
                    myScore[Total] += 35;
                 }
                } //보너스체크
                }
                }
                else
                {
                if(aIScore[angle -15] != 0) break; // angle - 15 !!!! //기록안했다면
                aIScore[angle] = 1; //기록 여부
                aIScore[angle -15] = ScoreAlgorithm(dice,angle-15); //점수반환해서 저장
                aIScore[Total] += aIScore[angle-15]; //토탈에도 갱신
                if(angle-15>=1 && angle-15<=6)
                aIScore[SubTotal] += aIScore[angle-15];
                if(aIScore[SubTotal]>=63){
                    if(aIScore[_35bonus] != 35)
                 {
                    aIScore[_35bonus] = 35;
                    aIScore[Total] += 35;
                 }
                } //보너스체크
                }
                
                

                //턴 끝나서 상대턴을 위해 변수 초기화
                individual_turn = 3;
                x=0;
                y=0;
                for(int i =0;i<5;i++)
                {
                    fixdice[i] = 0;
                }       
                RerollDiceAll(dice,fixdice);
                //차례 넘겨주기
                whoseturn *= -1;
                if(myScore[TURN]>aIScore[TURN]) aIScore[TURN]++;
                else myScore[TURN]++;
                //게임끝내는조건
                if(myScore[TURN]>12)
                {
                    nPage =-1; //결과창
                    break;
                }
                nPage = 3;

                break;
            }

            
        }
        return;
        

        default: break;
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
                    GamePlay(START);
            }
            break;
            case START_AI:
            {
                    clean();
                    GamePlay(START_AI);
            }
            break;
            case EXIT:
            return 0;
        }
    }
    return 0;
}
