#include <iostream>
#include <limits>
using namespace std;

struct SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;

    SinglyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
    }
};

class SinglyLinkedList {
public:
    SinglyLinkedListNode* head;
    SinglyLinkedListNode* tail;

    SinglyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void insert_node(int node_data) {
        SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

        if (!this->head) {
            this->head = node;
        } else {
            this->tail->next = node;
        }

        this->tail = node;
    }
};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ostream& out) {
    while (node) {
        out << node->data;

        node = node->next;

        if (node) {
            out << sep;
        }
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;
        delete temp;
    }
}

// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    SinglyLinkedList* result = new SinglyLinkedList();
    SinglyLinkedListNode* current1 = head1;
        SinglyLinkedListNode* current2 = head2;
    
    if (head1->data > head2->data) {
        current1 = head2;
        current2 = head1;
    }
        
    while (current1!=nullptr && current2!=nullptr) {
                
        while (current2!=nullptr && current2->data<=current1->data) {
            result->insert_node(current2->data);
            current2 = current2->next;
        }
        
        result->insert_node(current1->data);
        current1 = current1->next;
    }
    
    if (current2!=nullptr){
        current1 = current2;
    } else if (current1==nullptr && current2==nullptr) {
        return result->head;
    } 
    
    while (current1!=nullptr) {
        result->insert_node(current1->data);
        current1 = current1->next;
    }
    
    return result->head;
}

int main() {
    int tests;
    cin >> tests;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
        SinglyLinkedList* llist1 = new SinglyLinkedList();

        int llist1_count;
        cin >> llist1_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist1_count; i++) {
            int llist1_item;
            cin >> llist1_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist1->insert_node(llist1_item);
        }

        SinglyLinkedList* llist2 = new SinglyLinkedList();

        int llist2_count;
        cin >> llist2_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist2_count; i++) {
            int llist2_item;
            cin >> llist2_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist2->insert_node(llist2_item);
        }

        SinglyLinkedListNode* llist3 = mergeLists(llist1->head, llist2->head);

        print_singly_linked_list(llist3, " ", cout);
        cout << "\n";

        free_singly_linked_list(llist3);
        delete llist1;
        delete llist2;
    }

    return 0;
}