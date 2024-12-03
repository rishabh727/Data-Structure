#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    int data, height;
    Node* left, * right;
    Node(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) { return node ? node->height : 0; }
    int balanceFactor(Node* node) { return node ? height(node->left) - height(node->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x = y->left, * T2 = x->right;
        x->right = y; y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right, * T2 = y->left;
        y->left = x; x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        else return node;
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = balanceFactor(node);
        if (balance > 1 && value < node->left->data) return rightRotate(node);
        if (balance < -1 && value > node->right->data) return leftRotate(node);
        if (balance > 1 && value > node->left->data) { node->left = leftRotate(node->left); return rightRotate(node); }
        if (balance < -1 && value < node->right->data) { node->right = rightRotate(node->right); return leftRotate(node); }
        return node;
    }

    Node* deleteNode(Node* node, int value) {
        if (!node) return node;
        if (value < node->data) node->left = deleteNode(node->left, value);
        else if (value > node->data) node->right = deleteNode(node->right, value);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) { temp = node; node = nullptr; }
                else *node = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }
        if (!node) return node;
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = balanceFactor(node);
        if (balance > 1 && balanceFactor(node->left) >= 0) return rightRotate(node);
        if (balance < -1 && balanceFactor(node->right) <= 0) return leftRotate(node);
        if (balance > 1 && balanceFactor(node->left) < 0) { node->left = leftRotate(node->left); return rightRotate(node); }
        if (balance < -1 && balanceFactor(node->right) > 0) { node->right = rightRotate(node->right); return leftRotate(node); }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    void inorder(Node* node) {
        if (node) { inorder(node->left); cout << node->data << " "; inorder(node->right); }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) { root = insert(root, value); }
    void deleteNode(int value) { root = deleteNode(root, value); }
    void inorder() { inorder(root); cout << endl; }
};

int main() {
    AVLTree tree;
    tree.insert(50); tree.insert(30); tree.insert(20);
    tree.insert(40); tree.insert(70); tree.insert(60); tree.insert(80);
    cout << "Inorder: "; tree.inorder();
    tree.deleteNode(20); tree.deleteNode(30);
    cout << "Inorder after deletions: "; tree.inorder();
    return 0;
}
