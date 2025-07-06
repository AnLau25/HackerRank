#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

int main() {
    
    long n, q;
    cin>>n>>q;
    cin.ignore();
    
    vector<vector<long>> arr(n);
    string line;
    
    for (long i = 0; i < n; i++) {
        getline(cin, line);
        stringstream ss(line);
        
        long skip;
        ss >> skip;
        
        long num;
        while (ss >> num) {
            arr[i].push_back(num);
        }
    }
    
    long p1, p2;
    
    for (; q>0; q--){
        cin >> p1 >>p2;
        cout<<arr[p1][p2]<<'\n';
    }
    
       
    return 0;
}