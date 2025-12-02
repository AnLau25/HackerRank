#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <queue>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'printShortestPath' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER i_start
 *  3. INTEGER j_start
 *  4. INTEGER i_end
 *  5. INTEGER j_end
 */
struct cell{
    // Support struct to hold cell information
    int x, y;
    string dir;
    cell(): x(0), y(0), dir("") {}
    cell(int x, int y, string dir) : x(x), y(y), dir(dir) {}
};

void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) {
    // Print the distance along with the sequence of moves.
    vector<cell> moves = {{-2, -1, "UL"}, {-2,  1, "UR"}, { 0,  2, "R"}, { 2,  1, "LR"}, { 2, -1, "LL"}, { 0, -2, "L"}}; 
    // Possible moves for the "Red Knight" piece
    int steps = -1;
    
    queue<cell> q; // BFS queue
    vector<vector<bool>> visited(n, vector<bool> (n, false)); // Visited cells tracker
    
    visited[i_start][j_start] = true;
    q.push({i_start, j_start, ""});
    
    while (!q.empty()) {
        steps++;
        int s = q.size();
        while (s--) {
            cell curr = q.front();
            q.pop(); // Get the front cell
            
            // Check if end reached
            if(curr.x == i_end && curr.y == j_end){
                cout<<steps<<endl;
                cout<<curr.dir<<endl;
                return;
            }
            
            // Explore all possible moves
            for(cell m :  moves){
                int nx = curr.x + m.x;
                int ny = curr.y + m.y;
                
                if(nx>=0 && nx<n && ny>=0 && ny<n && !visited[nx][ny]){
                    visited[nx][ny] = true;
                    q.push({nx, ny, curr.dir + m.dir + " "});
                }
            
            }
        }
    }

    // If we exhaust the queue without finding the end position
    cout<< "Impossible" << endl;    
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int i_start = stoi(first_multiple_input[0]);

    int j_start = stoi(first_multiple_input[1]);

    int i_end = stoi(first_multiple_input[2]);

    int j_end = stoi(first_multiple_input[3]);

    printShortestPath(n, i_start, j_start, i_end, j_end);

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
 1. 7           <Dimension of the chessboard>
 2. 0 3 4 3     <i_start, j_start, i_end, j_end>

Output:
 3. 2           <Number of moves>
 4. LR LL       <Path taken>
*/