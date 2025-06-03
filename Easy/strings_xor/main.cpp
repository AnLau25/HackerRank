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
 * Debug the given function strings_xor to find the XOR of the two given strings appropriately.
 * You can modify at most three lines in the given code and you cannot add or remove lines to the code.
 * 
 * The function is expected to return a STRING.
 * The function accepts 2 STRINGS of identical length a as parameter.
 */

string strings_xor(string s, string t) {
    
    string res = "";
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == t[i])
            res += '0';
        else
            res += '1';
    }
    
    return res;
}

int main() {
    string s, t;
    cin >> s >> t;
    cout << strings_xor(s, t) << endl;
    return 0;
}

/* 
Input format:
1. 10101 <binary number as string>
2. 00101 <binary number as string>

Output:
3. 10000 <result of xOR operation>

s | t | xOR
1 | 0 |  1
0 | 0 |  0
1 | 1 |  0
0 | 0 |  0
1 | 1 |  0
*/