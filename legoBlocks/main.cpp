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
 * Complete the 'legoBlocks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */
const int MOD = 1000000007;

int mod_pow(int base, int exp, int mod) {
    long long result = 1, b = base;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * b) % mod;
        b = (b * b) % mod;
        exp /= 2;
    }
    return result;
}

int legoBlocks(int n, int m) {
    vector<int> row_ways(m + 1, 0);
    row_ways[0] = 1;

    // Count ways to build one row of width w
    for (int width = 1; width <= m; ++width) {
        for (int block = 1; block <= 4; ++block) {
            if (width - block >= 0)
                row_ways[width] = (row_ways[width] + row_ways[width - block]) % MOD;
        }
    }

    // Total combinations: raise row_ways[w] to power n
    vector<int> total_ways(m + 1, 0);
    for (int i = 1; i <= m; ++i)
        total_ways[i] = mod_pow(row_ways[i], n, MOD);

    // Compute solid walls (no vertical cracks)
    vector<int> solid_ways(m + 1, 0);
    solid_ways[0] = 1;
    for (int i = 1; i <= m; ++i) {
        solid_ways[i] = total_ways[i];
        for (int j = 1; j < i; ++j) {
            long long sub = ((long long)solid_ways[j] * total_ways[i - j]) % MOD;
            solid_ways[i] = (solid_ways[i] - sub + MOD) % MOD;
        }
    }

    return solid_ways[m];
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

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        std::cout<<legoBlocks(n, m)<<std::endl;

        //fout << result << "\n";
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