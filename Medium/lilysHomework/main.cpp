#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'lilysHomework' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int count_swaps(vector<int> cur, vector<int> expected){
    int swaps = 0;
    map<int, int> cur_map;
    
    for (int i = 0; i<cur.size(); i++){
        cur_map[cur[i]] = i;
    }
    
    for (int i = 0; i<cur.size(); i++){
        int temp = expected[i];
        if (temp!=cur[i]){
            int temp_i = cur_map[temp];
            cur[temp_i] = cur[i];
            cur_map[cur[i]] = temp_i;
            swaps++; 
        }
    }
    return swaps;
}

int lilysHomework(vector<int> arr) {
    vector<int> neg(arr.rbegin(), arr.rend());
    vector<int> pos(arr);
    sort(arr.begin(), arr.end());
    
    return min(count_swaps(arr, pos), count_swaps(arr, neg));
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

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

    int result = lilysHomework(arr);

    cout<<result<<"\n";

    //fout.close();

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
1. 6 <length of array>
2. 5 5 6 7 6 5 <space separated array>
*/