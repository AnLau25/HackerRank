#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int rows = grid.size(), cols = grid[0].size();
    
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, pair<int, int>>> q;
    
    q.push({0, {startX, startY}});
    visited[startX][startY] = true;
    
    int mx[] = {0, 0, -1, 1};
    int my[] = {-1, 1, 0, 0}; 
    
    while (!q.empty()){
        auto [moves, pos] = q.front();
        q.pop();
        int currX = pos.first, currY = pos.second;
        
        if(currX==goalX && currY==goalY) return moves;
        
        for(int m = 0; m < 4; ++m){
            int newX = currX, newY = currY;
            
            while (true) {
                int tempX = newX + mx[m], tempY = newY + my[m];
                
                if (tempX < 0 || tempX >= rows || tempY < 0 || tempY >= cols || grid[tempX][tempY] == 'X') break;
                
                newX = tempX;
                newY = tempY;
                
                if(!visited[newX][newY]){
                    visited[newX][newY] = true;
                    q.push({moves+1, {newX, newY}});
                }
            }
        }
    }
    return -1;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    cout<<result<<"\n";

    //fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
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