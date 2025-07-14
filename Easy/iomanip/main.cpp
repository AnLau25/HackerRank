#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    long t;
    cin>>t;
    
    while (t-->0) {
        double a, b, c;
        cin>>a>>b>>c;
        
        cout<< "0x"<<hex<<nouppercase<<(long long)a<<endl;
        
        cout<< setfill('_')           // Fills missing space
            << setw(15)               // Sets max width
            << showpos                // enables showpos globaly
            << fixed<<setprecision(2) //sets presition to 2 decimals after '.'
            << b<<endl;
        
        cout<< noshowpos 
            << scientific<<uppercase
            << setprecision(9)
            << c <<endl;
    }

         
    return 0;
}


/*
Test:
 1. 8 <elements in vector>
 2. 1 1 2 2 6 9 9 15 <space separated array>
 3. 4 <Numeber of queries>
 4. 1 <Queries ↓>
 5. 4
 6. 9
 7. 15

Output:
 9. Yes 1
10. No 5
11. Yes 6
12. Yes 8
*/