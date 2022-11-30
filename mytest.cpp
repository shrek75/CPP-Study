#include <iostream>

using namespace std;

int main()
{
    char question1[64] = {"이문장을따라적어보세요."};
    char myanswer[64] = {'\0'};

    cout << "아래에 나오는 문장을 똑같이 적어보세요." << endl;
    cout << question1 << endl;
    
    //스페단위로 받네.. 어떡하지.
    cin >> myanswer;

    if(!strcmp(question1,myanswer)) cout<< "성공!" << endl;
    else cout<< "실패" << endl;

    return 0;
}