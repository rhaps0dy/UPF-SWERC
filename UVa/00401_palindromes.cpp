#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    map<char,char> rev;
    rev['A'] = 'A';
    rev['B'] = '.';
    rev['C'] = '.';
    rev['D'] = '.';
    rev['E'] = '3';
    rev['F'] = '.';
    rev['G'] = '.';
    rev['H'] = 'H';
    rev['I'] = 'I';
    rev['J'] = 'L';
    rev['K'] = '.';
    rev['L'] = 'J';
    rev['M'] = 'M';
    rev['N'] = '.';
    rev['O'] = 'O';
    rev['P'] = '.';
    rev['Q'] = '.';
    rev['R'] = '.';
    rev['S'] = '2';
    rev['T'] = 'T';
    rev['U'] = 'U';
    rev['V'] = 'V';
    rev['W'] = 'W';
    rev['X'] = 'X';
    rev['Y'] = 'Y';
    rev['Z'] = '5';
    rev['1'] = '1';
    rev['2'] = 'S';
    rev['3'] = 'E';
    rev['4'] = '.';
    rev['5'] = 'Z';
    rev['6'] = '.';
    rev['7'] = '.';
    rev['8'] = '8';
    rev['9'] = '.';
    
    string inputWord = "";
    
    while (cin >> inputWord)
    {
          bool pal = true, mir = true;
          
          replace(inputWord.begin(), inputWord.end(), '0', 'O');

          for (unsigned i = 0; i < 0.5 * (float)inputWord.length(); ++i)
          {
              if (inputWord[i] != inputWord[inputWord.length()-1-i])
              {
                 pal = false;
                 break;
              }
          }

          string revWord;
          for (unsigned i = 0; i < inputWord.length(); ++i)
          {
              revWord = rev[inputWord[i]] + revWord;
          }
                    
          mir = (inputWord == revWord);
          
          cout << inputWord;
          if (pal && mir) cout << " -- is a mirrored palindrome." << endl << endl;
          else if (pal) cout << " -- is a regular palindrome." << endl << endl;
          else if (mir) cout << " -- is a mirrored string." << endl << endl;
          else cout << " -- is not a palindrome." << endl << endl;
    }

    return 0;   
}
