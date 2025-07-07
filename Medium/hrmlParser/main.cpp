#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <map>
using namespace std;

int main() {
    
    int n, q;
    cin>>n>>q;
    cin.ignore();
    
    map<string, map<string, string>> hrml;
    string line, path = "";
    
    while (n-->0) {
        getline(cin, line);
        stringstream ss(line);
        
        string token;
        ss >> token;
        
        if(token[1]=='/'){
            size_t pos = path.rfind('.');
            if(pos!=string::npos){
                path = path.substr(0, pos);
            }else{
                path = "";
            }
        }else{
            string tag = token.substr(1);
            if(!tag.empty() && tag.back() == '>') tag.pop_back();
            
            if(!path.empty()){
                path += "." + tag;
            }else{
                path = tag;
            }
            
            string attr, eq, value;
            while (ss >> attr >> eq >> value) {    
                
                if(value.front()=='"'){
                    if(!value.empty() && value.back() == '>') value.pop_back();
                    value = value.substr(1, value.size() - 2);
                }
                 
                hrml[path][attr]=value;
            }
        }
    }
    
    while (q-->0) {
        getline(cin, line);
        size_t tilPos = line.find('~');
        string tagPath = line.substr(0,tilPos);
        string attr = line.substr(tilPos + 1);
        
        if(hrml.count(tagPath) && hrml[tagPath].count(attr)){
            cout<<hrml[tagPath][attr]<<endl;
        }else{
            cout<<"Not Found!"<<endl;
        }
    }
       
    return 0;
}


/* 
Input format:
 1. 4 3
 2. <tag1 value = "HelloWorld">
 3. <tag2 name = "Name1">
 4. </tag2>
 5. </tag1>
 6. tag1.tag2~name
 7. tag1~name
 8. tag1~value

Output:
 9. Name1
10. Not Found!
11. HelloWorld

*/