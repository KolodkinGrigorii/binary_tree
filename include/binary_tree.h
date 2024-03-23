#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
private:
    Node* root;

    Node* insertHelper(Node* node, int value) {
        if (node == NULL) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insertHelper(node->left, value);
        }
        else {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node* deleteHelper(Node* node, int value) {
        if (node == NULL) {
            return node;
        }
        if (value < node->value) {
            node->left = deleteHelper(node->left, value);
        }
        else if (value > node->value) {
            node->right = deleteHelper(node->right, value);
        }
        else {
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = deleteHelper(node->right, temp->value);
        }
        return node;
    }

    void inorderHelper(Node* node) {
        if (node != NULL) {
            inorderHelper(node->left);
            cout << node->value << " ";
            inorderHelper(node->right);
        }
    }

public:
    BinaryTree() {
        root = NULL;
    }

    void insert(int value) {
        root = insertHelper(root, value);
    }

    void remove(int value) {
        root = deleteHelper(root, value);
    }

    void inorder() {
        inorderHelper(root);
    }
};