#include<iostream>
#include<vector>
#include<queue>

using namespace std ;

int main(){
    int n;
    cin>>n;
    while(n--)
    {
        int ix;
        cin>>ix;
        int p,cont = 0 ;
        vector<int> f;
        for(int k = 0 ; k < 20 ; ++k)
        {
            cin>>p;
            for(int i = 0 ; i < f.size()+1 ; ++i)
            {
                if(i == f.size())
                {
                    f.push_back(p);
                    break;
                }else{
                    if(p < f[i])
                    {
                        int aux;
                        cont += f.size()-i ;
                        for(int j = i ; j < f.size(); ++j)
                        {
                            aux = f[j];
                            f[j] = p;
                            p = aux;
                        }
                        f.push_back(p);
                        break;
                    }
                }
            }

        }

        cout<<ix<<" "<<cont<<endl;
    }
}
