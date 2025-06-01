#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <functional>
#include <queue>
#include <map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'matchingStrings' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY strings
 *  2. STRING_ARRAY queries
 */

vector<int> matchingStrings(vector<string> strings, vector<string> queries) {
    std::unordered_map<std::string, int> strMap;
    std::vector<int> found(queries.size());
    
    for (std::string i : queries){
        strMap.insert({i, 0});
    }
    
    for (std::string i : strings){
        
        if (strMap.find(i)!=strMap.end()){
            strMap[i]+=1;
        }
    }
    
    for (int i = 0; i<found.size(); i++){
        found[i] = strMap[queries[i]];
    }
    
    return found;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string strings_count_temp;
    getline(cin, strings_count_temp);

    int strings_count = stoi(ltrim(rtrim(strings_count_temp)));

    vector<string> strings(strings_count);

    for (int i = 0; i < strings_count; i++) {
        string strings_item;
        getline(cin, strings_item);

        strings[i] = strings_item;
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<string> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item;
        getline(cin, queries_item);

        queries[i] = queries_item;
    }

    vector<int> res = matchingStrings(strings, queries);

    for (size_t i = 0; i < res.size(); i++) {
        std::cout<< res[i];

        if (i != res.size() - 1) {
            std::cout<<"\n";
        }
    }

    //fout << "\n";

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

/* 
Input format:
1. ABACA <array, all caps for simplicity>

- U can go for lower case too
- And symbols
- It does not consider the space when taking the array input, so the stuff after a space is lost

Output:
ABACA <cause it builds the tree and encodes the array for us, our job is to decode>
      <makes it easier to check if u got it right>
*/