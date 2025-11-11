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

//Recursive function with memoization to find LCS length
int lcsRec(string &s1, string &s2,int m,int n, vector<vector<int>> &memo){
    
    //Base Case
    if (m == 0 || n == 0) return 0;

    //Check if the result for this subproblem is already computed
    if (memo[m][n] != -1) return memo[m][n];
    
    //Match Case
    if (s1[m - 1] == s2[n - 1]) return memo[m][n] = 1 + lcsRec(s1, s2, m - 1, n - 1, memo);
    
    //Don't Match Case
    return memo[m][n] = max(lcsRec(s1, s2, m, n - 1, memo), lcsRec(s1, s2, m - 1, n, memo));
}

/*Improoved with a 2d dp array
// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcs(string &s1, string &s2) {
    int m = s1.size();
    int n = s2.size();

    // Initializing a matrix of size (m+1)*(n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Building dp[m+1][n+1] in bottom-up fashion
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
    return dp[m][n];
}
*/

int commonChild(string s1, string s2) {
    //2d memoization array
    //size is (m+1)x(n+1) initialized to -1
    //the array serves to avoid recomputation of already solved subproblems
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