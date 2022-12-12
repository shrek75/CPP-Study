#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> v;
    //v.reserve(8); //capacity

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    for(vector<int>::size_type i = 0; i<v.size();i++)
    {
        cout << v[i] << endl;
    }

    for(vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
    {
        cout << *iter << endl;
    }

    vector<int>::const_iterator iter = v.begin();
    cout << iter[2] << endl;
    
    return 0;

}