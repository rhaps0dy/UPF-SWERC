#include<iostream>
#include<map>
#include<string>

using namespace std ;

int main(){
    map<char,bool> var;
    string s;
    int n;
    cin>>n;
    while(n > 0 )
    {
        --n;

        bool out = false , neg = false;
        cin>>s;
        for(int i = 0 ; i < s.size(); ++i)
        {
            if(s[i] == '~')
            {
                neg = true;
                continue;
            }
            if(s[i] >= 'a' && s[i]<= 'z')
            {
                if(var.find(s[i]) == var.end())
                {
                    var[s[i]] = !neg;
                    neg = false;
                    continue;
                }else{
                    if(var[s[i]] == !neg)
                    {
                        neg = false;
                        continue;
                    }
                    else
                    {
                        while(s[i] != ')')++i;
                        neg = false;
                        var.clear();
                        continue;
                    }
                }
            }
            if(s[i] == ')')
            {
                out = true;
            }
        }
        if(out)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
