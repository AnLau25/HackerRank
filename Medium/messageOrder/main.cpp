#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

class Message {
    int msg_id;
    string msg;

public: 
    static int id_count;
    
    Message() = default;
    Message(string _msg) {
        id_count++;
        msg_id = id_count;
        msg = _msg;
    }
    const string& get_text() {
        return msg;
    }
    
    const int& get_id(){
        return msg_id;
    }
    
    bool operator<(Message& other_msg){
        int other_id = other_msg.get_id();

        if(msg_id<other_id){
            return true;
        }
        return false;
    }  
};
int Message::id_count=0;

class MessageFactory:Message {
public:
    MessageFactory() = default;
    
    Message create_message(const string& text) {
        Message new_msg = Message(text);
        return new_msg;
    }
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());         
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};



int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
}

/* 
Input format:
1. 4 <length of array>
2. 2 <k=2, number of integers to concider for unfairnes>
3. 7 <numbers of the array ↓>
4. 1
5. 2
6. 4

Output:
7. 1 <minimum unfairness in a sub-array of size k>
     <[2,1]; 2-1=1 in this case>
*/