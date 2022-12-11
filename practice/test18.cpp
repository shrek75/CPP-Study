#include <iostream>
#include <string>

using namespace std;
template<typename RetType, typename ArgType>
class Functor
{
public:
    RetType operator() (ArgType data)
    {
        cout  << data << endl;
        return RetType(2);
    }
};

int main()
{
    Functor<bool,string> functor;
    cout<<functor("하이")<<endl;;
    return 0;
}