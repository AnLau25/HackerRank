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

/*
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(string gene) {
    int n = gene.size(), result = n;
    //Vectors storing the list of cumulative counts of each character
    vector<int> A = {0}, C = {0}, T = {0}, G = {0};
    
    for (int i=0; i < n; i++) {
        //Turns the vectors into sums of char apparitions up to index i
        //Meaning that vec.back() will always be the total count of that char in the whole string
        A.push_back(A.back() + (gene[i] == 'A' ? 1 : 0));
        C.push_back(C.back() + (gene[i] == 'C' ? 1 : 0));
        T.push_back(T.back() + (gene[i] == 'T' ? 1 : 0));
        G.push_back(G.back() + (gene[i] == 'G' ? 1 : 0));
    }
    
    //If already steady
    if (A.back() == n/4 and C.back() == n/4 and T.back() == n/4 and G.back() == n/4) return 0;
    
    for (int i=1; i <= n; i++) {
        //This line finds the earliest position j ≥ i such that the number of 'char' from i to j ≥ A.back() - n/4
        //𝗹𝗼𝘄𝗲𝗿_𝗯𝗼𝘂𝗻𝗱 searches for the earliest j where the number of that letter is reduced enough to reach the balanced condition.
        auto itA = lower_bound(A.begin()+i, A.end(), A.back()+A[i-1]-n/4);
        auto itC = lower_bound(C.begin()+i, C.end(), C.back()+C[i-1]-n/4);
        auto itT = lower_bound(T.begin()+i, T.end(), T.back()+T[i-1]-n/4);
        auto itG = lower_bound(G.begin()+i, G.end(), G.back()+G[i-1]-n/4);

        //if end is reached for any character, break the loop
        if (itA == A.end() or itC == C.end() or itT == T.end() or itG == G.end()) break;
        
        //Take the maximum index among all four, because all conditions must be satisfied (for A, C, T, G).
        //So j is the furthest point needed to make the substring [i, j] balance all letters.
        int j = max({distance(A.begin(), itA), distance(C.begin(), itC), distance(T.begin(), itT), distance(G.begin(), itG)});
        result = min(result, j-i+1); //Keep track of the smallest substring length that balances all four bases
    }
    return result;

}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

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


/* 
Input format:
 1. 8         <length of gene string>
 2. GAAATAAA  <gene string>
 
Output:
 5. 5         <length of the smallest substring that can be replaced to make the gene steady>
*/