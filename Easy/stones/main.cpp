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

/*
 * Complete the 'stones' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER a
 *  3. INTEGER b
 */

vector<int> stones(int n, int a, int b) {
    if(a==b) return {a*n -b};
    if(a==0) return {b*n};
    if(b==0) return {a*n};
    
    if(b<a){
        int c = a;
        a = b;
        b = c;
    }
    
    vector<int> last_stones(n);
    vector<int> aVec(n-1, 1);
    vector<int> bVec(n-1, 0);
    int ab_pos = 0;
    
    while (!(ab_pos>aVec.size())) {
        int last = 0;
        for(int i = 0; i<aVec.size(); i++){
            last += aVec[i]*a + bVec[i]*b;           
        }
        
        last_stones[ab_pos] = last;
        
        if(ab_pos<aVec.size()){    
            aVec[ab_pos] = 0;
            bVec[ab_pos] = 1;
        }
        ab_pos++;
    }
    
    return last_stones;
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

        string a_temp;
        getline(cin, a_temp);

        int a = stoi(ltrim(rtrim(a_temp)));

        string b_temp;
        getline(cin, b_temp);

        int b = stoi(ltrim(rtrim(b_temp)));

        vector<int> result = stones(n, a, b);

        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
            }
        }

        cout << "\n";
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
 1. 2       <T = 2 (test cases)>
 2. 3       <n = 3 (test case 1)>
 3. 1       <a = 1>
 4. 2       <b = 2>
 5. 4       <n = 4 (test case 2)>
 6. 10      <a = 10>
 7. 100     <b = 100>

Output:
 8. 2 3 4   <possible values to the last stone> 
 9. 30 120 210 300 
*/