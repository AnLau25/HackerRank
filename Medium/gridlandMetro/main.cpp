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
 * Complete the 'gridlandMetro' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY track
 */

long long gridlandMetro(long n, long m, long k, vector<vector<int>> track) {
    if(k==0) return n*m;
    
    sort(track.begin(), track.end());
    
    long long lamps = 0;
    int current = track[0][0], cell = 0, last = 0, rows = 0;
    
    for(int i = 0; i<k; i++){
        if(track[i][0]!=current){
            lamps+= m-cell;
            current = track[i][0];
            cell = 0;
            last = 0;
            rows++;
        }
        if(i<k-1 && track[i+1][0]==current && track[i][1] == track[i+1][1]) continue;
        
        cell += track[i][2] - track[i][1] + 1;
        cell = (track[i][1] <= last) ? (cell - min(last-track[i][1]+1, track[i][2]-track[i][1]+1)) : cell;
        last = max(last, track[i][2]);
    }
    
    lamps+= m*(n-rows) - cell;
    
    return lamps;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int k = stoi(first_multiple_input[2]);

    vector<vector<int>> track(k);

    for (int i = 0; i < k; i++) {
        track[i].resize(3);

        string track_row_temp_temp;
        getline(cin, track_row_temp_temp);

        vector<string> track_row_temp = split(rtrim(track_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int track_row_item = stoi(track_row_temp[j]);

            track[i][j] = track_row_item;
        }
    }

    long long result = gridlandMetro(n, m, k, track);

    fout << result << "\n";

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
 1. 3 3   <n=3 flowes, k=3 friends>
 2. 2 5 6 <array of flower costs>

Output:
 3. 13    <cost of flowers, following the equation ((i/k)+1)*c[i]>
*/