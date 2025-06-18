#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <set>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bigSorting' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY unsorted as parameter.
 */

struct compStrAsLong {
    bool operator()(const std::string &a, const std::string &b) const {
        if (a.length()!=b.length()){
            return  a.length()<b.length();
        }
        return a<b;
    }
};

vector<string> bigSorting(vector<string> unsorted) {
    std::multiset<string, compStrAsLong> sort;
    
    for (string str : unsorted) {
        sort.insert(str);
    }
    
    std::vector<string> sorted(sort.begin(),sort.end());
    
    return sorted;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> unsorted(n);

    for (int i = 0; i < n; i++) {
        string unsorted_item;
        getline(cin, unsorted_item);

        unsorted[i] = unsorted_item;
    }

    vector<string> result = bigSorting(unsorted);

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
 1. 6 <# of elements to sort>
 2. 96 <elements ↓>
 3. 165164984845155515165156875454468
 4. 5
 5. 88
 6. 1
 7. 10

Output:
 8. 1
 9. 5
10. 10
11. 88
12. 96
13. 165164984845155515165156875454468
*/