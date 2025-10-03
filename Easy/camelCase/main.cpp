#include <iostream>
#include <vector>
#include <string>
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

/*
 * Complete the 'camelCase' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int camelCase(string s) {
    int humps = 1;
    
    for (char c : s) {
        if (isupper(c)) {
            humps++;
        } 
    }
    
    return humps;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = camelCase(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/* 
Input format:
 1. 20 23 6 <range start, range end, mod>

Output:
 2. 2 <no of beutiful days>
*/