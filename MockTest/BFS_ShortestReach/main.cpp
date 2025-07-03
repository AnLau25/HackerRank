#include <iostream>
#include <vector>
#include <queue>
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
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {
    vector<vector<int>> adj(n+1);
    //Create the graph by tracking the links a node has 
    for (auto& edge : edges){
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    //Track distances, initialize all to -1 (default for unlinked nodes)
    vector<int> distance(n + 1, -1);
    //Track what nodes have been visited, init to false since none visited
    vector<bool> visited(n + 1, false);
    //Initialize queue (FIFO), would use stack for DFS (LIFO)
    queue<int> q;

    visited[s] = true; //First node already visited
    distance[s] = 0; //Distance from first-first is 0
    q.push(s); //Init the queue with the statrt point

    while (!q.empty()){ 
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]){ //Visit all the neighbors of the current node (BFS)
            if (!visited[neighbor]){ //If the neighbor has not been visited
                visited[neighbor] = true; //Mark it as visited
                distance[neighbor] = distance[node] + 6; // Mark it's distance from the start node [current node distance + 6]
                q.push(neighbor); //Push it in the queue so we can look for its neighbors
            }
        }
    }

    vector<int> paths;
    for (int i = 1; i<= n; i++){
        if (i!=s){ //Push all, except start node s
            paths.push_back(distance[i]);
        }
    }
    
    return  paths;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(2);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = bfs(n, m, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            std::cout<<result[i];

            if (i != result.size() - 1) {
                std::cout<< " ";
            }
        }

        //fout << "\n";
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
Input format:
1. 1 <number of tests>
2. 4 2 <n number of nodes, m number of edges; n=4 m=2>
3. 1 2 <edge [1, 2]>
4. 1 3 <edge [1, 3]>
5. 1 <s starting node>

Output:
6 6 -1 <-1 for node 4 since there is no edge to 4>
*/