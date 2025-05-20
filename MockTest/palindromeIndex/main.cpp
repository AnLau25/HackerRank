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

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */


bool isPalindrome(const string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

int palindromeIndex(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            if (isPalindrome(s, left + 1, right)) return left;
            if (isPalindrome(s, left, right - 1)) return right;
            return -1;
        }
        left++;
        right--;
    }

    return -1;
}

//Checks if remooving one letter makes palindrome

/*
int palindromeIndex(string s) {
    int right = s.size()-1;
    int left = 0;

    while (left<right)
    {
        if(s[left] != s[right]){
            //If by removing, it becomes even, solution found
            if(s[left]==s[right-1])
            {
                return right;
            }
            if (s[left+1]==s[right])
            {
                return left;
            }
        }

        left++;
        right--;
    }

    return -1;
}
*/

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = palindromeIndex(s);

        //fout << result << "\n";
        std::cout<<result<<std::endl;
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
1. 1 2 3 4 5 <space separated array>
*/
