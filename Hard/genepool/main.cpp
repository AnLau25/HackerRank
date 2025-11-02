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
struct dnastrand {
    int start;
    int end;
    string dna;

    dnastrand(int _start, int _end, string _dna)
        : start(_start), end(_end), dna(_dna) {}
};

struct TrieNode {
    //Max number or characters in lowercase English alphabet
    TrieNode* next[26] = {nullptr};
    TrieNode* fail = nullptr;
    TrieNode* outputLink = nullptr;
    vector<int> output;
};

class genepool {
    public:
    
    vector<string> genes;
    vector<int> health;
    vector<long long> strandsHp;
    TrieNode* root;

    genepool(vector<string> _genes, vector<int> _health)
        : genes(move(_genes)), health(move(_health)) {
        root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }

    void buildTrie() {
        for (int i = 0; i < genes.size(); ++i) {
            TrieNode* node = root;
            for (char c : genes[i]) {
                int idx = c - 'a';
                if (!node->next[idx]) node->next[idx] = new TrieNode();
                node = node->next[idx];
            }
            node->output.push_back(i);
        }
    }

    void buildFailureLinks() {
        queue<TrieNode*> q;
        root->fail = root;

        for (int i = 0; i < 26; ++i) {
            if (root->next[i]) {
                root->next[i]->fail = root;
                root->next[i]->outputLink = root;
                q.push(root->next[i]);
            }
        }

        while (!q.empty()) {
            TrieNode* current = q.front(); q.pop();

            for (int i = 0; i < 26; ++i) {
                TrieNode* child = current->next[i];
                if (!child) continue;

                TrieNode* f = current->fail;
                while (f != root && !f->next[i]) f = f->fail;
                if (f->next[i] && f->next[i] != child)
                    child->fail = f->next[i];
                else
                    child->fail = root;

                child->outputLink = !child->fail->output.empty() ? child->fail : child->fail->outputLink;

                q.push(child);
            }
        }
    }

    void insert_strands(int start, int end, const string& dna) {
        long long hp = 0;
        TrieNode* node = root;

        for (char c : dna) {
            int idx = c - 'a';
            while (node != root && !node->next[idx])
                node = node->fail;

            if (node->next[idx])
                node = node->next[idx];

            for (TrieNode* temp = node; temp != nullptr; temp = temp->outputLink) {
                for (int geneIdx : temp->output) {
                    if (geneIdx >= start && geneIdx <= end)
                        hp += health[geneIdx];
                }
            }
        }

        strandsHp.push_back(hp);
    }

    void sortGenes(const vector<dnastrand>& strands) {
        for (const auto& strand : strands)
            insert_strands(strand.start, strand.end, strand.dna);

        sort(strandsHp.begin(), strandsHp.end());
        cout << strandsHp.front() << " " << strandsHp.back();
    }
};*/

/* Aho-Corasick: Simplified */
const int maxs = INT16_MAX;
const int maxc = 26;

int out[maxs];

int f[maxs];

int g[maxs][maxc];

struct dnastrand {
    int start;
    int end;
    string dna;

    dnastrand(int _start, int _end, string _dna)
        : start(_start), end(_end), dna(_dna) {}
};

int matchingMachine(string arr[], int k){
    memset(out, 0, sizeof out);
    memset(g, -1, sizeof g);
    
    int states = 1;
    
    for(int i = 0; i<k; ++i){
        const string &word = arr[i];
        int currentState = 0;
        
        for (int j = 0; j<word.size(); j++){
            int ch = word[j] - 'a';
            if (g[currentState][ch] == -1){
                g[currentState][ch] = states++;
            }
            currentState = g[currentState][ch];
        }
        out[currentState] |= (1 << i);
    }

    for (int ch = 0; ch < maxc; ++ch){
        if (g[0][ch] == -1){
            g[0][ch] = 0;
        }
    }

    memset(f, -1, sizeof f);

    queue<int> q;

    for(int ch = 0; ch < maxc; ++ch){
        if (g[0][ch] != 0){
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }

    while(!q.empty()){
        int state = q.front();
        q.pop();

        for(int ch = 0; ch < maxc; ++ch){
            if (g[state][ch] != -1){
                int failure = f[state];

                while (g[failure][ch] == -1){
                    failure = f[failure];
                }

                failure = g[failure][ch];
                f[g[state][ch]] = failure;
                out[g[state][ch]] |= out[failure];
                q.push(g[state][ch]);
            }
        }
    }
    
    return states;
}

int searchGenes(vector<string> genes, vector<int> health, dnastrand strand) {
    int currentState = 0;
    int healthSum = 0;

    for (int i = 0; i < strand.dna.size(); ++i) {
        int ch = strand.dna[i] - 'a';

        while (g[currentState][ch] == -1) {
            currentState = f[currentState];
        }

        currentState = g[currentState][ch];

        for (int j = 0; j < genes.size(); ++j) {
            if (out[currentState] & (1 << j)) {
                if (j >= strand.start && j <= strand.end) {
                    healthSum += health[j];
                }
            }
        }
    }

    return healthSum;
}

void sortGenes (vector<dnastrand> strands, vector<string> genes, vector<int> health) {
    vector<int> strandsHp;    

    for(auto strand : strands){
        strandsHp.push_back(searchGenes(genes, health, strand));
    }

    sort(strandsHp.begin(), strandsHp.end());

    cout<<strandsHp[0]<<" "<<strandsHp.back();
}



/*Main*/
int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split(rtrim(genes_temp_temp));

    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<string> health_temp = split(rtrim(health_temp_temp));

    vector<int> health(n);

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);

        health[i] = health_item;
    }

    string s_temp;
    getline(cin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));
    vector<dnastrand> strands;

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int first = stoi(first_multiple_input[0]);

        int last = stoi(first_multiple_input[1]);

        string d = first_multiple_input[2];
        
        dnastrand strand(first, last, d);
        
        strands.push_back(strand);
    }

    sortGenes(strands, genes, health);

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
