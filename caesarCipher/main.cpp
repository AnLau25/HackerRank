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
 * Complete the 'caesarCipher' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER k
 */

string caesarCipher(string s, int k) {
    string caesar;
    k = k % 26; 
    
    for (char c : s) {
        if (isupper(c)) {
            caesar += (char)(((c - 'A' + k) % 26) + 'A');
        } else if (islower(c)) {
            caesar += (char)(((c - 'a' + k) % 26) + 'a');
        } else {
            caesar += c;
        }
    }
    
    return caesar;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string s;
    getline(cin, s);

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    string result = caesarCipher(s, k);

    //fout << result << "\n";

    //fout.close();

    std::cout<<result;

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
1. 6 <length of string>
2. narmol <string sin espacios>
3. 2 <cifra de encripcion>

Result:
actoqn
*/

/*
𝗛𝗼𝗺𝗲 𝗺𝗮𝗱𝗲 𝘃𝗲𝗿:

string caesarCipher(string s, int k) {
    string caesar;
    k = k%26;
    
    for (char c : s){
        int ascii = c;
        int num_val = ascii + k;
        
        if((num_val)>90 && ascii<=90){
            num_val = 64 + (num_val-90);
        }else if ((num_val)>122 && ascii>=97 && ascii<=122) {
            num_val = 96 + (num_val-122);
        }else if (ascii<64 || ascii>122 || (ascii>90 && ascii<97)){
            num_val = ascii;
        }
        
        char translated = static_cast<char>(num_val);
        caesar += translated;
    }
    
    return caesar;
}
*/