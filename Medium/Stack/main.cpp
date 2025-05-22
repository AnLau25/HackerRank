#include <cmath>
#include <sstream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


struct StackNode{
    StackNode* next;
    int value;
    
    StackNode(int node_value){
        this->value = node_value;
        this->next = nullptr;
    }
};

class Stack {
public:
    StackNode* head;
    StackNode* tail;
    
    Stack(){
        this->head = nullptr; 
        this->tail = nullptr;
    }
    
    void enqueue (int node_value){
        StackNode* node = new StackNode(node_value);
        
        if (!this->head) {
            this->head = node;
        }else{
            this->tail->next = node;
        }

        this->tail = node;
        
    }

    void dequeue (){
        if(this->head->next){
            this->head = this->head->next;
        }else{
            this->head = nullptr;
        }
    }

    void print (){
        if(this->head){
            int num = this->head->value;
            std::cout<<num<<std::endl;
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    Stack* stacked = new Stack();
    
    vector<vector<int>> cmds;
    
    int counter = 0;
    std::cin >> counter;
    std::cin.ignore();//Makes sure cin ignores next line (since it's getline) 

    while(counter-->0)
    {   
        std::string line;
        std::getline(std::cin, line); //Takes a full line of code
        std::istringstream iss(line);

        vector<int> com;
        int val;

        while (iss>>val){//Pushes the input into command
            com.push_back(val);
        }

        cmds.push_back(com);//Com to commands
    }

    for(vector<int> com : cmds)//Exhecutes the commands
    {
        if (com[0]==1){
            stacked->enqueue(com[1]);
        }else if (com[0]==2){
            stacked->dequeue();
        }else if (com[0]==3){
            stacked->print();
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
5 <only print shows smt in terminal>
*/