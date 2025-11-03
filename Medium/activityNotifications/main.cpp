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
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */
double median(vector<int> trail, int d) {
    int sum = 0;
    int m1 = -1, m2 = -1;
    
    if (d % 2 == 1) {
        int mid = d / 2 + 1;
        for (int i = 0; i < 201; i++) {
            sum += trail[i];
            if (sum >= mid) return i;
        }
    } else {
        int mid1 = d / 2, mid2 = d / 2 + 1;
        for (int i = 0; i < 201; i++) {
            sum += trail[i];
            if (m1 == -1 && sum >= mid1) m1 = i;
            if (sum >= mid2) { m2 = i; break; }
        }
        return (m1 + m2) / 2.0;
    }
    return 0; 
}

int activityNotifications(vector<int> spent, int d) {
    vector<int> trail(201,0);
    for(int i = 0; i<d; i++){
        trail[spent[i]]++;
    }
    
    int notifs = 0;

    for (int i = d; i < spent.size(); i++) {
        double trigger = median(trail, d) * 2.0;
        
        if (spent[i] >= trigger) {
            notifs++;
        }
        
        trail[spent[i-d]]--;
        trail[spent[i]]++;
    }

    return notifs;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
 1. 9 5                 <expenditure[] size n =9, d = 5>
 2. 2 3 4 2 3 6 8 4 5   <expenditure = [2, 3, 4, 2, 3, 6, 8, 4, 5]>

Output:
 3. 2                   <number of notifications>
*/