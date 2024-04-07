#include <iostream>
#include <vector>
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
    int size;

    Node* insertHelper(Node* node, int value) {
        if (node == NULL) {
            return new Node(value);
        }
        if (value <= node->value) {
            node->left = insertHelper(node->left, value);
        }
        else {
            node->right = insertHelper(node->right, value);
        }
        size++;
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
    class Iterator {
    private:
        Node* node;
        vector<Node> order;
        vector<bool> was;
    public:
        void DFS(Node& node) {
            if (node.left != NULL && !was[node.left->value]) {
                DFS(*node.left);
            }
            if (node.right != NULL && !was[node.right->value]) {
                DFS(*node.right);
            }
            was[node.value] = true;
            order.push_back(node);
        }
        void sort(vector<Node>& order) {
            for (int i = 0; i < order.size(); i++) {
                for (int j = 0; j < order.size(); j++) {
                    if (order[i].value < order[j].value) {
                        swap(order[i], order[j]);
                    }
                }
            }
        }
        Iterator(Node* nod, Node* root, int size) { node = nod; was = vector<bool>(size); DFS(*root); sort(order);  }
        Iterator& operator++() {
            for (int i = 0; i < order.size(); i++) {
                if (order[i].value == node->value) {
                    this->node = &order[i + 1];
                    return *this;
                }
            }
        }
        bool operator ==(const Iterator& other)
        {
            return (node == other.node);
        }
        bool operator !=(const Iterator& other)
        {
            return !(node->value==other.node->value);
        }
        Node& operator*() {
            return *node;
        }
        Node* operator->() {
            return this->node;
        }
    };
    BinaryTree() {
        root = NULL;
        size = 0;
    }
    Iterator find(int value) {
        Node* node = root;
        while (node->value != value) {
            if (value <= node->value && node->left!=NULL) {
                node = node->left;
            }
            else if (value > node->value && node->right!=NULL) {
                node = node->right;
            }
            else {
                throw "Invalid value";
            }
        }
        return Iterator(node, root, size);
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