// 3. Write a program to implement circular linked list as an ADT which supports the following operations:
// i. Insert an element x in the list
// ii. Remove an element from the list
// iii. Search for an element x in the list and return its pointer


#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;

    Node(int data) {
        val = data;
        next = NULL;
    }
};

class CircularLinkedList {
    Node* head;
public:
    CircularLinkedList() : head(NULL) {} // Initialize head to NULL

    void display() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        do {
            cout << temp->val << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head: " << head->val << ")\n";
    }

    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            newNode->next = head; // Point to itself
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode; 
            newNode->next = head; 
            head = newNode; 
        }
    }

    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            newNode->next = head; 
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode; 
            newNode->next = head; 
        }
    }

    void insertAtPosition(int val, int pos) {
        Node* newNode = new Node(val);
        if (pos == 0) {
            insertAtHead(val);
            return;
        }
        Node* temp = head;
        int currentPos = 0;
        while (currentPos < pos - 1 && temp->next != head) {
            temp = temp->next;
            currentPos++;
        }
        if (currentPos != pos - 1) {
            cout << "Position out of bounds." << endl;
            delete newNode; // Clean up newNode since we won't use it
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    void deleteAtHead() {
        if (head == NULL) return; // If the list is empty
        Node* temp = head;
        if (temp->next == head) { // Only one element
            delete head;
            head = NULL;
        } else {
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            head = head->next; 
            last->next = head; 
            delete temp; 
        }
    }

    void deleteAtTail() {
        if (head == NULL) return; 
        if (head->next == head) { // Only one element
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head;
        while (temp->next->next != head) {
            temp = temp->next; // Traverse to the second last node
        }
        delete temp->next; 
        temp->next = head; 
    }

    void deleteAtPosition(int pos) {
        if (pos == 0) {
            deleteAtHead();
            return;
        }
        Node* temp = head;
        int curPos = 0;
        while (curPos < pos - 1 && temp->next != head) {
            temp = temp->next;
            curPos++;
        }
        if (curPos != pos - 1 || temp->next == head) {
            cout << "Position out of bounds." << endl;
            return;
        }
        Node* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next; // Bypass the node to delete
        delete nodeToDelete; // Free memory
        
    }
};

int main() {
    CircularLinkedList list;
    list.insertAtHead(7);
    list.insertAtHead(9);
    list.insertAtTail(3);
    list.insertAtPosition(8, 0);
    list.insertAtPosition(12, 4);
    list.display(); // Display the list

    list.deleteAtHead(); // Remove head
    list.display(); // Display the list

    list.deleteAtTail(); // Remove tail
    list.display(); // Display the list

    list.deleteAtPosition(1); // Remove node at position 1
    list.display(); // Display the list

    return 0;
}
