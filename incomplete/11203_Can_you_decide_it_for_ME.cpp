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
        bool ME = true;
        cin>>s;
        for(int i = 0 ; i < s.size() ; ++i)
        {
            if(s[i] != '?' || s[i] != 'M' || s[i] != 'E')
            {
                ME = false;
                break;
            }

        }
        --n;
    }
}
