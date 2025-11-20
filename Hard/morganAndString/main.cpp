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

/*
 * Complete the 'morganAndString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
 */
bool comp(string a, int idxa, string b, int idxb){
    while(idxa<a.size() && idxb<b.size()){
        if (a[idxa]-'A' < b[idxb]-'A') return true;
        else if (a[idxa]-'A' > b[idxb]-'A') return false;   
        
        idxa++;
        idxb++;
    }
    
    return idxa == a.size()? false : true;
}

string morganAndString(string a, string b) {
    string min = "";
    int idxa = 0, idxb = 0, lna = a.size(), lnb = b.size();
    
    while(idxa<lna && idxb<lnb){
        
        int vala = a[idxa] - 'A';
        int valb = b[idxb] - 'A';
            
        if(vala<valb){
            min+=a[idxa];
            idxa++;
        }else if (vala>valb){
            min+= b[idxb];
            idxb++;
         }else{
            if(comp(a, idxa + 1, b, idxb + 1)){
                min+= a[idxa];
                idxa++;
                while (idxa<lna && a[idxa]==a[idxa-1]) {
                    min+= a[idxa];
                    idxa++;
                }
            }else{
                min+= b[idxb];
                idxb++;
                while (idxb<lnb && b[idxb]==b[idxb-1]) {
                    min+= b[idxb];
                    idxb++;
                }
            }
         }
        
    } 
    
    if(idxa<lna){
        min+= a.substr(idxa);
    }
    
    if(idxb<lnb){
        min+= b.substr(idxb);
    }
    
    return min;
}


int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = morganAndString(a, b);

        cout << result << "\n";
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

/* 
 1. 4 4 2        <rows m = 4, columns n = 4, rotation factor r = 2>
 2. 1 2 3 4      <matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]>
 3. 5 6 7 8
 4. 9 10 11 12
 5. 13 14 15 16

Output:
 6. 3 4 8 12     <matrix rotated by r ↓>
 7. 2 11 10 16
 8. 1 7 6 15
 9. 5 9 13 14
*/