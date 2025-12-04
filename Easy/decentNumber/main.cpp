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

/*
 * Complete the 'decentNumber' function below.
 *
 * The function accepts INTEGER n as parameter.
 */
 
void decentNumber(int n) {
    for (auto i = 0; i <= n; ++i) {
        if (i % 5 == 0 && (n - i) % 3 == 0) {
            cout << string(n - i, '5') << string(i, '3') << endl;
            return;
        }
    }
    cout << -1 << endl;
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        decentNumber(n);
    }

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

/* 
Input format:
 1. 4       <t = 4>
 2. 1       <n = 1 (first test case)>
 3. 3       <n = 3 (second test case)>
 4. 5
 6. 11

Output:
 7. -1
 8. 555
 9. 33333
10. 55555533333

Explanation:
 For each test case, the function finds the largest decent number with n digits.
 A decent number has:
  - Digits only 3's and 5's
  - Number of 3's is divisible by 5
  - Number of 5's is divisible by 3
 If no such number exists, it prints -1.
*/