#include <iostream>
#include <vector>
#include <string>
#include <cmath>      // for sqrt
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

bool is_smart_number(int num) {
    int val = (int) sqrt(num);
    if(num == val * val) //Because it's cpp num/val==val causes an imprecision error
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
 1. 4     <Number of test cases>
 2. 1     <Test cases ↓>
 3. 2
 4. 7
 5. 169

Output:
 6. YES   <Is the number a perfect square?>
 7. NO
 8. NO
 9. YES
*/