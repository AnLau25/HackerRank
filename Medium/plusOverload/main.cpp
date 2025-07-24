#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix {
    public:
        vector<vector<int>> a;

        Matrix() = default;

        Matrix operator + (const Matrix& _mat) const {
            Matrix sum;
            int row = a.size();
            int col = a[0].size();

            for (int i = 0; i < row; i++) {
                vector<int> temp;
                for (int j = 0; j < col; j++) {
                    temp.push_back(a[i][j] + _mat.a[i][j]);
                }
                sum.a.push_back(temp);
            }

            return sum;
        }
};


int main () {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
   }  
   return 0;
}


/* 
Input format:
1. john doe registered <person object + string>

Output:
2. first_name=john,last_name=doe registered
*/