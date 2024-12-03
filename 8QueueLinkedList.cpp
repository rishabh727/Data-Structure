#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class CircularQueue {
private:
    Node* rear;
    int size;

public:
    CircularQueue() : rear(nullptr), size(0) {}

    ~CircularQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            rear = newNode;
            rear->next = rear;
        } else {
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }

        Node* front = rear->next;
        int value = front->data;

        if (rear == front) {
            rear = nullptr;
        } else {
            rear->next = front->next;
        }

        delete front;
        size--;
        return value;
    }

    int peek() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        return rear->next->data;
    }

    bool isEmpty() {
        return rear == nullptr;
    }

    int getSize() {
        return size;
    }
};

int main() {
    CircularQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Front element: " << q.peek() << endl;

    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;

    q.enqueue(40);
    q.enqueue(50);

    while (!q.isEmpty()) {
        cout << "Dequeued: " << q.dequeue() << endl;
    }

    return 0;
}
