#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <set>
#include <climits>  
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumLoss' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts LONG_INTEGER_ARRAY price as parameter.
 */

long minimumLoss(vector<long> price) {
    long minDiff = INT_MAX;
    set<long> pset(price.begin(), price.end());
    
    for(int i = 0; i<price.size()-1; i++){
        auto it = pset.lower_bound(price[i]);
        long tmp = *it;
        
        if(it!=pset.begin()){
            it--;
            long k = *it;
            minDiff=min(minDiff, abs(price[i]-k));
        }
        pset.erase(tmp);
    }    
    
    
    return minDiff;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string price_temp_temp;
    getline(cin, price_temp_temp);

    vector<string> price_temp = split(rtrim(price_temp_temp));

    vector<long> price(n);

    for (int i = 0; i < n; i++) {
        long price_item = stol(price_temp[i]);

        price[i] = price_item;
    }

    long result = minimumLoss(price);

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