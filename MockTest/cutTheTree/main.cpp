#include <algorithm>
#include <iostream>
#include <stack>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

int bfs(map<int, vector<int>> adj, int node, map<int, int> vals) {
    int sum = 0;
    map<int, bool> visited;
    stack<int> neighbors;
    neighbors.push(node);
    visited[node] = true;

    while (!neighbors.empty()) {
        int curr = neighbors.top();
        neighbors.pop();
        sum += vals[curr];

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                neighbors.push(neighbor);
            }
        }
    }

    return sum;
}

int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    if (edges.size()<=1) return edges.size();
    
    map<int, int> values;
    map<int, vector<int>> adj;
    for( vector<int> edge : edges){
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    for ( auto [i, _] : adj){
        values[i] = data[i-1];
    }
    
    int edge_count = 0; 
    vector<pair<int, int>> diffs;
    
    for (vector<int> edge : edges){
        int node1 = edge[0], node2 = edge[1];

        map<int, vector<int>> modified_adj = adj;

        auto& v1 = modified_adj[node1];
        auto& v2 = modified_adj[node2];
        v1.erase(remove(v1.begin(), v1.end(), node2), v1.end());
        v2.erase(remove(v2.begin(), v2.end(), node1), v2.end());

        int diff1 = bfs(modified_adj, node1, values);
        int diff2 = bfs(modified_adj, node2, values);

        edge_count++;
        diffs.push_back({edge_count, abs(diff2 - diff1)});
    }
    
    std::sort(diffs.begin(), diffs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });
    
    return diffs.front().first; // .𝘴𝘦𝘤𝘤𝘰𝘯𝘥 to get minimum diff
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string data_temp_temp;
    getline(cin, data_temp_temp);

    vector<string> data_temp = split(rtrim(data_temp_temp));

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        int data_item = stoi(data_temp[i]);

        data[i] = data_item;
    }

    vector<vector<int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
        edges[i].resize(2);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    int result = cutTheTree(data, edges);

    cout<<result<<"\n";

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
1. 5       list of edges[] of size n = 5
2. 1 6     edges = [[1, 6],[2, 7], [3, 8], [4,9], [2, 6]]
3. 2 7
4. 3 8
5. 4 9
6. 2 6

Output:
7. 2 4 <components with: minimum nodes>1; biggest number of nodes> 
*/

