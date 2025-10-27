#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct dnastrand {
    int start;
    int end;
    string dna;

    dnastrand(int _start, int _end, string _dna)
        : start(_start), end(_end), dna(_dna) {}
};

struct TrieNode {
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
};

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
    
    genepool pool(genes, health);
    pool.sortGenes(strands);
    
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
 1. 4 4 2        <rows m = 4, columns n = 4, rotation factor r = 2>
 2. 1 2 3 4      <matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]>
 3. 5 6 7 8
 4. 9 10 11 12
 5. 13 14 15 16

Output:
 6. 3 4 8 12     <matrix rotated by r ↓>
 7. 2 11 10 16
 8. 1 7 6 15
 9. 5 9 13 14
*/