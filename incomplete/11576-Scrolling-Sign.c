#include <iostream>
#include<cctype>
#include<ctype.h>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<math.h>
#include<fstream>
#include<map>
#include<set>
#include<queue>
#include<stdio.h>
#include<cstring>
#include<sstream>
#include<locale>
#include<utility>
#include<list>
using namespace std;

#ifdef _DEBUG

   #include <fstream>

   istream * in;
   ostream * out;
#endif

#define MP make_pair
#define VI vector<int>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define CUBE(a) ((a)*(a)*(a))
#define SQ(a) ((a)*(a))


int main()
{
    #ifdef _DEBUG

     in  = new ifstream("entrada.txt");
     out = new ofstream("salida.txt");
     cin.rdbuf(in->rdbuf());
     cout.rdbuf(out->rdbuf());
    #endif

    int n , lon , tim, tot;
    string s ,sa;
    cin>>n;
    while(n--)
    {
        cin>>lon>>tim;
        cin>>sa;
        tot = sa.size();
        tim--;
        while(tim--)
        {
            cin>>s;
            int i;
            for(i = 0 ; i < sa.size() ; ++i)
            {
                int j;
                for(j = 0 ; j+i < sa.size() ; ++j)
                {
                    if(sa[i+j] != s[j])break;
                }
                if(j+i == sa.size())
                {
                    tot += s.size()-j;
                    break;
                }
            }
            if(i == sa.size())
            {
                tot += i;
            }
            sa = s ;
        }
        cout<<tot<<endl;
    }
}
