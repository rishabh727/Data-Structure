// 1. Write a program to implement singly linked list as an ADT that supports the following operations:
//     i. Insert an element x at the beginning of the singly linked list
//     ii. Insert an element x at i position in the singly linked list
//     iii. Remove an element from the beginning of the doubly linked list
//     iv.Remove an element from i position in the singly linked list.
//     vi.Search for an element x in the singly linked list and return its pointer

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

class LinkedList {
    Node* head;
public:
    LinkedList() : head(NULL) {} // Initialize head to NULL

    void display() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->val << "->";
            temp = temp->next;
        }
        cout << "Null\n";
    }

    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) { // If the list is empty
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void insertAtPosition(int val, int pos) {
        Node* newNode = new Node(val);
        if (pos == 0) {
            insertAtHead(val);
            return;
        }
        Node* temp = head;
        int currentPos = 0;
        while (temp != NULL && currentPos != pos - 1) {
            temp = temp->next;
            currentPos++;
        }
        if (temp == NULL) {
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
        head = head->next;
        delete temp; // Use delete instead of free
    }

    void deleteAtTail() {
        if (head == NULL) return; // If the list is empty
        if (head->next == NULL) { // If there's only one element
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        delete temp->next; // Use delete instead of free
        temp->next = NULL;
    }

    void deleteAtPosition(int pos) {
        if (pos == 0) {
            deleteAtHead();
            return;
        }
        Node* temp = head;
        int curPos = 0;
        while (temp != NULL && curPos != pos - 1) {
            temp = temp->next;
            curPos++;
        }
        if (temp == NULL || temp->next == NULL) {
            cout << "Position out of bounds." << endl;
            return;
        }
        Node* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete; // Use delete instead of free
    }
    
    void concatenate(LinkedList& other) {
    if (other.head == NULL) return;

    if (head == NULL) { 
        head = other.head;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = other.head; 
    }
}

};

int main() {
    LinkedList list1;
    list1.insertAtHead(7);
    list1.insertAtHead(9);
    list1.insertAtTail(3);
    list1.insertAtPosition(8, 0);
    list1.insertAtPosition(12, 4);
    list1.display();

    LinkedList list2;
    list2.insertAtHead(7);
    list2.insertAtTail(5);
    list2.insertAtTail(1);
    list2.insertAtTail(2);
    list2.insertAtTail(7);
    list2.display();
    
    list1.concatenate(list2);
    list1.display();

    
    return 0;
}
