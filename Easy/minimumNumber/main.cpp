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
 * Complete the 'minimumNumber' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING password
 */

int minimumNumber(int n, string password) {
    // Return the minimum number of characters to make the password strong
    int missing = 4;
    bool num = false, low = false, upr = false, chr = false;
    bool all = num && low && upr && chr;
    
    for(char c : password){
        
        if (!num && isdigit(c)) {
            num = true;
            missing--;
        }
        
        if (!low && islower(c)){
           low = true;
           missing--; 
        }
        
        if (!upr && isupper(c)){
            upr = true;
            missing--;
        }
        
        if (!chr && (!isalnum(c) && !isspace(c))) {
            chr = true;
            missing--;
        }
        
        if (all) return 0;      
    }
    
    if (password.size()<6) return max(int(6-password.size()),missing);
    
    return missing;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string password;
    getline(cin, password);

    int answer = minimumNumber(n, password);

    cout << answer << "\n";

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
 1. 3    <length of attempted password>
 2. Ab1  <attempted password>

Output:
 2. 3    <minimum number of changes to make the password valid>
*/