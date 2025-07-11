#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
#include <map>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache{
    private:
        void moveToHead(Node* node){
            if(node==head) return;
            removeNode(node);
            addNode(node);
        }
        
        void removeNode(Node* node){
            if (node->prev) node->prev->next = node->next;
            if (node->next) node->next->prev = node->prev;
            
            if (node==head) head = node->next;
            if (node==tail) tail = node->prev;   
        }
        
        void addNode(Node* node){
            node->prev = nullptr;
            node->next = head;
            if (head) head->prev = node;
            head=node;
            if (!tail) tail = node;            
        }
    
    public:
        LRUCache(int _cp){
            cp = _cp;
            head = tail = nullptr;
        }
        
        int get(int key){
            
            if(mp.find(key)!=mp.end()){
                
                Node* temp = mp[key];
                moveToHead(temp);
                
                return mp[key]->value;    
            }
            return -1;
        }
        
        void set(int key, int val){
            
            if(mp.find(key)!=mp.end()){
                Node* temp = mp[key];
                temp->value=val;
                moveToHead(temp);
                
            } else {
                Node* temp = new Node(key, val);
                
                if(mp.size()==cp){
                    mp.erase(tail->key);
                    removeNode(tail);
                }
                
                addNode(temp);
                mp[key]=temp;
            }
        }
    
};

int main() {
    int n, capacity,i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for(i=0;i<n;i++) {
        string command;
        cin >> command;
        if(command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } else if(command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key,value);
        }
    }
    return 0;
}

/* 
1. 5 3 <no of elements in the array, no of queries>
2. 1 2 100 <queries where range is {a,b} and k is the value to add>
3. 2 5 100 <ie, a=2, b=5 & k=100>
4. 3 4 100

Output:
5. 200 <maximum number in the array after al the sum operations>
*/