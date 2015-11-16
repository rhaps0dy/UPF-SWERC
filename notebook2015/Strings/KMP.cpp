/*Search of substring in O(n+k) */
void TablaKMP(string T,vector<int> &F)
{
    int pos = 2; // posicion actual en F
    int cnd = 0; // índice en T del siguiente carácter del actual candidato en la subcadena

    F[0] = -1;
    while(pos <= T.size())
    {
        if(T[pos - 1] == T[cnd] )
        {//siguiente candidato coincidente en la cadena
            cnd++;
            F[pos] = cnd;
            pos++;
        }else if(cnd > 0)
        {//sifallan coincidencias consecutivas entonces asignamos valor conocido la primera vez
            cnd = F[cnd];
        }else{
            F[pos] = 0 ;
            pos++;
        }
    }
}
int KMPSearch(string T, string P)//T: texto donde se busca P: palabra a buscar salida: posicion del match (-1 si no encontrado
{
    int k = 0 ; //puntero de T
    int i = 0 ; //avance en P

    vector<int> F(T.size(),0);

    if(T.size() >= P.size())
    {
        TablaKMP(T,F);//optimización para no repetir busquedas de subcadenas que no hacen match
        while(k+i < T.size())
        {
            if(P[i] == T[k+i])
            {
                if(i == P.size()-1)
                {
                    return k; //modificando el return podemos devolver todos los matches
                }
                i++;
            }else{
                k += i-F[i];
                if(i > 0)
                {
                    i = F[i];
                }
            }
        }
    }
    return -1;
}

int main(){
    string T = "PARTICIPARIA CON MI PARACAIDAS PARTICULAR";
    string P = "RTI";
    cout<<KMPSearch(T,P)<<endl;
}
