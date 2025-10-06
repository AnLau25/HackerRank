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

/*
 * Complete the 'alternate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */
int alternating(const string& str, char a, char b) {
    char prev = 0;
    int len = 0;
    for (char c : str) {
        if (c != a && c != b) continue; 
        if (c == prev) return -1;       
        prev = c;
        len++;
    }
    return len;
}

int alternate(string s) {
    set<char> str_set(s.begin(), s.end());
    vector<char> uniques;
    
    copy(str_set.begin(), str_set.end(), std::back_inserter(uniques));
    int bgs = 0;
    
    for(int i = 0; i<uniques.size(); i++){
        for (int j = i+1; j<uniques.size(); j++) {
            int len = alternating(s, uniques[i], uniques[j]);
            if(len>0 && len>bgs){
                bgs = len;
            }
        } 
    }
    
    return bgs;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

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
 1. 20 23 6 <range start, range end, mod>

Output:
 2. 2 <no of beutiful days>
*/