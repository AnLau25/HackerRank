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
 * Complete the 'kaprekarNumbers' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER p
 *  2. INTEGER q
 */

void kaprekarNumbers(int p, int q) {
    bool found = false;

    for (int i = p; i <= q; i++) {
        long long sq = 1LL * i * i;
        string num_str = to_string(sq);

        int len = num_str.length();
        int mid = len / 2;

        long long left = (mid == 0) ? 0 : stoll(num_str.substr(0, mid));
        long long right = stoll(num_str.substr(mid));

        if (left + right == i) {
            found = true;
            cout << i << " ";
        }
    }

    if (!found) cout << "INVALID RANGE";
}

int main()
{
    string p_temp;
    getline(cin, p_temp);

    int p = stoi(ltrim(rtrim(p_temp)));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    kaprekarNumbers(p, q);

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