#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

/*
 * Complete the 'superReducedString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string superReducedString(string s) {
    
    for(int i = 0; i<s.size(); i++){
        
        if(((i+1)<s.size()) && (s[i]==s[i+1])){
            s.erase(i,2);
            return superReducedString(s);
        }   
    }
    
    if(s.empty()){
        return "Empty String";
    }
    
    return s;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = superReducedString(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/* 
Input format:
 1. aaabccddd <string to reduce>

Output:
 2. abd <reduced string or "Empty String" if fully reduced>
*/