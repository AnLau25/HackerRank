#include <iostream>
#include <map>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int Q, q, v;
    string name;
    map<string, int> m;
    
    cin>>Q;
    for(; Q>0; Q--){
        cin>>q;
        
        switch (q) {
            case 1:
                cin>>name>>v;
                m[name]+=v;
                break;
            case 2:
                cin>>name;
                m.erase(name);
                break;
            case 3:
                cin>>name;
                if(m.find(name)!=m.end()){
                    cout<<m[name]<<endl;
                }else{
                    cout<<0<<endl;
                }
                break;
        }      
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