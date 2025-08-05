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

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'miniMaxSum' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

/*
void miniMaxSum(vector<int> arr) {
    int len = arr.size();
    int min = 0; 
    int max = 0;
    long min_sum = 0; 
    long max_sum = 0;
     
    for (int i = 0; i<len; i++){
       if (arr[i]<arr[min]){
           min = i;
       }
        
       if (arr[i]>arr[max]){
           max = i;
       }
    }
     
    for (int i = 0; i<len; i++){        
        if (i!=max){
            min_sum += arr[i];
        }
        if (i!=min){
            max_sum += arr[i];
        }
    }
     
    std::cout<<min_sum<<" "<<max_sum<<std::endl;

}
*/

/* Improved
void miniMaxSum(vector<int> arr) {
    std::sort(arr.begin(),arr.end());
    long len = arr.size();
    long min_sum = 0; 
    long max_sum = 0;
    
    for (int i = 0; i< len; i++){        
        if (i!=(len-1)){
            min_sum += arr[i];
        }
        if (i!=0){
            max_sum += arr[i];
        }
    }
     
    std::cout<<min_sum<<" "<<max_sum<<std::endl;
    
}*/

void miniMaxSum(vector<int> arr) {
    sort(arr.begin(),arr.end());
    
    long long max_sum = accumulate(arr.begin()+1,arr.end(),0LL);
    long long min_sum = accumulate(arr.begin(),arr.begin()+arr.size()-1,0LL);
    
    cout<<min_sum<<" "<<max_sum<<endl;   
}

int main()
{

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(5);

    for (int i = 0; i < 5; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    miniMaxSum(arr);

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
1. 1 2 3 4 5 <space separated array>
*/
