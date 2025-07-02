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
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    if (cities.empty() || c_lib <= c_road) return (long)n * c_lib;

    map<int, stack<int>> cityMap;
    for (vector<int> road : cities) {
        int city1 = road[0], city2 = road[1];
        cityMap[city1].push(city2);
        cityMap[city2].push(city1);
    }

    vector<bool> visited(n + 1, false); 
    long libs = 0, rds = 0;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            libs++;
            stack<int> neighbors;
            neighbors.push(i);
            visited[i] = true;

            while (!neighbors.empty()) {
                int curr = neighbors.top();
                neighbors.pop();

                while (!cityMap[curr].empty()) {
                    int neighbor = cityMap[curr].top();
                    cityMap[curr].pop();

                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        neighbors.push(neighbor);
                        rds++;
                    }
                }
            }
        }
    }

    return libs * c_lib + rds * c_road;
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

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        cout<<result<<"\n";
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
1. 1        <number of tests = 1>
2. 3 3 2 1  <number of cities = 3, number of city conections = 3, c_lib = 2, c_road = 1
3. 1 2      <cities(3) = [[1, 2], [3, 1], [2, 3]]>
4. 3 1
5. 2 3

Output:
6. 4 <minimum cost so all libs have a library> 
*/
