#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'counterGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts LONG_INTEGER n as parameter.
 */
string counterGame(long n) {
    int count = 1;
    
    if(n==1){
        return "Richard"; 
    }
    
    while (n>1) {
        double logValue = std::log2(n);
        int logAttempt = std::log2(n);
        
        if(logValue==logAttempt){
            n = n/2;
        }
        if(logValue!=logAttempt){
            n = n - std::pow(2,logAttempt);
        }
        
        count++;
    }
    
    if(count%2!=0){
        return "Richard";
    }

    return "Louise";
}// This is silly, oh so silly, I know there is a better way... but imma not gona look for it Ɛ( · — ·)3

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        long n = stol(ltrim(rtrim(n_temp)));

        std::cout<<counterGame(n)<<std::endl;

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
1. 1 <# of tests>
2. 132 <n=132>
*/