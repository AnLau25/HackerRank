#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'matrixRotation' function below.
 *
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER r
 */

void matrixRotation(vector<vector<int>> matrix, int r) {
    int row = matrix.size(), col = matrix[0].size();
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            
            //Find layer and  layer dimensions
            int layer = min({i, j, row-1-i, col-1-j});
            
            int top = layer, left = layer;
            int bottom = row-1-layer, right = col-1-layer;

            int perimeter = 2 * ((bottom-top) + (right-left));
            
            //Index of (i,j) along the perimeter
            int idx = 0;
            
            if (i == top){ 
                idx = j-left;
            }else if (j == right){
                idx = (right-left) + (i-top);
            }else if (i == bottom){ 
                idx = (right-left) + (bottom-top) + (right-j);
            }else{ 
                idx = (right-left) + (bottom-top) + (right-left) + (bottom-i);
            }
            
            //Shift backwards by r (since anticlockwise rotation)
            int newIdx = (idx + r) % perimeter;
             
            //Map newIdx back to coordinates in original
            int x, y;
            if (newIdx < (right-left)){ 
                x = top; 
                y = left + newIdx; 
            }else if (newIdx < (right-left) + (bottom-top)){ 
                x = top + (newIdx - (right-left)); 
                y = right; 
            }else if (newIdx < (right-left)*2 + (bottom-top)){ 
                x = bottom; 
                y = right - (newIdx - ((right-left)+(bottom-top))); 
            }else{ 
                x = bottom - (newIdx - ((right-left)*2 + (bottom-top))); 
                y = left; 
            }
            
            //Print
            cout << matrix[x][y] << " ";
        }
        cout << endl;
    }
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); })
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

/* 
 1. 4 4 2        <rows m = 4, columns n = 4, rotation factor r = 2>
 2. 1 2 3 4      <matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]>
 3. 5 6 7 8
 4. 9 10 11 12
 5. 13 14 15 16

Output:
 6. 3 4 8 12     <matrix rotated by r ↓>
 7. 2 11 10 16
 8. 1 7 6 15
 9. 5 9 13 14
*/