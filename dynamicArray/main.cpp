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
 * Complete the 'dynamicArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */

vector<int> dynamicArray(int n, vector<vector<int>> queries) {
    int lastAnswer = 0, indx = 0, dfq = 0;
    vector<int> answers;
    vector<vector<int>> arr(n);
    
    for(vector<int> i : queries){
        if(i[0]==1){
            indx = (i[1]^lastAnswer)%n;
            arr[indx].push_back(i[2]);
        }
        if(i[0]==2){
            indx = (i[1]^lastAnswer)%n;
            dfq = i[2]%(arr[indx].size()); 
            lastAnswer = arr[indx][dfq];
            answers.push_back(lastAnswer);
        }
    }
    
    return answers;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(3);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> result = dynamicArray(n, queries);

    for (size_t i = 0; i < result.size(); i++) {
        std::cout<<result[i];

        if (i != result.size() - 1) {
            std::cout<<"\n";
        }
    }

    std::cout<<"\n";

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
1. 2 5 <n = 2, length or arr; # queries = 5>
2. 1 0 5 <5 queries; format 𝘳𝘶𝘭𝘦 𝘹 𝘺>
3. 1 1 7
4. 1 0 3
5. 2 1 0
6. 2 1 1 

Output:
7. 7 <content of the 𝘢𝘯𝘴𝘸𝘦𝘳𝘴 array>
8. 3
*/ 