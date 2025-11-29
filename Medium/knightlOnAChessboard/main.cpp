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
 * Complete the 'knightlOnAChessboard' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts INTEGER n as parameter.
 */

//Struture that contains cell coordinates and distance from source 
struct cell{
    int x, y, dis;
    cell(): x(0), y(0), dis(0) {}
    cell(int x, int y, int dis) : x(x), y(y), dis(dis) {}
};

//Helper function to check if cell is inside board
bool inBoard(int x, int y, int n){
    return x>=0 && x<n && y>=0 && y<n;
}

//Function to find minimum steps to reach target cell ussing BFS
int steps(int a, int b, int n){
    //All possible moves of a knight (in this specific context)
    int dx[8] = { a,  a, -a, -a,  b,  b, -b, -b };
    int dy[8] = { b, -b,  b, -b,  a, -a,  a, -a };
    
    //Vector to keepp track of visited cells 
    vector<vector<bool>> visited(n+1, vector<bool>(n+1, false));
    visited[0][0] = true;
    
    //Queue for storing knight states
    queue<cell> q;
    q.push(cell(0, 0, 0));
    
    cell t;
    int x, y;
    
    //Loop untill q empty
    while (!q.empty()) {
        t = q.front();
        q.pop();
        
        //If goal reached, return distance (aka number of moves)
        if(t.x == n-1 && t.y == n-1) return t.dis;
        
        //Else visit all valid reachable states
        for(int i = 0; i<8; i++){
            x = t.x + dx[i];
            y = t.y + dy[i];
            
            if(inBoard(x, y, n) && !visited[x][y]){
                visited[x][y] = true;
                q.push(cell(x, y, t.dis+1));
            }
        }
    
    }
    
    return -1;
}

vector<vector<int>> knightlOnAChessboard(int n) {
    vector<vector<int>> result(n-1, vector<int>(n-1, 0));
    
    for(int i = 1; i<n; i++){
        for(int j = 1; j<n; j++){
            //Get no of steps for each (a,b) pair
            result[i-1][j-1] = steps(i, j, n);
        }
    }
    
    return result;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> result = knightlOnAChessboard(n);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            cout << result[i][j];

            if (j != result[i].size() - 1) {
                cout << " ";
            }
        }

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
 1. 5         <size of the chessboard>

Output:
 2. 4 4 2 8   <Number of steps to reach (n-1,n-1) for each (a,b) pair>   
 3. 4 2 4 4
 4. 2 4 -1 
 5. 8 4 -1 1

𝗡𝗼𝘁𝗲𝘀:
 - Rather than move like a normal knight, this knight moves in a (a, b)
 - where a and b are <n
 - You can use the same BFS as with a normal knight problem, just with difirerent limits
 - https://www.geeksforgeeks.org/dsa/minimum-steps-reach-target-knight/

*/