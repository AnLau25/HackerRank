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
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */

vector<int> componentsInGraph(vector<vector<int>> gb) {
    if (gb.empty()) return {0, 0};
    
    map<int, stack<int>> links;
    
    for (vector<int> arista : gb){
        int ar1 = arista[0], ar2 = arista[1];
        links[ar1].push(ar2);
        links[ar2].push(ar1);
    }
    
    vector<int> comp_size;
    map<int, bool> visited;
    
    for(auto& [node, _] : links){
        if(!visited[node]){
            int nodes = 0;
            stack<int> neighbors;
            neighbors.push(node);
            visited[node] = true;
            
            while (!neighbors.empty()) {
                int curr = neighbors.top();
                neighbors.pop();
                nodes++;
                
                while (!links[curr].empty()) {
                    int neighbor = links[curr].top();
                    links[curr].pop();
                    
                    if(!visited[neighbor]){
                        visited[neighbor] = true;
                        neighbors.push(neighbor);
                    }
                }
            }
            
            if(nodes>1){
                comp_size.push_back(nodes);
            }
        
        }
    }
    
    sort(comp_size.begin(), comp_size.end());
    
    
    int smallest = comp_size.front();
    int biggest = comp_size.back();
    
    return {smallest, biggest};

}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> gb(n);

    for (int i = 0; i < n; i++) {
        gb[i].resize(2);

        string gb_row_temp_temp;
        getline(cin, gb_row_temp_temp);

        vector<string> gb_row_temp = split(rtrim(gb_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int gb_row_item = stoi(gb_row_temp[j]);

            gb[i][j] = gb_row_item;
        }
    }

    vector<int> result = componentsInGraph(gb);

    for (size_t i = 0; i < result.size(); i++) {
        cout<<result[i];

        if (i != result.size() - 1) {
            cout<<" ";
        }
    }

    cout<<"\n";

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
1. 1        <number of tests = 1>
2. 3 3 2 1  <number of cities = 3, number of city conections = 3, c_lib = 2, c_road = 1
3. 1 2      <cities(3) = [[1, 2], [3, 1], [2, 3]]>
4. 3 1
5. 2 3

Output:
6. 4 <minimum cost so all libs have a library> 
*/

