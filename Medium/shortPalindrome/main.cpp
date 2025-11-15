#include <algorithm>
#include <iostream>
#include <stack>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

/*
 * Complete the 'shortPalindrome' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */
static const int MOD = 1000000007;

long shortPalindrome(string s) {
    long tuples = 0;
    vector<long> char1(26, 0);
    vector<long> char2(26*26, 0);
    vector<long> char3(26*26, 0);
    long charn = 0;
    long charc = 0;
    
    for(char c : s){
        charn = c - 97;
        charc = charn;
        tuples = (tuples%MOD) + char3[charc];
        for(int i = 0; i<26; i++){
            char3[i] += char2[charc];
            char2[charc] += char1[i];
            charc += 26;
        }
        char1[charn]++;
    }
    
    return tuples%MOD;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = shortPalindrome(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/* 
Input format:
 1. kkkkkkz         <strings to test>

Output:
 2. 15              <number of abba palindromic tuples that can be formed>
*/
