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
 * Complete the 'minimumBribes' function below.
 *
 * The function accepts INTEGER_ARRAY q as parameter.
 */

 //O(n) version
void minimumBribes(vector<int> q) {
    int bribes = 0;
    for (int i = 0; i < q.size(); i++) {
        //Checa si i no se saltó más de 2 puestos
        if (q[i] - (i + 1) > 2) {
            cout << "Too chaotic" << endl;
            return;
        }

        //max() ensures that we dont get out of range
        //Calculates how many people have bribed i (ie cuantos más grandes hay 𝘥𝘦𝘭𝘢𝘯𝘵𝘦 de i)
        //Incomodo pk el 𝘤𝘩𝘦𝘤𝘬 𝘥𝘦 𝘢𝘳𝘳𝘪𝘷𝘢 𝘮𝘪𝘳𝘢 𝘥𝘦𝘵𝘳𝘢𝘴 𝘥𝘦 𝘪 y esto 𝘮𝘪𝘳𝘢 𝘥𝘦𝘭𝘢𝘯𝘵𝘦 𝘥𝘦 𝘪
        for (int j = max(0, q[i] - 2); j < i; j++) {
            if (q[j] > q[i]) {
                bribes++;
            }
        }
    }

    cout << bribes << endl;
}


int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split(rtrim(q_temp_temp));

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

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