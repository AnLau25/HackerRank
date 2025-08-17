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
 * Complete the 'formingMagicSquare' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY s as parameter.
 */

int formingMagicSquare(vector<vector<int>> s) {
    vector<vector<vector<int>>> magicSquares = {
        {{8,1,6},{3,5,7},{4,9,2}},
        {{6,1,8},{7,5,3},{2,9,4}},
        {{4,9,2},{3,5,7},{8,1,6}},
        {{2,9,4},{7,5,3},{6,1,8}},
        {{8,3,4},{1,5,9},{6,7,2}},
        {{4,3,8},{9,5,1},{2,7,6}},
        {{6,7,2},{1,5,9},{8,3,4}},
        {{2,7,6},{9,5,1},{4,3,8}}
    };

    int minCost = INT_MAX;
    for (auto &magic : magicSquares) {
        int cost = 0;
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                cost += abs(s[i][j] - magic[i][j]);
            }
        }
        minCost = min(minCost, cost);
    }
    return minCost;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);

    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        string s_row_temp_temp;
        getline(cin, s_row_temp_temp);

        vector<string> s_row_temp = split(rtrim(s_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int s_row_item = stoi(s_row_temp[j]);

            s[i][j] = s_row_item;
        }
    }

    int result = formingMagicSquare(s);

    cout << result << "\n";

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
Notas:
 - The Lo Shu magic square is a 3x3 grid of numbers, where each row, column, and diagonal adds up to the same sum, which is 15. 
 - It's also known as the Lo Shu square and is one of the earliest examples of a magic square, originating from ancient China.
 - La solucion se basa en comparar con el cuadrado de Lo Shu, en todas su formas posibles (como cancelando en OX)
 - Para una version mas grande, no seria recomendable escribir las reflexiones y roaciones del cuadrado, habria que generarlas
 - Pero como es un 3x3 está bien
 - Kinda greedy algorithm 
*/


/* 
Input format:
 1. 4 9 2 <rows of the 3x3 matrix ↓>
 2. 3 5 7
 3. 8 1 5

Output:
 4. 1 <total cost of Lo Shu transform>
*/