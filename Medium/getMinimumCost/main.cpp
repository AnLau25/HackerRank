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

// Complete the getMinimumCost function below.
int getMinimumCost(int k, vector<int> c) {
    sort(c.begin(), c.end(), greater<int>());
    int prise = 0;
    
    for(int i=0; i<c.size(); i++){
        prise+=(int(i/k)+1)*c[i];
    }
    
    return prise;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string c_temp_temp;
    getline(cin, c_temp_temp);

    vector<string> c_temp = split_string(c_temp_temp);

    vector<int> c(n);

    for (int i = 0; i < n; i++) {
        int c_item = stoi(c_temp[i]);

        c[i] = c_item;
    }

    int minimumCost = getMinimumCost(k, c);

    fout << minimumCost << "\n";

    fout.close();

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