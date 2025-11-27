#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <queue>
#include <cinttypes>
#include <cstring>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countStrings' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING r
 *  2. INTEGER l
 */

const int MOD = 1000000007;

// =============================================================
// NFA STRUCT
// =============================================================
struct NFA {
    int start, end;
    vector<array<vector<int>,2>> trans;
    vector<vector<int>> eps;
};

int newState(vector<array<vector<int>,2>> &t, vector<vector<int>> &e) {
    t.push_back({});
    e.push_back({});
    return (int)t.size() - 1;
}

// =============================================================
// THOMPSON CONSTRUCTION
// =============================================================
NFA literal(char c) {
    NFA n;
    int s = newState(n.trans, n.eps);
    int e = newState(n.trans, n.eps);
    n.start = s;
    n.end = e;
    n.trans[s][c=='b'].push_back(e);
    return n;
}

NFA concatNFA(const NFA &A, const NFA &B) {
    NFA r;
    r.trans = A.trans;
    r.eps   = A.eps;
    int off = r.trans.size();

    // copy B
    for (int i = 0; i < (int)B.trans.size(); i++) {
        r.trans.push_back(B.trans[i]);
        r.eps.push_back(B.eps[i]);
    }

    // fix B offsets
    for (int i = off; i < (int)r.trans.size(); i++) {
        for (int c=0;c<2;c++)
            for (int &v : r.trans[i][c])
                v += off;
        for (int &v : r.eps[i])
            v += off;
    }

    // connect
    r.eps[A.end].push_back(B.start + off);

    r.start = A.start;
    r.end = B.end + off;
    return r;
}

NFA unionNFA(const NFA &A, const NFA &B) {
    NFA r;
    r.trans = {};
    r.eps   = {};

    int s = newState(r.trans, r.eps);

    int oA = r.trans.size();
    for (int i=0;i<(int)A.trans.size();i++) {
        r.trans.push_back(A.trans[i]);
        r.eps.push_back(A.eps[i]);
    }
    for (int i=oA;i<(int)r.trans.size();i++) {
        for (int c=0;c<2;c++)
            for (int &v : r.trans[i][c])
                v += oA;
        for (int &v : r.eps[i])
            v += oA;
    }

    int oB = r.trans.size();
    for (int i=0;i<(int)B.trans.size();i++) {
        r.trans.push_back(B.trans[i]);
        r.eps.push_back(B.eps[i]);
    }
    for (int i=oB;i<(int)r.trans.size();i++) {
        for (int c=0;c<2;c++)
            for (int &v : r.trans[i][c])
                v += oB;
        for (int &v : r.eps[i])
            v += oB;
    }

    int e = newState(r.trans, r.eps);

    r.eps[s].push_back(A.start + oA);
    r.eps[s].push_back(B.start + oB);

    r.eps[A.end + oA].push_back(e);
    r.eps[B.end + oB].push_back(e);

    r.start = s;
    r.end   = e;
    return r;
}

NFA starNFA(const NFA &A) {
    NFA r;
    r.trans = {};
    r.eps   = {};

    int s = newState(r.trans, r.eps);

    int oA = r.trans.size();
    for (int i=0;i<(int)A.trans.size();i++) {
        r.trans.push_back(A.trans[i]);
        r.eps.push_back(A.eps[i]);
    }
    for (int i=oA;i<(int)r.trans.size();i++) {
        for (int c=0;c<2;c++)
            for (int &v : r.trans[i][c])
                v += oA;
        for (int &v : r.eps[i])
            v += oA;
    }

    int e = newState(r.trans, r.eps);

    r.eps[s].push_back(A.start + oA);
    r.eps[s].push_back(e);
    r.eps[A.end + oA].push_back(A.start + oA);
    r.eps[A.end + oA].push_back(e);

    r.start = s;
    r.end   = e;
    return r;
}

// =============================================================
// PARSER (FULLY PARENTHESIZED REGEX)
// =============================================================
NFA parse(const string &s, int &i);

NFA parseElement(const string &s, int &i) {
    if (s[i] == 'a' || s[i] == 'b') {
        char c = s[i++];
        return literal(c);
    }

    if (s[i] == '(') {
        i++; // skip '('
        NFA L = parse(s, i);
        char op = s[i++]; // | or next element beginning

        if (op == '|') {
            NFA R = parse(s, i);
            i++; // skip ')'
            return unionNFA(L, R);
        }
        else {
            // concatenation
            i--; // un-read char
            NFA R = parse(s, i);
            i++; // skip ')'
            return concatNFA(L, R);
        }
    }

    return literal('a'); // unreachable
}

NFA parse(const string &s, int &i) {
    NFA x = parseElement(s, i);
    if (i < (int)s.size() && s[i] == '*') {
        i++;
        return starNFA(x);
    }
    return x;
}

NFA buildRegex(const string &s) {
    int i = 0;
    return parse(s, i);
}

// =============================================================
// EPSILON CLOSURES
// =============================================================
vector<vector<int>> computeClosure(const NFA &nfa) {
    int N = nfa.trans.size();
    vector<vector<int>> C(N);

    for (int i=0;i<N;i++) {
        vector<bool> vis(N,false);
        vector<int> q = {i};
        vis[i] = true;

        for (int p=0;p<(int)q.size();p++) {
            int u = q[p];
            C[i].push_back(u);
            for (int v : nfa.eps[u]) if (!vis[v]) {
                vis[v] = true;
                q.push_back(v);
            }
        }
        sort(C[i].begin(), C[i].end());
    }
    return C;
}

// =============================================================
// DP COUNTING
// =============================================================
int countStrings(string r, int L) {
    NFA nfa = buildRegex(r);
    int N = nfa.trans.size();

    auto closure = computeClosure(nfa);

    using BS = bitset<800>;
    unordered_map<unsigned long long,long long> dp, nxt;

    BS startSet;
    for (int x : closure[nfa.start]) startSet.set(x);
    dp[startSet.to_ullong()] = 1;

    auto moveSet = [&](const BS &st, int c) {
        BS mid, res;
        for (int u=0;u<N;u++) if (st[u]) {
            for (int v : nfa.trans[u][c]) mid.set(v);
        }
        for (int u=0;u<N;u++) if (mid[u]) {
            for (int v : closure[u]) res.set(v);
        }
        return res;
    };

    for (int i=0;i<L;i++) {
        nxt.clear();
        for (auto &p : dp) {
            BS S = BS(p.first);
            long long val = p.second;

            for (int c=0;c<2;c++) {
                BS T = moveSet(S, c);
                if (T.any()) {
                    nxt[T.to_ullong()] = (nxt[T.to_ullong()] + val) % MOD;
                }
            }
        }
        dp.swap(nxt);
    }

    long long ans = 0;
    for (auto &p : dp) {
        BS S = BS(p.first);
        if (S[nfa.end]) ans = (ans + p.second) % MOD;
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        string r = first_multiple_input[0];

        int l = stoi(first_multiple_input[1]);

        int result = countStrings(r, l);

        fout << result << "\n";
    }

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
 1. 6             <no of gene types>
 2. a b c aa d b  <gene types array>
 3. 1 2 3 4 5 6   <health values array>
 4. 3             <no strands to test ↓>
 5. 1 5 caaab     <types index range, strand to test>
 6. 0 4 xyz
 7. 2 4 bcdybc

Output:
 6. 0 19          <min and max health values among tested strands>
*/

// 𝗡𝗼𝘁𝗲𝘀:

// 𝗔𝗵𝗼-𝗖𝗼𝗿𝗮𝘀𝗶𝗰𝗸: Algorithm finds all words in O(n + m + z) time where z is total number of occurrences of words in text. 

// Used Aho-Corasick algorithm to efficiently find all occurrences of multiple patterns (genes) in the given strands.
// - Constructed a Trie to store the genes and built failure links for efficient searching.
// - For each strand, traversed the Trie while calculating health based on the specified gene index range.
//https://www.geeksforgeeks.org/dsa/aho-corasick-algorithm-pattern-searching/
