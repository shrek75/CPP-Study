#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    reverse_iterator<vector<int>::iterator> riter(v.end());
    reverse_iterator<vector<int>::iterator> end_riter(v.begin());
    vector<int>::reverse_iterator riter2(v.rbegin());
    for(;riter2 != v.rend();riter2++)
    {
        cout << *riter2 << endl;
    }
    return 0;
}