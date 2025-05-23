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
 * Complete the 'pairs' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY arr
 */

//Ussing double pointer technique, for 𝘖(𝘯) 𝘤𝘰𝘮𝘱𝘭𝘦𝘹𝘪𝘵𝘺 
int pairs(int k, vector<int> arr) {
    int count = 0;
    int i = 0, j = 1; 
    std::sort(arr.begin(), arr.end());
    
    while (j<arr.size()) {
        int diff = arr[j] - arr[i];

        if (diff == k) {//found pair, check next highest number
            count++;
            j++;
        } else if (diff < k) {//diff<k so next highest number could still give k
            j++;
        } else {//diff>k check next smallest number after i 
            i++;
            if (i == j) j++;
        }
    
    }
    return count;   
}

/*
functional, but obvious runtime error for large inputs
int pairs(int k, vector<int> arr) {
    int count = 0;
    std::sort(arr.begin(), arr.end());
    
    for (int i = 0; i<arr.size(); i++){
        for (int j = i+1; j < arr.size(); j++) {
            int pair =  arr[j]-arr[i];
            if (pair == k) {
                count++;
            }
        }
    }
    
    return count;   
}
*/

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    std::cout<<pairs(k, arr)<<std::endl;

    //fout << result << "\n";

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
1. 6 2 <length of array and value of k>
2. 1 2 3 4 5 6 <space separated array>

Output:
4 <total of pair where the difference is k, k=2 in this case>
*/