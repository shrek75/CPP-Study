#include <iostream>
#include <vector>
using namespace std;
int main()
{
    /*
    4
    23124 distance
    524212 price
    */
    int n=0; //도시의 개수
    scanf("%d",&n);
    vector<int> distance;
    distance.reserve(n-1);
    vector<int> price;
    price.reserve(n);
    int min = 0;
    long long int result =0;
    int index = -1;
    int index2 =-1;
    long long int total =0;

    for(int i=0; i<n-1;i++)
    {
        scanf("%d",&min);
        distance.push_back(min);
    }
        for(int i=0; i<n-1;i++)
    {
        scanf("%d",&min);
        price.push_back(min);
    }
    scanf("%d",&min);
    min = price[0];

    for(int i=0; i<n-1; i++)
    {
        if(min>price[i])
        {
            index2 = index; //이까지는 썼다
            index = i-1; //새로운 최소값
            for(int j = index2+1; j<= index; j++)
            {
                result += distance[j];
            }
            result *= min;
            total += result;
            result =0;
            min = price[i];
            
        }
    }
    //마지막
    index2 = index; //이까지는 썼다
    index = n-2; //새로운 최소값
            for(int j = index2+1; j<= index; j++)
            {
                result += distance[j];
            }
            result *= min;
            total += result;
    std::cout << total << std::endl;

    //뭐냐 에러한번없이 한번에품 ;;;;
    return 0;
}