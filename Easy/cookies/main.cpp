#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <queue>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */

int cookies(int k, vector<int> A) {
    //std::priority_queue ussualy inits with 𝘴𝘵𝘥::𝘱𝘳𝘪𝘰𝘳𝘪𝘵𝘺_𝘲𝘶𝘦𝘶𝘦<𝘪𝘯𝘵> 𝘱𝘲; as a 𝘔𝘢𝘹𝘏𝘦𝘢𝘱
    //By default it uses 𝘴𝘵𝘥::𝘭𝘦𝘴𝘴<𝘛> internaly, meaning MaxHeap cause 𝘮𝘢𝘹 𝘯𝘶𝘮𝘣𝘦𝘳 𝘪𝘴 𝘬𝘦𝘱𝘵 𝘰𝘯 𝘵𝘰𝘱
    //Init like this for 𝘔𝘪𝘯𝘏𝘦𝘢𝘱, where we use 𝘴𝘵𝘥::𝘨𝘳𝘦𝘢𝘵𝘦𝘳<𝘪𝘯𝘵> as custom comparator
    //𝘴𝘵𝘥::𝘷𝘦𝘤𝘵𝘰𝘳<𝘪𝘯𝘵> temporarely holds .𝘱𝘶𝘴𝘩(𝘯𝘦𝘸_𝘷𝘢𝘭𝘶𝘦) so it can be sorted
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(A.begin(), A.end());
    int mix = 0;
    
    while (minHeap.size()>=2 && minHeap.top()<k) {
        int cookie1 = minHeap.top();
        minHeap.pop();
        int cookie2 = minHeap.top();
        minHeap.pop();
        
        int neoCookie = cookie1 + 2*cookie2;
        minHeap.push(neoCookie);
        
        mix++;
        
        if (minHeap.top()>=k) {
            return mix;
        }
    }

     if(minHeap.top()>k){
        return mix;
    }
    
    return -1;
}


/*
Fancy, but causes run time error.
int cookies(int k, vector<int> A) {
    if((A.size()==1 && A[0]<k) || A.empty()){
        return -1;
    }
    
    bool small = true;
    int mix = 0;
    
    while (small) {
        sort(A.begin(), A.end());
        
        if(A[0]>=k){
            small = false;
        }else if(A.size()==1 && A[0]<k){
            mix = -1;
            small = false;
        }else{
            int cookie1 = A[0];
            int cookie2 = A[1];
            
            A.erase(A.begin(), A.begin() + 2);
            
            int neoCookie = cookie1 + 2*cookie2;
        
            A.push_back(neoCookie);

            mix++;
        }        
    }
    return mix;
}
*/

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

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

    std::cout<<cookies(k, A)<<std::endl;

    //fout << result << "\n";

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
1. 5 7 <array length = 5, k = 7>
2. 1 2 3 4 5 <space separated array>

Output:
3 <number of iterations so, Ɐ n in array A n>=k>

*/