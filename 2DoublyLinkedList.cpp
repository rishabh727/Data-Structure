// 2. Write a program to implement doubly linked list as an ADT that supports the following operations:
//     i.Insert an element x at the beginning of the doubly linked list
//     ii. Insert an element x at the end of the doubly linked list
//     iii. Remove an element from the beginning of the doubly linked list
//     iv.Remove an element from the end of the doubly linked list

#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* prev; // Pointer to the previous node

    Node(int data) {
        val = data;
        next = NULL;
        prev = NULL; // Initialize prev to NULL
    }
};

class DoublyLinkedList {
    Node* head;
public:
    DoublyLinkedList() : head(NULL) {} // Initialize head to NULL , Null will

    void display() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->val << " <-> ";
            temp = temp->next;
        }
        cout << "Null\n";
    }

    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode; // Update the previous pointer of the old head
        }
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
        newNode->prev = temp; // Set the previous pointer of the new tail
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
        if (temp->next != NULL) {
            temp->next->prev = newNode; // Update the previous pointer of the next node
        }
        temp->next = newNode;
        newNode->prev = temp; // Set the previous pointer of the new node
    }

    void deleteAtHead() {
        if (head == NULL) return; // If the list is empty
        Node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL; // Update the previous pointer of the new head
        }
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
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->prev->next = NULL; // Remove the last node
        delete temp; // Use delete instead of free
    }

    void deleteAtPosition(int pos) {
        if (pos == 0) {
            deleteAtHead();
            return;
        }
        Node* temp = head;
        int curPos = 0;
        while (temp != NULL && curPos != pos) {
            temp = temp->next;
            curPos++;
        }
        if (temp == NULL) {
            cout << "Position out of bounds." << endl;
            return;
        }
        if (temp->prev != NULL) {
            temp->prev->next = temp->next; // Bypass the node to delete
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev; // Update the previous pointer of the next node
        }
        delete temp; // Use delete instead of free
    }

    void concatenate(DoublyLinkedList& other) {
        if (other.head == NULL) return; //

        if (head == NULL) { 
            head = other.head;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = other.head; 
            other.head->prev = temp; // Update the previous pointer of the other list's head
        }
    }
};

int main() {
    DoublyLinkedList list1;
    list1.insertAtHead(7);
    list1.insertAtHead(9);
    list1.insertAtTail(3);
    list1.insertAtPosition(8, 0);
    list1.insertAtPosition(12, 4);
    list1.insertAtPosition(30,3);
    list1.display();

    DoublyLinkedList list2;
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
