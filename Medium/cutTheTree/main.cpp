#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <numeric>   // for accumulate
#include <climits>   // for INT_MAX
#include <map>
#include <bits/stdc++.h> 
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
map<int, vector<int>> adj;
vector<bool> visited(100001);
vector<int> sum(100001); 
 
int dfs(int node, vector<int>& data){
    int ret = data[node-1]; // Start with the node's own value
    visited[node] = true; // Mark as visited
    
    for(int next : adj[node]){
        // If not visited, continue DFS
        if(!visited[next]){
            ret += dfs(next, data);
        }
    }
    return sum[node] = ret;
}

int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    int mindiff = INT_MAX;
    int total = accumulate(data.begin(), data.end(), 0);
    
    // Build adjacency list
    for (vector<int> e : edges){
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    
    // Perform DFS to calculate subtree sums
    dfs(1, data);
    for(int i = 2; i<=data.size(); i++){
        // Calculate the difference if we cut the edge leading to subtree rooted at i
        int diff = abs(total - 2*sum[i]); 
        mindiff = min(mindiff, diff);
    }
    
    return mindiff;
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
 1. 6                           <data[] size n = 6>
 2. 100 200 100 500 100 600     <data = [100, 200, 100, 500, 100, 600]>
 3. 1 2                         <edges = [[1, 2], [2, 3], [2, 5], [4, 5], [5, 6]]>
 4. 2 3
 5. 2 5
 6. 4 5
 7. 5 6

Output:
 8. 400                         <minimum difference between two subtrees after cutting one edge>                           
*/