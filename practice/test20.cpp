#include <iostream>

using namespace std;
template <typename T>
class Stack
{
private:
    int size_;
    int capacity_;
    T * buffer;
    T * now;  //현재 가리키는곳
public:
    explicit Stack(int capacity = 100):capacity_(capacity)
    {
        size_ = 0;
        buffer = new T[capacity_];
        now = buffer;
    }
    ~Stack()
    {
        delete buffer;
    }
    bool Empty() const
    {
        if(size_==0) return 1;
        else return 0;
    }
    int Push(T data)
    {
        if(size_++ == capacity_) return -1;
        now++;
        *now = data;
    }
    T Pop()
    {
        if(size_-- == 0) throw "이럴 수는 없는 거야!";
        return *now--;
    }

};
int main()
{
    Stack<int> st;

    st.Push(10);
    st.Push(20);
    st.Push(30);

    if(!st.Empty())
    cout << st.Pop() << endl;
    if(!st.Empty())
    cout << st.Pop() << endl;
    if(!st.Empty())
    cout << st.Pop() << endl;
    return 0;
}