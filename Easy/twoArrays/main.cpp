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
 * Complete the 'twoArrays' (one int) function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 *  3. INTEGER_ARRAY B
 */

 //... This shoulve been a runtime err... pero bueh.
/*string twoArrays(int k, vector<int> A, vector<int> B) {
    int b = B.size()-1;
    std::sort(A.begin(),A.end());
    std::sort(B.begin(),B.end());
    
    while(A.size()>1 && B.size()>1){
        
        if(A[0]+B[b]>=k){
            A.erase(A.begin());
            B.erase(B.begin()+b);
            b = B.size()-1;
        }else{
            b--;
        }
        
        if(b==-1){
            return "NO";
        }
    }
    
    if(A.size()!=B.size()){
        return "NO";
    }
    
    if(!(A[0]+B[0]>=k)){
        return "NO";
    }
    
    return "YES";
}*/

//So... I had solved this one before
string twoArrays(int k, vector<int> A, vector<int> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());
    
    for(int i = 0; i<A.size(); i++){
        if(A[i]+B[i]<k){
            return "NO";
        }
    }
    
    return "YES";
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

        int k = stoi(first_multiple_input[1]);

        string A_temp_temp;
        getline(cin, A_temp_temp);

        vector<string> A_temp = split(rtrim(A_temp_temp));

        vector<int> A(n);

        for (int i = 0; i < n; i++) {
            int A_item = stoi(A_temp[i]);

            A[i] = A_item;
        }

        string B_temp_temp;
        getline(cin, B_temp_temp);

        vector<string> B_temp = split(rtrim(B_temp_temp));

        vector<int> B(n);

        for (int i = 0; i < n; i++) {
            int B_item = stoi(B_temp[i]);

            B[i] = B_item;
        }

        std::cout<<twoArrays(k, A, B)<<std::endl;

        //fout << result << "\n";
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
1. 1 <no of test cases>
2. 3 10 <q=3,length of arrays; k=10>
3. 2 3 1 <space separated array>
4. 9 8 7 <space separated array>

Output:
5. YES <cause there is an arrangement st. ∀ i ∈ ArrA, ArrB, ArrA[i] + ArrB[i] >= k>
*/