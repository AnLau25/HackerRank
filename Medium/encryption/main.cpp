#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cmath>
#include <iomanip> 
using namespace std;

/*
 * Complete the 'encryption' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string encryption(string s) {
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
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = encryption(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}



/* 
Input format:
 1. haveaniceday <sentence without spaces>

Output:
 2. hae and via ecy <matrix encrypted sentence>
*/