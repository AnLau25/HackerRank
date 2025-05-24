#include <cmath>
#include <sstream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


void append(string a, vector<string>*){
    
    
}

void erase(string a, vector<string>*){
    
    
}

void print(int a, vector<string>*){
    
}

void undo(int a, vector<string>*){
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    vector<vector<std::string>> cmds;
    vector<char> txt;
    vector<string> hist(2);
    
    int counter = 0;
    std::cin>>counter;
    std::cin.ignore();
    
        while(counter-->0)
    {   
        std::string line;
        std::getline(std::cin, line); 
        std::istringstream iss(line);

        vector<std::string> cmd;
        std::string val;

        while (iss>>val){
            cmd.push_back(val);
        }

        cmds.push_back(cmd);
        
        
       
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