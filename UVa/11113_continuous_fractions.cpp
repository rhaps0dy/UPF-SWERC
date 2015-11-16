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

VI digitos , linea;

int digits(unsigned long long n)
{
    int i = 0 ;

    while(n!= 0)
    {
        n /= 10 ;
        ++i;
    }
    if(i == 0)return 1;
    else return i;
}

int lineas(vector<unsigned long long> &c , int pos)
{
    int d , lin;
    if(pos != c.size()-1)
    {
        d = digits(c[pos]);
        digitos.push_back(d);
        lin =  d + 3 + lineas(c,++pos);
        linea.push_back(lin);
        return lin ;
    }
    else
    {
        d = 1;
        lin = 1 ;
        digitos.push_back(d);
        linea.push_back(0);
        linea.push_back(lin);

        return lin;
    }
}

int main()
{
    #ifdef _DEBUG

     in  = new ifstream("entrada.txt");
     out = new ofstream("salida.txt");
     cin.rdbuf(in->rdbuf());
     cout.rdbuf(out->rdbuf());
    #endif

    unsigned long long caso = 1 , d1 , d2 , div , res;
    vector<unsigned long long> p ;
    while(cin>>d1>>d2)
    {


        if(d1 == 0 && d2 == 0) break;
        if(caso != 1)cout<<endl;

        cout<<"Case "<<caso++<<":"<<endl;
        cout<<d1<<" / "<<d2<<endl;

        p.clear();
        digitos.clear();
        linea.clear();

        while(d2 != 0)
        {
            div = d1 / d2 ;
            res = d1 % d2 ;
            p.push_back(div);
            d1 = d2 ;
            d2 = res ;
        }
        p[p.size()-1] = p[p.size()-1] -1 ;

        p.push_back(1);
        int gp = lineas(p,0) , dig , ant = 0;
        for(int i = 0 ; i < p.size()-1 ; ++i)
        {
            for(int j = 0; j < (gp - (linea[linea.size()-1-(i+1)]/2 +1 ) ) ; ++j )
            {
                cout<<".";
            }
            cout<<"1";
            for(int j = 0 ; j < linea[linea.size()-1-(i+1)]/2 ; ++j)
            {
                cout<<".";
            }
            cout<<endl;
            for(int j = 0 ; j < gp - (linea[linea.size()-1-(i+1)] + 3 + digitos[i]) ; ++j )
            {
                cout<<".";
            }
            cout<<p[i]<<".+.";
            for(int j = 0 ; j < linea[linea.size()-1-(i+1)] ; ++j)
            {
                cout<<"-";
            }
            cout<<endl;
        }
        for(int ii = 0 ; ii < gp-1 ; ++ii)
        {
            cout<<".";
        }
        cout<<"1";
    }
}
