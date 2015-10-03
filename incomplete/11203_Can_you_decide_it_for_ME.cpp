#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;

int main(){
    int n ;
    string s;
    cin>>n;
    while(n > 0)
    {
        bool ME = true ;
        int sw = 1 , p1 = 0, p2 = 0 , p3 = 0;
        cin>>s;
        for(int i = 0 ; i < s.size(); ++i)
        {
            if(s[i] != '?' && s[i] != 'M' && s[i] != 'E')
            {
                ME = false;
                break;
            }
            switch(sw){
                case 1:
                    if(s[i] == 'M')
                    {
                        sw = 2;
                    }else p1++;

                    break;
                case 2:
                    if(s[i] == 'E')sw = 3;
                    else p2++;
                    break;
                case 3:
                    p3++;
                    break;
            }
        }

        if(ME && sw == 3 && p1 > 0 && p2 > 0 && p3 > 0 && p3 == (p1 + p2) )cout<<"theorem"<<endl;
        else cout<<"no-theorem"<<endl;
        --n;
    }
}
