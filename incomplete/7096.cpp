#include<iostream>

using namespace std;

int main(){
    int n;
    cin>>n;
    while(n--)
    {
        long long xi,a,b,lvl = 0;
        char caca;
        cin>>xi;
        cin>>a>>caca>>b;
        lvl = a/b;
        a = a % b ;
        b -= a;
        a+=b;
        b = lvl * a + b;
        cout<<xi<<" "<<a<<"/"<<b<<endl;
    }
}
