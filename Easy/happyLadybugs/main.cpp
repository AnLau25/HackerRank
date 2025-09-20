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
 * Complete the 'happyLadybugs' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING b as parameter.
 */

string happyLadybugs(string b) {
    
    vector<int> occ(26, 0);
    bool happy = true, underscore = false;
    b = "0"+b+"0";
    for(int i = 1; i < b.size()-1; i++){
        if(b[i] != '_' && b[i] != b[i-1] && b[i] != b[i+1]) happy = false;
        if(b[i] == '_') underscore = true;
        else occ[b[i] - 'A']++;
    }
    if(happy) return "YES";
    if(underscore && find(occ.begin(), occ.end(), 1) == occ.end()) return "YES";
    return "NO";


    return "YES";

}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string g_temp;
    getline(cin, g_temp);

    int g = stoi(ltrim(rtrim(g_temp)));

    for (int g_itr = 0; g_itr < g; g_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string b;
        getline(cin, b);

        string result = happyLadybugs(b);

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
 1. 4       <no of test cases>
 2. 7       <length of string b>
 3. RBY_YBR <string b>
 4. 6
 5. X_Y__X
 6. 2
 7. __
 8. 6
 9. B_RRBR

Output:
10. YES     <if happy ladybugs>
11. NO      <if not all ladydugs are happy>
12. YES
13. YES
*/