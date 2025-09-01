#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <set>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    set<pair<int,int>> obs;
    for (auto &o : obstacles) {
        obs.insert({o[0], o[1]});
    }

    vector<pair<int,int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    int count = 0;

    for (auto [dr, dc] : directions) {
        int r = r_q + dr;
        int c = c_q + dc;

        while (r >= 1 && r <= n && c >= 1 && c <= n && !obs.count({r,c})) {
            count++;
            r += dr;
            c += dc;
        }
    }

    return count;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string second_multiple_input_temp;
    getline(cin, second_multiple_input_temp);

    vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

    int r_q = stoi(second_multiple_input[0]);

    int c_q = stoi(second_multiple_input[1]);

    vector<vector<int>> obstacles(k);

    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        string obstacles_row_temp_temp;
        getline(cin, obstacles_row_temp_temp);

        vector<string> obstacles_row_temp = split(rtrim(obstacles_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int obstacles_row_item = stoi(obstacles_row_temp[j]);

            obstacles[i][j] = obstacles_row_item;
        }
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

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
𝗡𝗼𝗻 𝗼𝗽𝘁𝗶𝗺𝗮𝗹: 𝗟𝗶𝗺𝗶𝘁 𝘁𝗶𝗺𝗲 𝗲𝘅𝗰𝗲𝗱𝗲𝗱 O(n^2)
void minimumBribes(vector<int> q) {
    int len = q.size();
    int bribes = 0;
    
    for (int i = 0; i<len; i++){
        int curr_bribe = 0;
        for(int j = i + 1; j<len; j++){
           if(q[i]>q[j]){
                curr_bribe++;
            }
            if (curr_bribe>2) {
                std::cout<<"Too chaotic"<<std::endl;
                return;
            }           
        }    
        bribes+=curr_bribe;  
    }
    
    std::cout<<bribes<<std::endl;
    return;
}
*/

/* 
Input format:
1. 1 <number of tests>
2. 5 <array length>
3. 1 3 2 5 4 <space separated array>

Return:
"2" <in this case or "Too chaotic" in case of 3+ bribes>
*/