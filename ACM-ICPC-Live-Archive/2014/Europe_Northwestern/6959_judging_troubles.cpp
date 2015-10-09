#include<iostream>
#include<map>
#include<stdio.h>
using namespace std;

int main()
{
    map<string,int> m;
    char in[16];
    while(true) {

    int n , result = 0 ;
    int res = scanf("%d",&n);

    if (res != 1)
        return 0;

        m.clear();

    for(int i = 0 ; i < n ; ++i)
    {
        scanf("%s",in);
        if(m.find(in) == m.end())
        {
            m[in] = 1;
        }else m[in]++;
    }
    for(int i = 0 ; i < n ; ++i)
    {
        scanf("%s",in);
        if(m.find(in) != m.end() && m[in] != 0)
        {
            m[in]--;
            result++;
        }
    }

    cout<<result<< endl;
    }
    return 0;
}
