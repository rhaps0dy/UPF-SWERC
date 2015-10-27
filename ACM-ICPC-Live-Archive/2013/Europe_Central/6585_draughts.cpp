#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#define ROWS 10
#define COLUMNS 10

using namespace std;

char B[ROWS][COLUMNS];
bool V[10][10];

int findNumMovements(const pair<int, int>& p)
{
    int numMovements[4] = {0, 0, 0, 0};
    
    // Northwest
    {
        int nw_i = p.first - 1;
        int nw_j = p.second - 1;
        
        if (nw_i >= 0 && nw_j >= 0 && B[nw_i][nw_j] == 'B' && !V[nw_i][nw_j])
        {
            int target_i = nw_i - 1;
            int target_j = nw_j - 1;
            
            if (target_i >= 0 && target_j >= 0 && (B[target_i][target_j] == '#' || (B[target_i][target_j] == 'B' && V[target_i][target_j])))
            {
                V[nw_i][nw_j] = true;
                numMovements[0] = findNumMovements(make_pair(target_i, target_j)) + 1;
                V[nw_i][nw_j] = false;
            }
        }
    }
    
    // Northeast
    {
        int ne_i = p.first - 1;
        int ne_j = p.second + 1;
        
        if (ne_i >= 0 && ne_j < COLUMNS && B[ne_i][ne_j] == 'B' && !V[ne_i][ne_j])
        {
            int target_i = ne_i - 1;
            int target_j = ne_j + 1;
            
            if (target_i >= 0 && target_j < COLUMNS && (B[target_i][target_j] == '#' || (B[target_i][target_j] == 'B' && V[target_i][target_j])))
            {
                V[ne_i][ne_j] = true;
                numMovements[1] = findNumMovements(make_pair(target_i, target_j)) + 1;
                V[ne_i][ne_j] = false;
            }
        }
    }

    // Southwest
    {
        int sw_i = p.first + 1;
        int sw_j = p.second - 1;
        
        if (sw_i < ROWS && sw_j >= 0 && B[sw_i][sw_j] == 'B' && !V[sw_i][sw_j])
        {
            int target_i = sw_i + 1;
            int target_j = sw_j - 1;
            
            if (target_i < ROWS && target_j >= 0 && (B[target_i][target_j] == '#' || (B[target_i][target_j] == 'B' && V[target_i][target_j])))
            {
                V[sw_i][sw_j] = true;
                numMovements[2] = findNumMovements(make_pair(target_i, target_j)) + 1;
                V[sw_i][sw_j] = false;
            }
        }
    }
    
    // Southeast
    {
        int se_i = p.first + 1;
        int se_j = p.second + 1;
        
        if (se_i < ROWS && se_j < COLUMNS && B[se_i][se_j] == 'B' && !V[se_i][se_j])
        {
            int target_i = se_i + 1;
            int target_j = se_j + 1;
            
            if (target_i < ROWS && target_j < COLUMNS && (B[target_i][target_j] == '#' || (B[target_i][target_j] == 'B' && V[target_i][target_j])))
            {
                V[se_i][se_j] = true;
                numMovements[3] = findNumMovements(make_pair(target_i, target_j)) + 1;
                V[se_i][se_j] = false;
            }
        }
    }
    
    sort(numMovements, numMovements + 4);
    
    return numMovements[3];
}

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        char c;
        
        vector< pair<int, int> > lightPieces;
        
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLUMNS; ++j)
            {
               cin >> c;  
               B[i][j] = c;
               
               if (c == 'W')
               {
                   lightPieces.push_back(make_pair(i, j));
               }
            }
        }
        
        int maxMov = 0;
        
        for (int i = 0; i < lightPieces.size(); ++i)
        {
            const pair<int, int>& lightPiece = lightPieces[i];
            
            B[lightPiece.first][lightPiece.second] = '#';
            int numMov = findNumMovements(lightPieces[i]);
            B[lightPiece.first][lightPiece.second] = 'W';

            if (numMov > maxMov)
            {
                maxMov = numMov;
            }
        }
        
        cout << maxMov << endl;
    }

    return 0;
}

