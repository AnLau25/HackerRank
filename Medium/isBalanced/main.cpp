#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'isBalanced' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */
template <typename T>
struct StackNode {
    T value;
    StackNode<T>* next;

    StackNode(T node_value) {
        this->value = node_value;
        this->next = nullptr;
    }
};

template<typename  T>
class Stack {
private:
    StackNode<T>* head;
    
public:  
    
    Stack(){
        this->head = nullptr;
    }
    
    void push (T node_value){
        StackNode<T>* node = new StackNode<T>(node_value);
        
        if (!head) {
            head = node;
        }else{
            node->next = head; //Current head becomes the next to node
            head = node;//Node becomes new current head
        }        
    }

    T pop (){ 
        if (!head) {
            throw std::runtime_error("Stack underflow");
        }
               
        StackNode<T>* dummy = head; //Store ref to head
        T value = dummy->value;
        head = head->next; //break head from stack by making next the new head
        
        delete dummy; //delete the ref to old head
        return value; //return value
    }

    void print (){
        if(this->head){
            T num = this->head->value;
            std::cout<<num<<std::endl;
        }
    }
    
    bool isEmpty(){
        return head==nullptr;
    }
};

string isBalanced(string s) {
    Stack<char> balance;
    
    for (char c : s){
        
        if (c=='{' || c=='[' || c=='('){
            balance.push(c);
        }else if (c=='}' || c==']' || c==')'){
            if (balance.isEmpty()) return "NO";
            
            char top = balance.pop();//Cannot simply return it, you gotta make it into char 
            std::string test = std::string(1, top) + c;
             
            if (!(test=="{}" || test=="[]" || test=="()")){
               return "NO";
            }
        }
    }
    
    if (!(balance.isEmpty())){
        return "NO";
    }
    
    return "YES";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        std::cout<<isBalanced(s)<<std::endl;

        //fout << result << "\n";
    }

    //fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); })
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

/* 
Input format:
1. 1 <number of strings to test>
2. [{(5 5 6 7 6 5)}] <string to test>

Return:
YES <printed to terminal, NO if is not balanced, ie {[)]}>
*/