#include <iostream>
#include <vector>
#include <string>
#include <sstream>    // for split
#include <iomanip> 
using namespace std;

/*
 * Complete the 'marsExploration' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int marsExploration(string s) {
    int errs = 0;
    
    for (size_t i = 0; i < s.size(); i += 3) {
        string sos = s.substr(i, 3);
        
        if(sos!="SOS"){
            if(sos[0]!='S'){
                errs++; 
            }
            if(sos[1]!='O'){
                errs++; 
            }
            if(sos[2]!='S'){
                errs++; 
            }
        }
    }
    return errs;

}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = marsExploration(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/* 
Input format:
 1. SOSSPSSQSSOR <Rover message string>

Output:
 2. 3            <number of errors>
*/