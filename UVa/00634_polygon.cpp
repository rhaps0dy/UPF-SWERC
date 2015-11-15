#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
 int x;
 int y;        
} Point;

bool isInside(vector<Point>& points, Point& toSearch)
{
     int numberUpper = 0;
     
     for (unsigned int i = 0; i <= points.size(); ++i)
     {
         Point& p1 = points[i];
         Point& p2 = points[(i+1) % (points.size()-1)];
         
         if (p1.y == p2.y && p1.y >= toSearch.y)
         {
          if ((p1.x <= toSearch.x && p2.x >= toSearch.x) ||
              (p2.x <= toSearch.x && p1.x >= toSearch.x))
              {
               ++numberUpper;      
              }    
                  
         }
     }

     if (numberUpper % 2 == 0) return false;
     else return true;
}

int main()
{
    int size = 0;
    int x = 0, y = 0;
    
    vector<Point> points;
           Point toSearch;
    
    while (cin >> size)
    {
          if (size == 0)
             break;
    
       points.resize(size);
       
       for (unsigned int i = 0; i < size; ++i)
       {
        cin >> points[i].x >> points[i].y;
       }
       
       cin >> x >> y;

       toSearch.x = x;
       toSearch.y = y;
       
       if (isInside(points, toSearch))
       {
        cout << "T" << endl;                     
       }
       else
       {
        cout << "F" << endl;    
       }
    }
    
    return 0;
}
