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
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(string gene) {
    int n = gene.size(), result = n;
    vector<int> A = {0}, C = {0}, T = {0}, G = {0};
    
    for (int i=0; i < n; i++) {
        A.push_back(A.back() + (gene[i] == 'A' ? 1 : 0));
        C.push_back(C.back() + (gene[i] == 'C' ? 1 : 0));
        T.push_back(T.back() + (gene[i] == 'T' ? 1 : 0));
        G.push_back(G.back() + (gene[i] == 'G' ? 1 : 0));
    }
    
    if (A.back() == n/4 and C.back() == n/4 and T.back() == n/4 and G.back() == n/4) return 0;
    
    for (int i=1; i <= n; i++) {
        auto itA = lower_bound(A.begin()+i, A.end(), A.back()+A[i-1]-n/4);
        auto itC = lower_bound(C.begin()+i, C.end(), C.back()+C[i-1]-n/4);
        auto itT = lower_bound(T.begin()+i, T.end(), T.back()+T[i-1]-n/4);
        auto itG = lower_bound(G.begin()+i, G.end(), G.back()+G[i-1]-n/4);

        if (itA == A.end() or itC == C.end() or itT == T.end() or itG == G.end()) break;
        
        int j = max({distance(A.begin(), itA), distance(C.begin(), itC), distance(T.begin(), itT), distance(G.begin(), itG)});
        result = min(result, j-i+1);
    }
    return result;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

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