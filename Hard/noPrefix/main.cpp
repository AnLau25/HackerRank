#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <unordered_map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */
struct TrieNode {
    bool isEnd;
    std::unordered_map<char, TrieNode*> children;
    
    TrieNode() : isEnd(false) {}
};

bool insert(TrieNode* root, const std::string& word) {
    TrieNode* current = root;

    for (char c : word) {
        if (current->isEnd) {
            return true; // existing word is a prefix of this one
        }
        if (!current->children.count(c)) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }

    if (current->isEnd || !current->children.empty()) {
        return true; // duplicate word or prefix conflict
    }

    current->isEnd = true;
    return false;
}


void noPrefix(const std::vector<std::string>& words) {
    TrieNode* root = new TrieNode();
    
    for (const std::string& word : words) {
        if (insert(root, word)) {
            std::cout << "BAD SET\n" << word << std::endl;
            return;
        }
    }
    
    std::cout << "GOOD SET" << std::endl;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> words(n);

    for (int i = 0; i < n; i++) {
        string words_item;
        getline(cin, words_item);

        words[i] = words_item;
    }

    noPrefix(words);

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
1. 6 <number or strings>
2. ab <space separated array>
3. ac
4. acdc
5. abcd

Output:
BAD SET
acdc <cause it comes before abcd>
*/