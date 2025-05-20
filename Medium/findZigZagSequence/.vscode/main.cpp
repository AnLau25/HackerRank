#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> 
using namespace std;

void findZigZagSequence(vector < int > a, int n){
    sort(a.begin(), a.end());
    int mid = (n)/2; // Mod1
    swap(a[mid], a[n-1]);
    /*
        Bassed on problem description you'd think ur not allowed mod 1, but it is literally the only option here
    */

    int st = mid + 1;
    int ed = n - 2; // Mod 2
    while(st <= ed){
        swap(a[st], a[ed]);
        st = st + 1;
        ed = ed - 1; // Mod 3
    }
    for(int i = 0; i < n; i++){
        if(i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
}

int main() {
    int n, x;
    int test_cases;
    cin >> test_cases;

    for(int cs = 1; cs <= test_cases; cs++){
        cin >> n;
        vector < int > a;
        for(int i = 0; i < n; i++){
            cin >> x;
            a.push_back(x);
        }
        findZigZagSequence(a, n);
    }
}
