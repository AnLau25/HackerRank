#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <queue>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */

/* 
The hardcoded, time ineficient, version I'm still very much attached to
vector<vector<int>> devide(vector<int> arr, int i){
    vector<vector<int>> subarrs;
    vector<int> curr;
    int ent=0;
    
    while ((ent+i-1)<(arr.size())) {
        curr.push_back(arr[ent]);
        
        for(int k = 1; k<i; k++){
            curr.push_back(arr[ent+k]);
        }
        subarrs.push_back(curr);
        curr={};
        ent++;
    }
    
    return subarrs;
}

vector<int> max(vector<vector<int>> subarrs){
    vector<int> locMaxes;
    
    for (vector<int> vec : subarrs){
        locMaxes.push_back(*max_element(vec.begin(), vec.end()));
    }
    
    return locMaxes;
}  

vector<int> solve(vector<int> arr, vector<int> queries) {
    vector<int> soln;
    
    for (int i : queries){
        vector<int> temp = max(devide(arr, i));
        soln.push_back(*min_element(temp.begin(), temp.end()));   
    }
    
    return soln;
}
*/

vector<int> solve(vector<int> arr, vector<int> queries) {
    vector<int> soln;

    for (int k : queries) {
        deque<int> dq;
        vector<int> max_in_windows;

        for (int i = 0; i < arr.size(); ++i) {
            
            // Remove elements out of the window
            if (!dq.empty() && dq.front() <= i - k){
                dq.pop_front();
            }
            
            // Maintain deque: remove elements smaller than current
            while (!dq.empty() && arr[dq.back()] <= arr[i]){
                dq.pop_back();
            }

            dq.push_back(i);

            // If window is valid, record max
            {if (i >= k - 1)
                max_in_windows.push_back(arr[dq.front()]);
            }
        }

        // Take the min of all maxes in the window
        soln.push_back(*min_element(max_in_windows.begin(), max_in_windows.end()));
    }

    return soln;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<int> queries(q);

    for (int i = 0; i < q; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<int> result = solve(arr, queries);

    for (size_t i = 0; i < result.size(); i++) {
        cout<<result[i];

        if (i != result.size() - 1) {
            cout<<"\n";
        }
    }

    cout<<"\n";

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
1. 5 2 <length of array, no of queries>
2. 2 3 4 5 6 <space separated array>
3. 2 <query values ↓>
4. 3

Output:
5. 3 <min of the max, min(max aj)>
6. 4
*/