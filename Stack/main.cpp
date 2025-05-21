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
            std::cout<<this->head->value<<std::endl;
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    Stack* stacked = new Stack();
    
    int counter=0;
    vector<vector<int>> cmds;
    std::cin>>counter;
    


    for(int i = 0; i<counter; i++)
    {   
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);

        vector<int> com(2);
        int val;

        while (iss>>val){
            com.push_back(val);
        }
        
        std::cin>>com[0]>>com[1];

        cmds.push_back(com);
    }

    for(vector<int> com : cmds)
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
1. 1 <number of test cases>
2. 3 <numbers of elements in list 1>
3. 1 <enter-separated elements of list 1>
4. 2
5. 3
6. 2 <numbers of elements in list 2>
7. 1 <enter-separated elements of list 2>
8. 2

Output:
1 1 2 2 3 4 5
*/