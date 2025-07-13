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
 1. 7 <Numeber of queries>
 2. 1 Jesse 20 <Queries ↓>
 3. 1 Jess 12
 4. 1 Jess 18
 5. 3 Jess
 6. 3 Jesse
 7. 2 Jess
 8. 3 Jess

Output:
 9. 30
10. 20
11. 0
*/