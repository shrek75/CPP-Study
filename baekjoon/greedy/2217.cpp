#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n= 0;
    vector<int> v;
    scanf("%d",&n);
    for(int i=0; i<n;i++)
    {
        v.push_back(0);
        scanf("%d",&v[i]);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)
    {
        v[i] = v[i]*(n-i);
    }
    int max =0;
    for(int i=0;i<n;i++)
    {
        if(max<v[i]) max = v[i];
    }
    cout << max;
    return 0;
}