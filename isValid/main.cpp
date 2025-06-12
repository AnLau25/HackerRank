#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'lonelyinteger' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */
string isValid(string s) {
    map<char, int> charMap;
    map<int, int> freq;
    
    for(char c : s){
        charMap[c]++;
    }
    
    for (auto& pair : charMap) {
        freq[pair.second]++;
    }
    
    if(freq.size()==1){
        return "YES";
    }
    
    if(freq.size()==2){
        auto it = freq.begin();
        int f1 = it->first, count1 = it->second;
        ++it;
        int f2 = it->first, count2 = it->second;
        
        if ((f1 == 1 && count1 == 1) || (f2 == 1 && count2 == 1)) {
            return "YES";
        }

        if ((abs(f1 - f2) == 1) && (count1 == 1 || count2 == 1)) {
            return "YES";
        }
    }
    
    return "NO";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    std::cout<<result<<"\n";

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
1. aabbcd <string to test>

Output:
2. NO <not a valid Sherlock Holmes>
*/