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
 1. 8 <Numeber of queries>
 2. 1 9 <Queries ↓, 1: insert, 2: erase, 3:find>
 3. 1 6
 4. 1 10
 5. 1 4
 6. 3 6
 7. 3 14
 8. 2 6
 9. 3 6 

Output:
10. Yes <Find, results ↓>
11. No
12. Yes
*/