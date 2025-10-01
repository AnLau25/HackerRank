#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'almostSorted' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void almostSorted(vector<int> arr) {
    bool swp = false, rev = false;
    int idx1 = -1, idx2 = -1, sorted = 0;
    
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i+1]) {
            if (sorted == 0) {
                idx1 = i;
            }
            idx2 = i+1;
            sorted++;
        }
    }

    if (sorted == 0) {
        cout << "yes" << endl;
        return;
    }

    swap(arr[idx1], arr[idx2]);
    if (is_sorted(arr.begin(), arr.end())) {
        cout << "yes" << endl;
        cout << "swap " << idx1+1 << " " << idx2+1 << endl;
        return;
    }
    swap(arr[idx1], arr[idx2]); 

    reverse(arr.begin()+idx1, arr.begin()+idx2+1);
    if (is_sorted(arr.begin(), arr.end())) {
        cout << "yes" << endl;
        cout << "reverse " << idx1+1 << " " << idx2+1 << endl;
        return;
    }

    cout << "no" << endl;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); })
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}


/* 
Input format:
 1. 6 7 3 <rows = 6, columns = 7, sec = 3>
 2. ....... <grid made of string arrays ↓>         
 3. ...O...                
 4. ....O..
 5. .......
 6. OO.....
 7. OO.....

Output:
 8. OOO.OOO
 9. OO...OO
10. OOO...O
11. ..OO.OO
12. ...OOOO
13. ...OOOO
*/