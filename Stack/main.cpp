#include <cmath>
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
        if(!this->head){
            this->head = this->head->next;
        }
    }

    void print (){
        std::cout<<this->head->value<<std::endl;
    }
    
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int counter=0;
    vector<int> cmds;
    std::cin>>counter;
    Stack* stacked = new Stack();

    for(int i = 0; i<counter; i++)
    {   
        int com = 0;

        std::cin>>com;

        cmds.push_back(com);
    }

    while (counter!=0)
    {
        
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