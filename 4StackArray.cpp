#include <iostream>
using namespace std;

class Stack {
private:
    int *stack;
    int top;
    int capacity;

public:
    Stack(int capacity) {
        this->capacity = capacity;
        stack = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] stack;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    void push(int item) {
        if (isFull()) {
            cout << "Stack Overflow: Cannot push, stack is full." << endl;
            return;
        }
        stack[++top] = item;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow: Cannot pop, stack is empty." << endl;
            return -1;
        }
        return stack[top--];
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return -1;
        }
        return stack[top];
    }

    int size() {
        return top + 1;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack stack(5);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);

    stack.display();

    cout << "Top element: " << stack.peek() << endl;

    cout << "Popped element: " << stack.pop() << endl;

    stack.display();

    return 0;
}
