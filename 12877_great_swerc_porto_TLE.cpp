#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int N; // num words
int* W[10][10]; // words pointing to values
int L[10]; // length of each word
int V[10]; // values of each char
int numChars = 0; // num of chars
bool U[10]; // tested numbers

bool hasLeadingZeros()
{
    for (int i = 0; i < N; ++i)
    {
        if (*(W[i][0]) == 0)
        {
            return true;
        }
    }
    
    return false;
}

int getNumberForWord(int w)
{
    int n = 0;
    
    for (int i = 0; i < L[w]; ++i)
    {
        int num = *(W[w][i]);
        n += num * pow(10, L[w] - i - 1);
    }
    
    return n;
}

bool isValidAssignment()
{
    int sum = 0;
    int res = getNumberForWord(N - 1);

    for (int i = 0; i < N - 1; ++i)
    {
        int num = getNumberForWord(i);
        
        if (num > res)
        {
            return false;
        }
        
        sum += num;
    }
    
    return sum == res;
}

void getNumAssignments(int& totalAssignments, int assignedChars)
{
    if (assignedChars == numChars)
    {
        if (isValidAssignment())
        {
            ++totalAssignments;
        }
    }
    else
    {
        for (int i = 0; i < 10; ++i)
        {
            if (!U[i])
            {
                U[i] = true;
                V[assignedChars] = i;
             
                if (!(i == 0 && hasLeadingZeros()))
                {
                    getNumAssignments(totalAssignments, assignedChars + 1);
                }
                
                V[assignedChars] = -1;
                U[i] = false;
            }
        }
    }
}

int main()
{
    while (cin >> N)
    {
        string w;
    
        map<char, int*> corresp;
    
        numChars = 0;
    
        for (int i = 0; i < 10; ++i)
        {
            U[i] = false;
            V[i] = -1;
        }
    
        for (int i = 0; i < N; ++i)
        {
            cin >> w;
            
            L[i] = w.length();
            
            for (int j = 0; j < w.length(); ++j)
            {
                char c = w[j];
                
                map<char, int*>::iterator it = corresp.find(c);
                
                if (it == corresp.end())
                {
                    corresp[c] = V + numChars;
                    W[i][j] = V + numChars;
                    ++numChars;
                }
                else
                {
                    W[i][j] = corresp[c];
                }
            }
        }
        
        int totalAssignments = 0;
        getNumAssignments(totalAssignments, 0);
        cout << totalAssignments << endl;
    }

    return 0;
}

