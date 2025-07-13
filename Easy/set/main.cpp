#include <iostream>
#include <set>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int Q, q, v;
    set<int> s;
    
    cin>>Q;
    for(; Q>0; Q--){
        
        cin>>q>>v;
        
        switch (q) {
            
            case 1:
                s.insert(v);
                break;
            case 2:
                s.erase(v);
                break;
            case 3:
                auto iter = s.find(v);
                if(iter!=s.end()){
                    cout<<"Yes"<<endl;
                }else{
                    cout<<"No"<<endl;
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