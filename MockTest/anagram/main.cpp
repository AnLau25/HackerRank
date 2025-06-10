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

int anagram(string s) {
    int len = s.size();
    if (len % 2 != 0 || len == 0) return -1;

    int mid = len / 2;
    vector<int> count1(26, 0), count2(26, 0);

    for (int i = 0; i < mid; i++) {
        count1[s[i] - 'a']++;
        count2[s[i + mid] - 'a']++;
    }

    int changes = 0;
    for (int i = 0; i < 26; i++) {
        if (count1[i] > count2[i]) {
            changes += count1[i] - count2[i];
        }
    }

    return changes;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = anagram(s);

        std::cout<<result<<"\n";
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
1. 6 <length of array>
2. 5 5 6 7 6 5 <space separated array>
*/