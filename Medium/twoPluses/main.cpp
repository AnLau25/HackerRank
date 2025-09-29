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
 * Complete the 'twoPluses' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY grid as parameter.
 */
struct Plus {
    int area;
    vector<pair<int,int>> cells;
};

vector<Plus> allPlussesAt(int y, int x, const vector<string>& grid) {
    vector<Plus> result;
    if (grid[y][x] != 'G') return result;

    int arm = 0;
    int rows = grid.size(), cols = grid[0].size();

    while (y-arm >= 0 && y+arm < rows &&
           x-arm >= 0 && x+arm < cols &&
           grid[y-arm][x] == 'G' &&
           grid[y+arm][x] == 'G' &&
           grid[y][x-arm] == 'G' &&
           grid[y][x+arm] == 'G') {
        
        vector<pair<int,int>> cells;
        cells.push_back({y,x});
        for (int k=1; k<=arm; k++) {
            cells.push_back({y-k,x});
            cells.push_back({y+k,x});
            cells.push_back({y,x-k});
            cells.push_back({y,x+k});
        }
        
        result.push_back({1 + 4*arm, cells});
        arm++;
    }

    return result;
}

vector<Plus> allPlusses(const vector<string>& grid) {
    vector<Plus> plusses;
    for (int y=0; y<grid.size(); y++) {
        for (int x=0; x<grid[0].size(); x++) {
            auto p = allPlussesAt(y, x, grid);
            plusses.insert(plusses.end(), p.begin(), p.end());
        }
    }
    return plusses;
}

bool overlap(const Plus& a, const Plus& b) {
    for (auto &cellA : a.cells) {
        for (auto &cellB : b.cells) {
            if (cellA == cellB) return true;
        }
    }
    return false;
}

int maxPlusAreaAt(int y, int x, const vector<string>& grid) {
    if (grid[y][x] != 'G') return 0;

    int arm = 0;
    int rows = grid.size(), cols = grid[0].size();

    while (y-arm >= 0 && y+arm < rows &&
           x-arm >= 0 && x+arm < cols &&
           grid[y-arm][x] == 'G' &&
           grid[y+arm][x] == 'G' &&
           grid[y][x-arm] == 'G' &&
           grid[y][x+arm] == 'G') {
        arm++;
    }
    arm--; 
    
    return 1 + 4*arm;
}

int twoPluses(vector<string> grid) {
    vector<Plus> plusses = allPlusses(grid);

    int best = 0;
    for (int i=0; i<plusses.size(); i++) {
        for (int j=i+1; j<plusses.size(); j++) {
            if (!overlap(plusses[i], plusses[j])) {
                best = max(best, plusses[i].area * plusses[j].area);
            }
        }
    }

    return best;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

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
Input format:
 1. 6 6    <dimentions of the grid>
 2. BGBBGB <Grid rows ↓>
 3. GGGGGG
 4. BGBBGB
 5. GGGGGG
 6. BGBBGB
 7. BGBBGB

Output:
 8. 25     <maximum product of the areas of two non-overlapping pluses>
*/