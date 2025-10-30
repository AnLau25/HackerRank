#include <iostream>
#include <map>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

/*
 * Complete the 'gameOfThrones' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string gameOfThrones(string s) {
    bool univ = false;
    map<char, int> charcount;
    
    for(char c : s){
        charcount[c]+=1;
    }
    
    for(auto [key, val] : charcount){
        if(val%2!=0&&univ==false){
            univ = true;
        }else if(val%2!=0&&univ==true){
            return "NO";
        }
    }
    
    return "YES";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = gameOfThrones(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/* 
Input format:
 1. aaabbbb <string to test>

Output:
 2. YES     <if can be rearranged to palindrome, else NO>
*/