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
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int backtrack(vector<vector<int>> &matrix, int i, int j){
    if(i>=0 && i<matrix.size() && j>=0 &&
     j<matrix[0].size() && matrix[i][j]!=0){
        matrix[i][j]--;
        return (1+backtrack(matrix,i-1,j)+backtrack(matrix,i+1,j)+
        backtrack(matrix,i,j-1)+backtrack(matrix,i,j+1)+backtrack(matrix,i-1,j-1)+
        backtrack(matrix,i-1,j+1)+backtrack(matrix,i+1,j-1)+
        backtrack(matrix,i+1,j+1));
    }
    else{
        return 0;
    }
}


int connectedCell(vector<vector<int>> matrix) {
    vector<int>v;
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            if(matrix[i][j]==1){
                v.push_back(backtrack(matrix,i,j));
            }
        }
    }
    sort(v.begin(),v.end());
    if(v.empty()) return 0;
    else return v[v.size()-1];
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = connectedCell(matrix);

    cout << result << "\n";

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
Input format:
 1. 4           <n = 4>
 2. 4           <m = 4>
 3. 1 1 0 0     <grid = [[1, 1, 1, 0], [0, 1, 1, 0], [0, 0, 1, 0], [1, 0, 0, 0]]>
 4. 0 1 1 0
 5. 0 0 1 0
 6. 1 0 0 0

Output:
 7. 5           <n = 4>
*/