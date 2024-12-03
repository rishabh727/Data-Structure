#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        } else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* search(Node* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void levelOrder(Node* node) {
        if (node == nullptr) return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            cout << current->data << " ";
            q.pop();

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    
    }

public:
    BST() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    void searchAndUpdate(int value, int newValue) {
        Node* node = search(root, value);
        if (node) {
            node->data = newValue;
            root = deleteNode(root, newValue);
            insert(newValue);
        }
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    void levelOrder() {
        levelOrder(root);
        cout << endl;
    }

    int height() {
        return height(root);
    }
};

int main() {
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Preorder Traversal: ";
    tree.preorder();

    cout << "Inorder Traversal: ";
    tree.inorder();

    cout << "Postorder Traversal: ";
    tree.postorder();

    cout << "Level Order Traversal: ";
    tree.levelOrder();

    cout << "Height of the BST: " << tree.height() << endl;

    cout << "\nDeleting node 20:\n";
    tree.deleteNode(20);

    cout << "Inorder Traversal after deletion: ";
    tree.inorder();

    cout << "\nSearching for 30 and updating it to 35:\n";
    tree.searchAndUpdate(30, 35);

    cout << "Inorder Traversal after update: ";
    tree.inorder();

    return 0;
}
