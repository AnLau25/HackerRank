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

// Definition of a Trie node
struct TrieNode {
    bool isEnd; // Indicates if a word ends at this node
    std::unordered_map<char, TrieNode*> children; // Map of child nodes for each character

    TrieNode() : isEnd(false) {} // Constructor initializes isEnd to false
};

// Inserts a word into the Trie
// Returns true if there's a prefix conflict (either this word is a prefix of another or vice versa)
bool insert(TrieNode* root, const std::string& word) {
    TrieNode* current = root;

    for (char c : word) {
        if (current->isEnd) {
            return true; 
            // An existing word ends here, making it a prefix of the current word
        }
        if (!current->children.count(c)) {
            current->children[c] = new TrieNode(); // Create new node if character path doesn't exist
        }
        current = current->children[c]; // Move to the next node in the path
    }

    // If word already exists or this word is a prefix of another existing word
    //or if the end of current has smt after
    //Like if it has been found that smnt comes after, meaning that it is part of another word 
    if (current->isEnd || !current->children.empty()) {
        return true;
    }

    current->isEnd = true; // Mark the end of the word
    return false; // No prefix conflict
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
1. 4 <number or strings>
2. ab <space separated array>
3. ac
4. acdc
5. abcd

Output:
BAD SET
acdc <cause it comes before abcd>
*/