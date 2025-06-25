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
 * Complete the 'lonelyinteger' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

/*
int lonelyinteger(vector<int> a) {
    int len = a.size()-1;
    bool flag = true;
    int pringle = 0;
    
    while (flag) {
        pringle = a[len];
        
        bool found = false;
        for (int i = 0; i<a.size(); i++){
            
            if (a[i]==pringle && i!=len){
                found = true;
                len--;
                break;
            }   
        }
        
        if (!found){
            flag = false;
        }
    }
    
    std::cout<<pringle<<std::endl;

    return pringle;
}
*/

//Improved... but adieu single 𝘱𝘳𝘪𝘯𝘨𝘭𝘦
int lonelyinteger(vector<int> a) {
    if (a.size() == 1) return a[0];
    
    std::sort(a.begin(), a.end());
    
    for (int i = 0; i < a.size() - 1; i += 2) {
        if (a[i] != a[i + 1]) {
            return a[i];
        }
    }
    
    return a[a.size() - 1];
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = lonelyinteger(a);

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
Aparently XOR is a thing in c++???
like???????

int lonelyinteger(vector<int> a) {
    int result = 0;
    for (int num : a) {
        result ^= num;
    }
    return result;
}
*/

/* 
Input format:
1. 6 <length of array>
2. 5 5 6 7 6 5 <space separated array>
*/