#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <queue>
#include <array>
#include <map>
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

const long long MOD = 1000000007;

struct Node {
    char op; // 'a', 'b', '|', '.', '*'
    Node *l, *r; // left and right children for operators
    Node(char c): op(c), l(NULL), r(NULL) {}
};

string s;
int pos;

// ------------ PARSER ------------

Node* parseRegex();
Node* parseAlt();
Node* parseConcat();
Node* parseRepeat();
Node* parseBase();

Node* parseRegex() { return parseAlt(); }

Node* parseAlt() {
    Node* left = parseConcat();
    while (pos < (int)s.size() && s[pos] == '|') {
        pos++;
        Node* p = new Node('|');
        p->l = left;
        p->r = parseConcat();
        left = p;
    }
    return left;
}

Node* parseConcat() {
    // sequence of repeats
    Node* left = parseRepeat();
    while (pos < (int)s.size() && (s[pos]=='a' || s[pos]=='b' || s[pos]=='(')) {
        Node* p = new Node('.');
        p->l = left;
        p->r = parseRepeat();
        left = p;
    }
    return left;
}

Node* parseRepeat() {
    // base followed by zero or more '*'
    Node* n = parseBase();
    while (pos < (int)s.size() && s[pos] == '*') {
        Node* p = new Node('*');
        p->l = n;
        pos++;
        n = p;
    }
    return n;
}

Node* parseBase() {
    // single character or parenthesized expression
    if (s[pos] == 'a' || s[pos] == 'b') {
        Node* n = new Node(s[pos]);
        pos++;
        return n;
    }
    if (s[pos] == '(') {
        pos++;
        Node* inside = parseRegex();
        pos++; // ')'
        return inside;
    }
    return NULL; // should not reach here
}

// ------------ NFA CONSTRUCTION ------------

struct Frag { int st, en; };

int newState(vector<vector<int>>& eps, vector<array<vector<int>,2>>& tr) {
    eps.push_back({});
    tr.push_back({vector<int>(), vector<int>()});
    return eps.size() - 1;
}

Frag buildNFA(Node* n,
              vector<vector<int>>& eps,
              vector<array<vector<int>,2>>& tr) {
    if (!n) return {-1, -1};

    if (n->op == 'a' || n->op == 'b') {
        int s = newState(eps, tr);
        int t = newState(eps, tr);
        int idx = (n->op == 'a' ? 0 : 1);
        tr[s][idx].push_back(t);
        return {s, t};
    }

    if (n->op == '|') {
        Frag L = buildNFA(n->l, eps, tr);
        Frag R = buildNFA(n->r, eps, tr);
        int s = newState(eps, tr);
        int t = newState(eps, tr);
        eps[s].push_back(L.st);
        eps[s].push_back(R.st);
        eps[L.en].push_back(t);
        eps[R.en].push_back(t);
        return {s, t};
    }

    if (n->op == '.') {
        Frag A = buildNFA(n->l, eps, tr);
        Frag B = buildNFA(n->r, eps, tr);
        eps[A.en].push_back(B.st);
        return {A.st, B.en};
    }

    if (n->op == '*') {
        Frag A = buildNFA(n->l, eps, tr);
        int s = newState(eps, tr);
        int t = newState(eps, tr);
        eps[s].push_back(A.st);
        eps[s].push_back(t);
        eps[A.en].push_back(A.st);
        eps[A.en].push_back(t);
        return {s, t};
    }

    return {-1,-1};
}

// ------------ DFA (subset construction) ------------

using Bits = vector<uint64_t>;

Bits toBits(const vector<int>& v, int N) {
    Bits b((N + 63) / 64);
    for (int x : v) b[x/64] |= (1ULL << (x%64));
    return b;
}

vector<int> epsilonClosure(int start,
                           const vector<vector<int>>& eps) {
    int N = eps.size();
    vector<char> vis(N,0);
    queue<int> q;
    q.push(start);
    vis[start] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : eps[u]) {
            if (!vis[v]) { vis[v] = 1; q.push(v); }
        }
    }

    vector<int> res;
    for (int i = 0; i < N; i++)
        if (vis[i]) res.push_back(i);
    return res;
}

vector<int> epsilonClosureSet(const vector<int>& st,
                              const vector<vector<int>>& eps) {
    int N = eps.size();
    vector<char> vis(N,0);
    queue<int> q;

    for (int u : st) {
        if (!vis[u]) { vis[u] = 1; q.push(u); }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : eps[u])
            if (!vis[v]) { vis[v] = 1; q.push(v); }
    }

    vector<int> res;
    for (int i = 0; i < N; i++)
        if (vis[i]) res.push_back(i);
    return res;
}

// ------------ MATRIX EXPONENTIATION ------------

using Mat = vector<vector<long long>>;

Mat matMul(const Mat& A, const Mat& B) {
    int n = A.size();
    Mat C(n, vector<long long>(n,0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (A[i][k])
                for (int j = 0; j < n; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

Mat matPow(Mat base, long long e) {
    int n = base.size();
    Mat r(n, vector<long long>(n,0));
    for (int i = 0; i < n; i++) r[i][i] = 1;

    while (e) {
        if (e & 1) r = matMul(r, base);
        base = matMul(base, base);
        e >>= 1;
    }
    return r;
}

// ------------ TOP-LEVEL FUNCTION ------------

int countStrings(string r, int L) {
    // build parse tree
    s.clear();
    for (char c : r) if (c!=' ') s += c;
    pos = 0;

    Node* root = parseRegex();

    // build NFA
    vector<vector<int>> eps;
    vector<array<vector<int>,2>> tr;
    Frag f = buildNFA(root, eps, tr);
    int N = eps.size();

    // subset-construction (DFA)
    map<Bits,int> id;
    vector<Bits> states;
    vector<int> accept;

    // start closure
    vector<int> st0 = epsilonClosure(f.st, eps);
    Bits b0 = toBits(st0, N);
    id[b0] = 0;
    states.push_back(b0);
    accept.push_back(find(st0.begin(), st0.end(), f.en) != st0.end() ? 1 : 0);

    queue<Bits> q;
    q.push(b0);

    vector<array<int,2>> dfatrans;
    dfatrans.push_back({-1,-1});

    while (!q.empty()) {
        Bits u = q.front(); q.pop();
        int ui = id[u];

        // decode
        vector<int> ulist;
        for (int i = 0; i < N; i++)
            if ( (u[i/64] >> (i%64)) & 1ULL ) ulist.push_back(i);

        for (int c = 0; c < 2; c++) {
            vector<int> move;
            vector<char> vis(N,0);

            for (int x : ulist)
                for (int y : tr[x][c])
                    if (!vis[y]) { vis[y] = 1; move.push_back(y); }

            vector<int> clo = epsilonClosureSet(move, eps);
            Bits nb = toBits(clo, N);

            if (!id.count(nb)) {
                int k = states.size();
                id[nb] = k;
                states.push_back(nb);
                accept.push_back(find(clo.begin(), clo.end(), f.en) != clo.end());
                dfatrans.push_back({-1, -1});
                q.push(nb);
            }
            dfatrans[ui][c] = id[nb];
        }
    }

    int M = states.size();

    // Build transition matrix
    Mat A(M, vector<long long>(M,0));
    for (int i = 0; i < M; i++) {
        A[i][dfatrans[i][0]] = (A[i][dfatrans[i][0]] + 1) % MOD;
        A[i][dfatrans[i][1]] = (A[i][dfatrans[i][1]] + 1) % MOD;
    }

    if (L == 0) return accept[0];

    Mat AL = matPow(A, L);

    long long ans = 0;
    for (int i = 0; i < M; i++)
        if (accept[i])
            ans = (ans + AL[0][i]) % MOD;

    return ans;
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

        string r = first_multiple_input[0];

        int l = stoi(first_multiple_input[1]);

        int result = countStrings(r, l);

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
 1. 3                   <number of test cases>
 2. ((ab)|(ba)) 2       <regex and length L ↓>
 3. ((a|b)*) 5  
 4. ((a*)(b(a*))) 100

Output:
 5. 2                   <number of strings of length L that match the regex>  
 6. 32  
 7. 100
*/

// 𝗡𝗼𝘁𝗲𝘀:
// - The regex supports characters 'a', 'b', alternation '|', concatenation (implicit),
//   Kleene star '*', and grouping with parentheses '()'.
// - The approach involves parsing the regex into a syntax tree, constructing an NFA,
//   converting it to a DFA using subset construction, and then using matrix exponentiation
//   to count the number of accepted strings of length L efficiently.
// - The time complexity is O(M^3 log L), where M is the number of DFA states.
// 𝗥𝗲𝗳𝗲𝗿𝗲𝗻𝗰𝗲𝘀:
// - https://www.geeksforgeeks.org/theory-of-computation/introduction-of-finite-automata/
// - https://www.geeksforgeeks.org/theory-of-computation/designing-non-deterministic-finite-automata-set-3/
// - https://www.geeksforgeeks.org/dsa/matrix-exponentiation/
