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
/*
 * Complete the 'cavityMap' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY grid as parameter.
 */

vector<string> cavityMap(vector<string> grid) {
    int n = grid.size();
    vector<string> result = grid; 

    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            char current = grid[i][j];
            if (current > grid[i-1][j] && 
                current > grid[i+1][j] &&
                current > grid[i][j-1] &&
                current > grid[i][j+1]) 
            {
                result[i][j] = 'X';
            }
        }
    }

    return result;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = cavityMap(grid);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    //fout.close();

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

/* 
Input format:
 1. 4       <grid[] size n = 4>
 2. 1112    <grid = ['1112', '1912', '1892', '1234']>
 3. 1912
 4. 1892
 5. 1234

Output:
 6. 1112
 7. 1X12
 8. 18X2
 9. 1234
*/