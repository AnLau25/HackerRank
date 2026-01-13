#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

bool is_smart_number(int num) {
    int val = (int) sqrt(num);
    if(num == val * val)
        return true;
    return false;
}

int main() {
    
    int test_cases;
    cin >> test_cases;
    int num;
    for(int i = 0; i < test_cases; i++) {
        cin >> num;
        bool ans = is_smart_number(num);
        if(ans) {
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
    }
    return 0;
}

/* 
Input format:
 1. 20 3 6 85 <p=20, d=3, m=6, s=85>

Output:
 2. 6 <no of games you can buy>
*/