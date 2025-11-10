#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <bits/stdc++.h> 
using namespace std;


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


/* 
Input format:
 1. SHINCHAN <two same ength strings ↓>
 2. NOHARAAA

Output:
 3. 3        <length of longest common subsequence>

Note:
 - https://www.geeksforgeeks.org/dsa/longest-common-subsequence-dp-4/

*/