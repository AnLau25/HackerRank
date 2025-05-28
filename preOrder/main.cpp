#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
                }

               return root;
           }
        }

/* you only have to complete the function given below.*/


    void preOrder(Node *root) {
       
        if (root == nullptr){
                return;
        }

        std::cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);     
    }
    
    

}; //End of Solution


/* 
Input format:
1. 6 <length of array>
2. 5 5 6 7 6 5 <space separated array>
*/