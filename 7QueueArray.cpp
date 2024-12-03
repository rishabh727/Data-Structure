#include <iostream>
#include <stdexcept>

using namespace std;

class CircularQueue {
private:
    int* arr;
    int front, rear, size, capacity;

public:
    CircularQueue(int capacity) : capacity(capacity), size(0), front(0), rear(capacity - 1) {
        arr = new int[capacity];
    }

    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (isFull()) {
            throw overflow_error("Queue is full");
        }
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        int value = arr[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    int peek() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        return arr[front];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};

int main() {
    try {
        CircularQueue q(5);

        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);
        q.enqueue(40);
        q.enqueue(50);

        cout << "Front element: " << q.peek() << endl;

        cout << "Dequeued: " << q.dequeue() << endl;
        cout << "Dequeued: " << q.dequeue() << endl;

        q.enqueue(60);
        q.enqueue(70);

        while (!q.isEmpty()) {
            cout << "Dequeued: " << q.dequeue() << endl;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
