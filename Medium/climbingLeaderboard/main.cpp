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
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

/*
Runtime error, too slo (Liam Lawson much)

void cleance(vector<int> *array){
    std::sort(array->begin(), array->end(), std::greater<int>());
    
    auto dups = std::unique(array->begin(), array->end());
    array->erase(dups, array->end());
}

vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
    vector<int> new_rank;
    cleance(&ranked);
    
    for(int n : player){
        ranked.push_back(n);
        cleance(&ranked);
        
        auto idx = std::find(ranked.begin(), ranked.end(), n);
        
        new_rank.push_back(std::distance(ranked.begin(), idx)+1);
    }
    
    return new_rank;
}
*/

// I was just being extra causious, sue me Ɛ( · — ·)3
vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
    vector<int> new_rank;
    sort(ranked.begin(), ranked.end(), greater<int>());
    ranked.erase(unique(ranked.begin(), ranked.end()), ranked.end());
    
    for(int n : player){
        ranked.push_back(n);
                
        auto it = lower_bound(ranked.begin(), ranked.end(), n, greater<int>());;
        int idx = std::distance(ranked.begin(), it)+1;
        new_rank.push_back(idx);
    }
    
    return new_rank;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string ranked_count_temp;
    getline(cin, ranked_count_temp);

    int ranked_count = stoi(ltrim(rtrim(ranked_count_temp)));

    string ranked_temp_temp;
    getline(cin, ranked_temp_temp);

    vector<string> ranked_temp = split(rtrim(ranked_temp_temp));

    vector<int> ranked(ranked_count);

    for (int i = 0; i < ranked_count; i++) {
        int ranked_item = stoi(ranked_temp[i]);

        ranked[i] = ranked_item;
    }

    string player_count_temp;
    getline(cin, player_count_temp);

    int player_count = stoi(ltrim(rtrim(player_count_temp)));

    string player_temp_temp;
    getline(cin, player_temp_temp);

    vector<string> player_temp = split(rtrim(player_temp_temp));

    vector<int> player(player_count);

    for (int i = 0; i < player_count; i++) {
        int player_item = stoi(player_temp[i]);

        player[i] = player_item;
    }

    vector<int> result = climbingLeaderboard(ranked, player);

    for (size_t i = 0; i < result.size(); i++) {
        cout<<result[i];

        if (i != result.size() - 1) {
            cout<<"\n";
        }
    }

    std::cout<<"\n";

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
1. 7 <# of already ranked scores>
2. 100 100 50 40 40 20 10 <space separated scores array>
3. 4 <# of scores to rank>
4. 5 25 50 120 <space separated array of scores>

Output:
5. 6 <rank of the latest ranked score>
7. 4
8. 2
9. 1 
*/