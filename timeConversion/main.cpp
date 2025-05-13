#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip> 
using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

 string timeConversion(string s) {
    std::string ans;    
    
    std::istringstream iss(s);
    std::vector<std::string> parts;
    std::string part;
    while(std::getline(iss, part, ':')){
        parts.push_back(part);
    }
    
    std::string secconds;
    for (char c : parts[2]){
        if (std::isdigit(c)){
            secconds += c;
        }
        
        if ((!std::isdigit(c)) && c == 'A'){
            if(parts[0]=="12"){
                ans = "00:" + parts[1] + ":" + secconds;
                break;
            }
            ans = parts[0] + ":" + parts[1] + ":" + secconds;
        }
        
        if ((!std::isdigit(c)) && c == 'P'){
            if(parts[0]=="12"){
                ans = "12:" + parts[1] + ":" + secconds;
                break;
            }
            ans = std::to_string((std::stoi(parts[0])+12)) + ":" + parts[1] + ":" + secconds;
        }
    }
    
    return ans;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    std::cout<<result<<std::endl;

    //fout << result << "\n";
    //fout.close();

    return 0;
}

/* 
Input format:
1. 6 <length of array>
2. -2 -3 -5 0 0 1 <space separated array>
*/