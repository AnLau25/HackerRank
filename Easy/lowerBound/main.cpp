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
    int n, q, v, indx=0;
    
    cin>>n;
    vector<int> vec(n);
    for(int i = 0; i<n; i++) cin>>vec[i];
    
    cin>>q; 
    for(; q>0; q--){
        
        cin>>v;
        auto iter = lower_bound(vec.begin(), vec.end(), v);
        indx = (iter - vec.begin());
        
        if(vec[indx]==v){
            cout<<"Yes "<<indx+1<<endl;
        }else{
            cout<<"No "<<indx+1<<endl;
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