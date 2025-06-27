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
 * Complete the 'highestValuePalindrome' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER n
 *  3. INTEGER k
 */

string highestValuePalindrome(string s, int n, int k) {
    int left = 0, right = n - 1;
    vector<bool> changed(n, false);

    while (left < right) {
        if (s[left] != s[right]) {
            s[left] = s[right] = max(s[left], s[right]);
            changed[left] = changed[right] = true;
            k--;
        }
        left++;
        right--;
    }

    if (k < 0) return "-1"; 

    left = 0, right = n - 1;
    while (left <= right) {

        if (left == right) { // If at the middle, make 9
            if (k > 0 && s[left] != '9') {
                s[left] = '9';
                k--;
            }

        } else {
            if (s[left] != '9') {  
                if (changed[left] || changed[right]) {
                    // If this mas already modified prior
                    if (k >= 1) {
                        // Turn both numbers to 9, but only k--, since we substracted 1 when making equal
                        s[left] = s[right] = '9';
                        k--;
                    }
                } else if (k >= 2) { // Else, tunr to 9 and k-2
                    s[left] = s[right] = '9';
                    k -= 2;
                }
            }
        }
        left++;
        right--;
    }

    return s;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

    cout<<result<<"\n";

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
1. 6 3 <length of String, no of allowed modifications>
2. 092282 <string>

3. 992299 <maximized palindrome>
*/