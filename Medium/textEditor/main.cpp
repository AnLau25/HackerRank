#include <cmath>
#include <sstream>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<string>> hist;

void append(string a, vector<string>* arr){
    vector<string> did(2);
    did[0] = "2";
    did[1] = "0";

    for(char c : a){
        string str1 = {c};
        arr->push_back(str1);
        did[1] = std::to_string(std::stoi(did[1]) + 1);
    }  
    
    hist.push_back(did);
}

void remove(int a, vector<string>* arr){
    vector<string> did(2);
    did[0] = "1";
    did[1] = "";

    while (a-->0)
    {
        did[1] = arr->back() + did[1];
        arr->pop_back();
    }

    hist.push_back(did);
}

void print(int a, vector<string>* arr){
    std::cout<<(*arr)[a-1]<<std::endl;
    
}

void undo(vector<string>* arr){
    if (hist.empty()) return;
    vector<string> did = hist.back();
    hist.pop_back();

    switch (std::stoi(did[0]))
    {
    case 1:
        append(did[1], arr);
        hist.pop_back();
        break;
    case 2:
        remove(std::stoi(did[1]), arr);
        hist.pop_back();
    default:
        break;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    vector<vector<std::string>> cmds;
    vector<string> txt;
    
    int counter = 0;
    std::cin>>counter;
    std::cin.ignore();
    
    while(counter-->0){   
        std::string line;
        std::getline(std::cin, line); 
        std::istringstream iss(line);

        vector<std::string> cmd;
        std::string val;

        while (iss>>val){
            cmd.push_back(val);
        }

        cmds.push_back(cmd);
    }
    
    for(vector<std::string>cmd : cmds){

        switch (std::stoi(cmd[0]))
        {
        case 1:
            append(cmd[1], &txt);
            break;
        case 2:
            remove(std::stoi(cmd[1]), &txt);
            break;
        case 3:
            print(std::stoi(cmd[1]), &txt);
            break;
        case 4:
            undo(&txt);
            break;
        default:
            std::cout<<cmd[0]<<"not a command"<<std::endl;
            break;
        }
    }
        
       
    return 0;
}

/* 
Input format:
1. 6 <number of commands>
2. 1 abcd <append string "abcd">
3. 2 2 <remove the 2 last elements>
4. 3 2 <print the 2nd element>
5. 4 <undo latest mod>
6. 3 4 <print the 4th element>

Output: Ɛ( · — ·)3
b <only print shows smt in terminal>
d
*/