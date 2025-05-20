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
 * Complete the 'flippingMatrix' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int flippingMatrix(vector<vector<int>> matrix) {
    
    int n = matrix.size() / 2;
    int sum = 0;
    
    //Chooses the top corner of the matrix (i<matrix.size()/2 and j<matrix.size()/2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //For the current position in that top corner, which value would be the biggest if:
            sum += max({
                matrix[i][j], //We leave the array as is
                matrix[i][2 * n - 1 - j], //We flip the column
                matrix[2 * n - 1 - i][j], //We flip the row
                matrix[2 * n - 1 - i][2 * n - 1 - j] //We flip both
            });
        }
    }

    /* 
    𝗟𝗲𝘀𝘀𝗼𝗻𝘀 𝗹𝗲𝗮𝗿𝗻𝗲𝗱:
    - max(): compares 2 or more values and finds the biggest
    - If they ask u to return an int, dont waste time trying to reconfigure the matrix
    */

    return sum;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        vector<vector<int>> matrix(2 * n);

        for (int i = 0; i < 2 * n; i++) {
            matrix[i].resize(2 * n);

            string matrix_row_temp_temp;
            getline(cin, matrix_row_temp_temp);

            vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

            for (int j = 0; j < 2 * n; j++) {
                int matrix_row_item = stoi(matrix_row_temp[j]);

                matrix[i][j] = matrix_row_item;
            }
        }

        int result = flippingMatrix(matrix);

        std::cout<<result;

        //fout << result << "\n";
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
Inut format:
1. 1
2. 1 2 3
   4 5 6
   7 8 9
*/