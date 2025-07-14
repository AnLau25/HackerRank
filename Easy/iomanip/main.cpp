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
 1. 1 <number of tests> 
 2. 100.345 2006.008 2331.41592653498 <values of a, b and c>

Output:
 3. 0x64        
 4. _______+2006.01  
 5. 331415927E+03
*/