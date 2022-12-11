#include <iostream>
#include <string>
using namespace std;

template<typename IterT,typename Func>
void For_each(IterT begin,IterT end,Func pf)
{
    while(begin != end)
    {
        pf(*begin++);
    }
}
template <typename T >
struct PrintFunctor
{
   
    string sep; //출력 구분자 정보
    PrintFunctor(const string& s= " "):sep(s){}
    void operator()(T data)
    {
        cout << data << sep;
    } 

};
int main()
{
  //  PrintFunctor<int>()(4);
    PrintFunctor<int> a;
    a(4);
    return 0;
}