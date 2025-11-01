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
 * Complete the 'insertionSort' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

long long insertionSort(vector<int> arr) {
    long long count = 0; //inversion count 
    long long fenSum = 0; //Numbers seen so far
    vector<int> fenwick(10000001, 0); //Fenwick tree init to 0; assuming arr max size = 10^7

    for (int n : arr) { //Build the tree using values as indexes
        count += fenSum; //All numbers seen so far are greater than current number (shifts)
        int idx = n; //Current index in Fenwick tree

        while (idx) { //Substract numbers less than or equal to current number
            count -= fenwick[idx];
            idx -= idx & -idx; //Move to parent
        }

        idx = n;
        while (idx < 10000001) { //Insert current number into Fenwick tree
            fenwick[idx] += 1; //Increment count at index, seen more than one occurrence
            idx += idx & -idx; //Move to next
        }

        fenSum += 1; //Increment total numbers seen so far
    }

    return count;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
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

        long long result = insertionSort(arr);

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
 1. 2          <number of test cases>
 2. 5          <arr size>
 3. 1 1 1 2 2  <arr elements>
 4. 5  
 5. 2 1 3 1 2

Output:
 6. 0          <number of inversions to sort arr>
 7. 4   

Note:
    - Using a Fenwick Tree (Binary Indexed Tree) to count inversions efficiently.
    - Time Complexity: O(n log m), where n is the number of elements and m is the range of input values.
    - Space Complexity: O(m) for the Fenwick tree.
    - https://www.geeksforgeeks.org/dsa/binary-indexed-tree-or-fenwick-tree-2/
    - https://stackoverflow.com/questions/61158098/count-the-no-of-shifts-in-insertion-sort-using-fenwick-tree-binary-index-tree
*/