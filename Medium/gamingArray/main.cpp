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
 * Complete the 'gamingArray' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

string gamingArray(vector<int> arr) {
    vector<int> mxm;
    int curr = arr[0];
    
    mxm.push_back(arr[0]);
    for(int i = 1; i<arr.size(); i++){
        if(arr[i]>curr){
            curr = arr[i];
            mxm.push_back(arr[i]);
        }
    } 
    
    return mxm.size()%2==0?"ANDY" : "BOB";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string g_temp;
    getline(cin, g_temp);

    int g = stoi(ltrim(rtrim(g_temp)));

    for (int g_itr = 0; g_itr < g; g_itr++) {
        string arr_count_temp;
        getline(cin, arr_count_temp);

        int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(arr_count);

        for (int i = 0; i < arr_count; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        string result = gamingArray(arr);

        cout << result << "\n";
    }

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
 1. 2           <number of games/test cases>
 2. 5           <size of array for game 1>
 3. 5 2 6 3 4   <elements of array for game 1>
 4. 2
 5. 3 1

Output:
 6. ANDY        <winner of game>
 7. BOB
*/