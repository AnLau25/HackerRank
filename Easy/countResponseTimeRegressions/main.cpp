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
 * Complete the 'countResponseTimeRegressions' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY responseTimes as parameter.
 */

int countResponseTimeRegressions(vector<int> responseTimes) {
    if(responseTimes.size()<2) return 0;
    
    int abv = 0;
    double sum = responseTimes[0];
    
    for (int i = 1; i<responseTimes.size(); i++){
        double avr = sum/i;
        
        if(responseTimes[i]>avr){
            abv++;
        }
        
        sum+=responseTimes[i];
    }
    
    return abv;
}

int main()
{
    string responseTimes_count_temp;
    getline(cin, responseTimes_count_temp);

    int responseTimes_count = stoi(ltrim(rtrim(responseTimes_count_temp)));

    vector<int> responseTimes(responseTimes_count);

    for (int i = 0; i < responseTimes_count; i++) {
        string responseTimes_item_temp;
        getline(cin, responseTimes_item_temp);

        int responseTimes_item = stoi(ltrim(rtrim(responseTimes_item_temp)));

        responseTimes[i] = responseTimes_item;
    }

    int result = countResponseTimeRegressions(responseTimes);

    cout << result << "\n";

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