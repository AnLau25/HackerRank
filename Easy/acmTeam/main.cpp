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
 * Complete the 'acmTeam' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY topic as parameter.
 */
class BinaryString {
public:
    std::string value;

    BinaryString(const std::string& bin_str) : value(bin_str) {}

    // Overload the + operator
    BinaryString operator+(const BinaryString& other) const {
        std::string result = "";
        
        for (int i = 0; i<value.size(); i++) {
            if(value[i]=='1' || other.value[i]=='1'){
                result+="1";
            }
        }
        std::reverse(result.begin(), result.end());
        return BinaryString(result);
    }
};

vector<int> acmTeam(vector<string> topic) {
    int subjects = 0;
    int knowitalls = 0;
    std::vector<BinaryString> teams;
    std::transform(topic.begin(), topic.end(), std::back_inserter(teams), [](const std::string& s) { return BinaryString(s); });
    
    for(int i = 0; i<teams.size(); i++){
        for(int j = i+1; j<teams.size(); j++){
             BinaryString team_sum = teams[i] + teams[j];
             
             if(team_sum.value.size()>subjects){
                subjects = team_sum.value.size();
                knowitalls = 0;
             }
             
            if(team_sum.value.size()==subjects){
                knowitalls++;
             }
        }
    }
    
    
    return {subjects, knowitalls};
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> topic(n);

    for (int i = 0; i < n; i++) {
        string topic_item;
        getline(cin, topic_item);

        topic[i] = topic_item;
    }

    vector<int> result = acmTeam(topic);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

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
 1. 4 5 <number of  attendees, number of subjects>
 2. 10101 <topis mastered by each atendee ↓>
 3. 11100
 4. 11010
 5. 00101

Output:
 6. 5 <number of subjects mastered by all atendees>
 7. 2 <number of teams that master ↑ subjects>
*/