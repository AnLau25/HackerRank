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
 * Complete the 'anagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int anagram(string s) {
    if(s.size()%2!=0) return -1;
    
    string halfa = s.substr(0, (s.size()/2));
    string halfb = s.substr(s.size()/2);
    vector<int> freq(26, 0);
    
    
    for (char c : halfa) freq[c - 'a']++;
   
    for (char c : halfb) freq[c - 'a']--;
    
    int modifs = 0;
    for (int f : freq) {
        if (f > 0) modifs += f;
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

        int result = anagram(s);

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
 1. 6      <no of test cases>
 2. aaabbb
 3. ab
 4. abc
 5. mnop
 6. xyyx
 7. xaxbbbxx

Output:
 8. 3
 9. 1
10. -1
11. 2
12. 0
13. 1
*/