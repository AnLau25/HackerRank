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
 * Complete the 'initialize' function below.
 *
 * The function accepts STRING s as parameter.
 */
const int MAXN = 100000; 
const int MOD = 1000000007; 

vector<array<int, 26>> letcmpt;
vector<long long> fact(MAXN + 1), invFact(MAXN + 1); 

long long modpow(long long base, long long exp, long long mod) { 
    long long res = 1; 
    while (exp > 0) { 
        if (exp & 1) res = (res * base) % mod; 
        base = (base * base) % mod; 
        exp >>= 1; 
    } 
    return res; 
}

void initialize(string s) {
    // This function is called once before all queries.
    int n = s.size();
    fact[0] = 1;
    
    for (int i = 1; i<=n; i++) {
        fact[i] = (fact[i-1]*i)%MOD;
    }
    invFact[n] = modpow(fact[n], MOD - 2, MOD);
    
    for(int i = n-1; i>=0; i--){
        invFact[i] = (invFact[i+1] * (i+1))%MOD; 
    }
    
    letcmpt.resize(n+1);
    letcmpt[0].fill(0);
    
    for(int i = 0; i<n; i++){
        letcmpt[i+1] = letcmpt[i];
        letcmpt[i+1][s[i] - 'a']++; 
    }
}

/*
 * Complete the 'answerQuery' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER l
 *  2. INTEGER r
 */

int answerQuery(int l, int r) {
    // Return the answer for this query modulo 1000000007.
    vector<int> freq(26);
    for(int i = 0; i<26; i++){
        freq[i] = letcmpt[r][i] - letcmpt[l-1][i];
    }
    
    long long left = 0, odds = 0, denom = 1;
    for(int f : freq){
        left +=f/2;
        if (f%2!=0) odds++;
        denom = (denom * fact[f/2]) % MOD;
    }
    
    long long res = (fact[left]*modpow(denom, MOD-2, MOD)) % MOD;
    if(odds) res = (res*odds) % MOD;
    return res;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    initialize(s);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int l = stoi(first_multiple_input[0]);

        int r = stoi(first_multiple_input[1]);

        int result = answerQuery(l, r);

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
 1. 9 5                 <expenditure[] size n =9, d = 5>
 2. 2 3 4 2 3 6 8 4 5   <expenditure = [2, 3, 4, 2, 3, 6, 8, 4, 5]>

Output:
 3. 2                   <number of notifications>
*/