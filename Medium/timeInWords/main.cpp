#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'timeInWords' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER h
 *  2. INTEGER m
 */

string timeInWords(int h, int m) {
    string time = "";
    map<int, string> numerals = {{1, "one"}, 
                                {2, "two"}, 
                                {3, "three"},
                                {4, "four"},
                                {5, "five"},
                                {6, "six"},
                                {7, "seven"},
                                {8, "eight"},
                                {9, "nine"},
                                {10, "ten"},
                                {11, "eleven"},
                                {12, "twelve"},
                                {13, "thirteen"},
                                {14, "fourteen"},
                                {15, "fifteen"},
                                {16, "sixteen"},
                                {17, "seventeen"},
                                {18, "eighteen"},
                                {19, "nineteen"},
                                {20, "twenty"}};
    
    time += m>30? numerals[h+1] : numerals[h];
    
    if(m==0) time = time + " o' clock";
    
    if(m==15) time =  "quarter past " + time;
    
    if(m==30) time = "half past " + time;
    
    if((m>0 && m<15) || (m>15 && m<30)) time = (m==1? numerals[m] + " minute past " : (((m)>20? numerals[20] + " " + numerals[m-20] : numerals[60-m]) + " minutes past ")) + time;
    
    if(m==45) time = "quarter to " + time;
    
    if(m>45 || (m>30 && m<45)) time = (60-m==1 ? numerals[m] + " minute to " :  (((60-m)>20? numerals[20] + " " + numerals[60-m-20] : numerals[60-m])  + " minutes to ")) + time;
    
    return time;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string h_temp;
    getline(cin, h_temp);

    int h = stoi(ltrim(rtrim(h_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    string result = timeInWords(h, m);

    cout << result << "\n";

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
1. 6  <hour>
2. 35 <minutes>

Output:
3. twenty five minutes to seven <time in words>
*/