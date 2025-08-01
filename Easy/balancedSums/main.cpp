#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <numeric>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'balancedSums' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

 /* Time ineficient, I'm still attached to it tho
 string balancedSums(vector<int> arr) {
    if (arr.size()==1){
        return "YES";
    }
    
    if (arr.size()==0){
        return "NO";
    }
    
    int left = 0, right = 0;    
    
    for (int i = 0; i<arr.size(); i++){
        left = std::accumulate(arr.begin(), arr.begin()+i, 0);
        right = std::accumulate(arr.begin()+i+1, arr.end(),0);
        if(left==right){
            return "YES";
        }
    }
    
    return "NO";
}
 */

string balancedSums(vector<int> arr) {
    int total = std::accumulate(arr.begin(), arr.end(), 0);
    int leftSum = 0;

    for (int i = 0; i < arr.size(); i++) {
        int rightSum = total - leftSum - arr[i];
        if (leftSum == rightSum) {
            return "YES";
        }
        leftSum += arr[i];
    }

    return "NO";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string T_temp;
    getline(cin, T_temp);

    int T = stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
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

        string result = balancedSums(arr);

        std::cout<<result<<"\n";
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
1. 1 <# of test cases> 
2. 4 <length of array>
3. 1 2 3 3 <space separated array>

Output:
4. YES <in dis case, since 1 + 2 = 3; using 3 a middle> 
*/