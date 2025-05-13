#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <cctype>
# include <algorithm>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'median' function below.
 *
 * The function is expected to return a INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void median(vector<int> arr) 
{   int len = arr.size();
    vector<int> new_arr = arr;

    for (int i=0; i<len; i++){
        int current = new_arr[i];

        if (current>new_arr[i+1] && !((i+1)>=len)){
            new_arr[i] = new_arr[i+1];
            new_arr[i+1] = current;
        }
    }

    for (int i=0; i<len; i++){
        int current = new_arr[i];

        if (new_arr[i+1]<current && !((i+1)>=len)){
            new_arr[i] = new_arr[i+1];
            new_arr[i+1] = current;
        }
    }

    std::sort(arr.begin(), arr.end());
    std::cout<<"Sort function: "<<arr[len/2]<<std::endl;
    std::cout<<"Homemade vrsn: "<<new_arr[len/2]<<std::endl;
    
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

    median(arr);

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

