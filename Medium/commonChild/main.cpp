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
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */
int lcsRec(string &s1, string &s2,int m,int n, vector<vector<int>> &memo){
    if (m == 0 || n == 0) return 0;

    if (memo[m][n] != -1) return memo[m][n];
    
    if (s1[m - 1] == s2[n - 1]) return memo[m][n] = 1 + lcsRec(s1, s2, m - 1, n - 1, memo);
    
    return memo[m][n] = max(lcsRec(s1, s2, m, n - 1, memo), lcsRec(s1, s2, m - 1, n, memo));
}

int commonChild(string s1, string s2) {
    vector<vector<int>> memo(s1.size()+1, vector<int>(s1.size()+1, -1));
    return lcsRec(s1,s2,s1.size(),s2.size(), memo);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

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