#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <stack>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'waiter' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY number
 *  2. INTEGER q
 */

vector<int> sieveOfEratos(int n) {
    vector<bool> verif(n + 1, true);
    vector<int> primes;
    verif[0] = verif[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (verif[p]) {
            for (int i = p * p; i <= n; i += p) {
                verif[i] = false;
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (verif[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

vector<int> waiter(vector<int> number, int q) {
    vector<int> primes = sieveOfEratos(10000);
    vector<int> answers;

    stack<int> A, B;

    for (int i = 0; i < number.size(); i++) {
        A.push(number[i]);
    }

    for (int i = 0; i < q; ++i) {
        stack<int> nextA;
        B = stack<int>();  

        while (!A.empty()) {
            int val = A.top();
            A.pop();
            if (val % primes[i] == 0) {
                B.push(val);
            } else {
                nextA.push(val);
            }
        }

        while (!B.empty()) {
            answers.push_back(B.top());
            B.pop();
        }

        A = nextA; 
    }

    vector<int> remaining;
    while (!A.empty()) {
        remaining.push_back(A.top());
        A.pop();
    }
    
    answers.insert(answers.end(), remaining.begin(), remaining.end());

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

    string number_temp_temp;
    getline(cin, number_temp_temp);

    vector<string> number_temp = split(rtrim(number_temp_temp));

    vector<int> number(n);

    for (int i = 0; i < n; i++) {
        int number_item = stoi(number_temp[i]);

        number[i] = number_item;
    }

    vector<int> result = waiter(number, q);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

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
1. 5 1 <length of array, number of iters>
2. 3 4 7 6 5 <space separated array>

Output:
3. 4 <stack of plates after manipulation ↓>
4. 6
5. 3
6. 7
7. 5
*/