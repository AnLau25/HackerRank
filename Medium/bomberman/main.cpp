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
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 */

vector<string> fillGrid(size_t rows, size_t columns){
    std::string fill;
    fill.insert(0, columns, 'O');
    
    return {rows, fill}; // array where all rows(elements) are str fill

}

void tnt(std::vector<string>& grid, int x, int y){
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    if(x<0 || y<0 || x>=rows || y>=cols){
        return;
    }

    grid[x][y] = '.';

}

vector<string> detonate(vector<string> const& grid){
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    auto new_grid =  fillGrid(rows, cols);

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            if (grid[i][j] == 'O') {
                if (i + 1 < rows) new_grid[i + 1][j] = '.';
                if (i - 1 >= 0)   new_grid[i - 1][j] = '.';
                if (j + 1 < cols) new_grid[i][j + 1] = '.';
                if (j - 1 >= 0)   new_grid[i][j - 1] = '.';
                new_grid[i][j] = '.';
            }
        }
    }

    return new_grid;
}

vector<string> bomberMan(int n, vector<string> grid) {
   
    size_t rows = grid.size();
    size_t cols = grid[0].size();
    
    if(n <= 1){
        return grid;
    }
    
    if(n%2==0){
        return fillGrid(rows, cols);
    }
    
    if(n%4==3){
        return detonate(grid);
     }
     
    if(n%4==1){
        auto result = detonate(grid);
        return detonate(result);
    }
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int r = stoi(first_multiple_input[0]);

    int c = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (size_t i = 0; i < result.size(); i++) {
        std::cout<< result[i];

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
1. 6 <length of array>
2. 5 5 6 7 6 5 <space separated array>
*/