#include <iostream>
#include <vector>
using namespace std;
template<typename TypeKey, typename TypeData>
struct Node {
    TypeKey key;
    TypeData value;
    Node* left;
    Node* right;

    Node(TypeKey nkey, TypeData val) {
        key = nkey;
        value = val;
        left = NULL;
        right = NULL;
    }
};
template<typename TypeKey, typename TypeData>
class BinaryTree {
private:
    Node<TypeKey, TypeData>* root;
    int size;

    Node<TypeKey, TypeData>* insertHelper(Node<TypeKey, TypeData>* node, TypeKey key, TypeData value) {
        if (node == NULL) {
            return new Node<TypeKey, TypeData>(key, value);
        }
        if (value <= node->value) {
            node->left = insertHelper(node->left, key, value);
        }
        else {
            node->right = insertHelper(node->right, key, value);
        }
        size++;
        return node;
    }

    Node<TypeKey, TypeData>* minValueNode(Node<TypeKey, TypeData>* node) {
        Node<TypeKey, TypeData>* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node<TypeKey, TypeData>* deleteHelper(Node<TypeKey, TypeData>* node, TypeKey key, TypeData value) {
        if (node == NULL) {
            return node;
        }
        if (value < node->value) {
            node->left = deleteHelper(node->left, key, value);
        }
        else if (value > node->value) {
            node->right = deleteHelper(node->right, key, value);
        }
        else {
            if (node->left == NULL) {
                Node<TypeKey, TypeData>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node<TypeKey, TypeData>* temp = node->left;
                delete node;
                return temp;
            }
            Node<TypeKey, TypeData>* temp = minValueNode(node->right);
            node->value = temp->key;
            node->right = deleteHelper(node->right, temp->key, temp->value);
        }
        return node;
    }

    void inorderHelper(Node<TypeKey, TypeData>* node) {
        if (node != NULL) {
            inorderHelper(node->left);
            cout << node->value << " ";
            inorderHelper(node->right);
        }
    }

public:
    class Iterator {
    private:
        Node<TypeKey, TypeData>* node;
        vector<Node<TypeKey, TypeData>> order;
        vector<bool> was;
    public:
        void DFS(Node<TypeKey, TypeData>& node) {
            if (node.left != NULL && !was[node.left->value]) {
                DFS(*node.left);
            }
            if (node.right != NULL && !was[node.right->value]) {
                DFS(*node.right);
            }
            was[node.value] = true;
            order.push_back(node);
        }
        void sort(vector<Node<TypeKey, TypeData>>& order) {
            for (int i = 0; i < order.size(); i++) {
                for (int j = 0; j < order.size(); j++) {
                    if (order[i].value < order[j].value) {
                        swap(order[i], order[j]);
                    }
                }
            }
        }
        Iterator(Node<TypeKey, TypeData>* nod, Node<TypeKey, TypeData>* root, int size) { node = nod; was = vector<bool>(size); DFS(*root); sort(order); }
        Iterator& operator++() {
            for (int i = 0; i < order.size(); i++) {
                if (order[i].key == node->key) {
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
            return !(node->key == other.node->key);
        }
        TypeData& operator*() {
            return node->value;
        }
        Node<TypeKey, TypeData>* operator->() {
            return this->node;
        }
    };
    BinaryTree() {
        root = NULL;
        size = 0;
    }
    Iterator find(TypeKey fkey) {
        Node<TypeKey, TypeData>* node = root;
        while (node->key != fkey) {
            if (fkey <= node->key && node->left!=NULL) {
                node = node->left;
            }
            else if (fkey > node->key && node->right!=NULL) {
                node = node->right;
            }
            else {
                throw "Invalid value";
            }
        }
        return Iterator(node, root, size);
    }
    Iterator begin() {
        Node<TypeKey, TypeData>* node = root;
        while (node->left != NULL) {
            node = node->left;
        }
        return Iterator(node, root, size);
    }

    Iterator end() {
        Node<TypeKey, TypeData>* node = root;
        while (node->right != NULL) {
            node = node->right;
        }
        return Iterator(node, root, size);
    }
    void insert(TypeKey key, TypeData value) {
        root = insertHelper(root, key, value);
    }

    void remove(TypeKey key, TypeData value) {
        root = deleteHelper(root,key, value);
    }

    void inorder() {
        inorderHelper(root);
    }
};