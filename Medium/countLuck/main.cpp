#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <bits/stdc++.h> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countLuck' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING_ARRAY matrix
 *  2. INTEGER k
 */

int rowN, colN;
vector<string> grid;
vector<vector<bool>> visited;

bool dfs(int i, int j, int &waves) {
    if (grid[i][j] == '*') return true;

    visited[i][j] = true;

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    vector<pair<int,int>> moves;

    for (auto &d : dirs) {
        int ni = i + d[0];
        int nj = j + d[1];
        if (ni>=0 && ni<rowN && nj>=0 && nj<colN &&
            grid[ni][nj] != 'X' &&
            !visited[ni][nj]) 
        {
            moves.push_back({ni, nj});
        }
    }

    // Try each move: only count waves for the correct branch
    for (auto &p : moves) {
        int ni = p.first, nj = p.second;

        int old = waves;       // save wave count before recursion

        // Count wave BEFORE recursing (if multiple choices)
        if (moves.size() > 1) waves++;

        if (dfs(ni, nj, waves))
            return true;

        waves = old; // restore waves if that branch was wrong
    }
    return false;
}

string countLuck(vector<string> mx, int k) {
    grid = mx;
    rowN = mx.size();
    colN = mx[0].size();

    visited.assign(rowN, vector<bool>(colN, false));

    int si = 0, sj = 0;
    for (int i = 0; i < rowN; i++)
        for (int j = 0; j < colN; j++)
            if (grid[i][j] == 'M')
                si = i, sj = j;

    int waves = 0;
    dfs(si, sj, waves);

    return (waves == k ? "Impressed" : "Oops!");
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        string k_temp;
        getline(cin, k_temp);

        int k = stoi(ltrim(rtrim(k_temp)));

        string result = countLuck(matrix, k);

        cout << result << "\n";
    }

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
 1. week  <string to query>
 2. 2     <number of queries>
 3. 1 4   <r=1, l=4>  
 4. 2 3   <r=2, l=3>

Output:
 5. 2     <number of palindromic anagrams for substring ↓>
 6. 1

Note:
 - Ussing Fermat's little theorem for calculating modular inverses (ie for speeding up calculation). 
 - Precomputing factorials and their inverses for efficient query answering.
 - https://blogarithms.github.io/articles/2019-01/fermats-theorem
 - https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
 - https://brilliant.org/wiki/permutations-with-repetition/

*/