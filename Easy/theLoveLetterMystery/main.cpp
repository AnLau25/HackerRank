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
 * Complete the 'theLoveLetterMystery' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int theLoveLetterMystery(string s) {
    int modifs = 0, lft = 0, rgt = s.size()-1;  
    
    while (lft<rgt) {
        int indx = s[lft]<=s[rgt]? rgt : lft; 
        
        while (s[lft]!=s[rgt]) {
            s[indx]--;
            modifs++;
        }
        
        lft++;
        rgt--;
    }
    return modifs;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = theLoveLetterMystery(s);

        cout << result << "\n";
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

/* 
Input format:
 1. 4       <q = 4>
 2. abc     <queries ↓>
 3. abcba
 4. abcd
 5. cba

Output:
 6. 2       <modifs needed to turn to palindrome>
 7. 0
 8. 4
 9. 2
*/