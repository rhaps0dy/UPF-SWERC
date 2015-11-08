/**
 * Author: Daniel F.B. (Ertsiger)
 * 07/11/2015
 * Time: 0.136
 */
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>

#define X first
#define Y second
#define SZ size()

using namespace std;

typedef pair< pair<int,int>, int> P; // par de nodos + coste

int bellmanford(int N, const vector<P>& v, int a, int b)
{
    vector<int> d(N, 1000000000);
    d[a] = 0;
    for (int i = 1; i < N; i++)
        for (int j = 0; j < (int)v.SZ; j++)
            if (d[v[j].X.X] < 1000000000 && d[v[j].X.X] + v[j].Y < d[v[j].X.Y])
                d[v[j].X.Y] = d[v[j].X.X] + v[j].Y;
        for (int j = 0; j < (int)v.SZ; j++)
            if (d[v[j].X.X] < 1000000000 && d[v[j].X.X] + v[j].Y < d[v[j].X.Y])
                return -1000000000; // existe ciclo negativo
    return d[b];
}

int main()
{
    int W, H; // width and height
    
    while (cin >> W >> H)
    {
        if (W == 0 && H == 0) break;
    
        // Gravestones
        set< pair<int, int> > gravestones;

        int G; // number of gravestones
        int Gx, Gy; // gravestone position

        cin >> G;
        
        for (int g = 0; g < G; ++g)
        {
            cin >> Gx >> Gy;
            gravestones.insert(make_pair(Gy, Gx));
        }
        
        // Haunted holes
        map<int, pair<int, int> > hauntedHoles; // origin, (destination, cost)
        
        int E; // number of haunted holes
        int Ex1, Ey1, Ex2, Ey2, Et;
        
        cin >> E;
        
        for (int e = 0; e < E; ++e)
        {
            cin >> Ex1 >> Ey1 >> Ex2 >> Ey2 >> Et;
            
            int idCell1 = Ey1 * W + Ex1;
            int idCell2 = Ey2 * W + Ex2;
            
            hauntedHoles[idCell1] = make_pair(idCell2, Et);
        }
        
        // Create graveyard
        vector<P> graveyard;
        
        int origin = 0;
        int end = W * H - 1;
        
        for (int i = 0; i < H; ++i)
        {
            for (int j = 0; j < W; ++j)
            {    
                int idCell = i * W + j;
            
                map<int, pair<int, int> >::iterator it = hauntedHoles.find(idCell);
            
                // Adjacent cells cannot be reached if this cell is a haunted hole
                if (it != hauntedHoles.end())
                {
                    graveyard.push_back(make_pair(make_pair(it->first, it->second.first), it->second.second));
                }
                else
                {
                    if (idCell != end && gravestones.find(make_pair(i, j)) == gravestones.end())
                    {
                        // North adjacency
                        if (i + 1 < H && gravestones.find(make_pair(i + 1, j)) == gravestones.end())
                        {
                            int sibCell = (i + 1) * W + j;
                            graveyard.push_back(make_pair(make_pair(idCell, sibCell), 1));
                        }
                        
                        // East adjacency
                        if (j + 1 < W && gravestones.find(make_pair(i, j + 1)) == gravestones.end())
                        {
                            int sibCell = i * W + (j + 1);
                            graveyard.push_back(make_pair(make_pair(idCell, sibCell), 1));
                        }
                        
                        // West adjacency
                        if (j - 1 >= 0 && gravestones.find(make_pair(i, j - 1)) == gravestones.end())
                        {
                            int sibCell = i * W + (j - 1);
                            graveyard.push_back(make_pair(make_pair(idCell, sibCell), 1));
                        }
                        
                        // South adjacency
                        if (i - 1 >= 0 && gravestones.find(make_pair(i - 1, j)) == gravestones.end())
                        {
                            int sibCell = (i - 1) * W + j;
                            graveyard.push_back(make_pair(make_pair(idCell, sibCell), 1));
                        }
                    }
                }
            }
        }
        
        int res = bellmanford(W * H, graveyard, origin, end);
        
        if (res == 1000000000)
        {
            cout << "Impossible\n";
        }
        else if (res == -1000000000)
        {
            cout << "Never\n";
        }
        else
        {
            cout << res << "\n";
        }
    }

    return 0;
}

