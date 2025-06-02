#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <functional>
#include <queue>
#include <map>
using namespace std;

/*
 * Complete the 'pangrams' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string pangrams(string s) {
    map<char,int> found;
    
    for (char c : s){
        
        if(std::isalpha(c)){
        
            if (std::isupper(c)){
                c = tolower(c);
            }
            
            if(found.find(c)==found.end()){
                found[c]=1;
            }
        }
    }
    
    if(found.size()>=26){
        return "pangram";
    }
    
    return "not pangram";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    std::cout<<pangrams(s);

    //fout << result << "\n";

    //fout.close();

    return 0;
}


/* 
Input format:
 1. We promptly jusged antique ivory buckles for the next prize <string to evalueate>

Output:
2. panagram <or not panagram, test by taking out "next">
*/