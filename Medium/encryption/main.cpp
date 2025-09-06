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
 * Complete the 'encryption' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string encryption(string s) {
     s.erase(remove(s.begin(), s.end(), ' '), s.end());
    int L = s.size();

    int rows = floor(sqrt(L));
    int cols = ceil(sqrt(L));
    if (rows * cols < L) {
        rows = cols;
    }

    vector<string> result;
    for (int c = 0; c < cols; c++) {
        string word = "";
        for (int r = 0; r < rows; r++) {
            int idx = r * cols + c;
            if (idx < L) {
                word += s[idx];
            }
        }
        result.push_back(word);
    }

    string encoded = "";
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) encoded += " ";
        encoded += result[i];
    }

    return encoded;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = encryption(s);

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
 1. 6 7 3 <rows = 6, columns = 7, sec = 3>
 2. ....... <grid made of string arrays ↓>         
 3. ...O...                
 4. ....O..
 5. .......
 6. OO.....
 7. OO.....

Output:
 8. OOO.OOO
 9. OO...OO
10. OOO...O
11. ..OO.OO
12. ...OOOO
13. ...OOOO
*/