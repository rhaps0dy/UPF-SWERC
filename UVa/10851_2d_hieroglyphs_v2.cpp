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

    map<string,char> mapa ;
    string aux;

    for(int asci = 0 ; asci < 256 ; ++asci)
    {
        aux = "";
        for(double i = 0 ; i < 8 ; ++i)
        {
            if( ( asci / int(pow (2.0,i) ) ) %2)
            {
                aux += '\\';
            }else aux += '/';
        }
        mapa[aux] = char(asci);
    }

    int n ;
    string mat[10];

    cin>>n;
    for(; n > 0 ; --n)
    {
        cin.ignore();
        for(int i = 0 ; i < 10 ; ++i)
        {
            getline(cin,mat[i]);
        }
        for(int j = 1 ; j < mat[0].size()-1 ; ++j)
        {
            aux = "";
            for(int i = 1 ; i < 9 ; ++i)
            {
                aux += mat[i][j];
            }
            cout<<mapa[aux];
        }
        cout<<endl;

    }
}
