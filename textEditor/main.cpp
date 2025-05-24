#include <cmath>
#include <sstream>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> hist(2);

void append(string a, vector<string>* arr){
    vector<string> did(2);
    did[0] = "2";
    did[1] = "0";

    for(char c : a){
        string str1 = {c};
        arr->push_back(str1);
        did[1] = std::to_string(std::stoi(did[1]) + 1);
    }
    
    hist =  did;
}

void erase(int a, vector<string>* arr){
    vector<string> did(2);
    did[0] = "1";
    did[1] = "";

    while (a-->0)
    {
        did[1] += arr->back();
        arr->pop_back();
    }
    
    hist =  did;
}

void print(int a, vector<string>* arr){
    std::cout<<(*arr)[a]<<std::endl;
    
}

void undo(vector<string>* arr){
    switch (std::stoi(hist[0]))
    {
    case 1:
        append(hist[1], arr);
        break;
    case 2:
        erase(std::stoi(hist[1]), arr);
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
            erase(std::stoi(cmd[1]), &txt);
            break;
        case 3:
            print(std::stoi(cmd[1]), &txt);
            break;
        case 4:
            //undo();
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
1. 4 <number of commands>
2. 1 2 <1 = enqueue number>
3. 2 <2 = deuque from head>
4. 1 5
5. 3 <3 = print head>

Output:
𝘛𝘩𝘦 𝘴𝘶𝘥𝘥𝘦𝘯 𝘳𝘦𝘢𝘭𝘪𝘻𝘢𝘵𝘪𝘰𝘯 𝘵𝘩𝘢𝘵 𝘵𝘩𝘦 𝘦𝘯𝘲𝘶𝘦𝘶𝘦 𝘪𝘴 𝘢𝘭𝘭 𝘸𝘳𝘰𝘯𝘨 𝘢𝘯𝘥 𝘵𝘩𝘢𝘵 𝘵𝘩𝘪𝘴 𝘱𝘢𝘴𝘴𝘦𝘥 𝘵𝘩𝘦 𝘵𝘦𝘴𝘵𝘴 𝘣𝘺 𝘤𝘩𝘦𝘦𝘳 𝘮𝘪𝘳𝘢𝘤𝘭𝘦. Ɛ( · — ·)3
5 <only print shows smt in terminal>

*/