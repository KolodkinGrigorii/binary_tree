#include <iostream>
#include <vector>
using namespace std;
template<typename TypeKey, typename TypeData>
struct Node {
    TypeKey key;
    TypeData value;
    Node* left;
    Node* right;
    Node* parent;

    Node(TypeKey nkey, TypeData val) {
        key = nkey;
        value = val;
        left = NULL;
        right = NULL;
        parent = NULL;
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
            node->left->parent = node;
        }
        else {
            node->right = insertHelper(node->right, key, value);
            node->right->parent = node;
        }
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
        Node<TypeKey, TypeData>* current;

        Node<TypeKey, TypeData>* successorHelper(Node<TypeKey, TypeData>* node) const {
            if (node->right != nullptr) {
                return minHelper(node->right);
            }

            Node<TypeKey, TypeData>* parent = node->parent;
            while (parent != nullptr && node == parent->right) {
                node = parent;
                parent = parent->parent;
            }

            return parent;
        }
    public:
        Iterator(Node<TypeKey, TypeData>* node) : current{ node } {}

        TypeData& operator*() { return current->value; }
        Node<TypeKey, TypeData>* operator->() { return current; }

        Iterator& operator++(){
            current = successorHelper(current);
            return *this;
        }
        Node<TypeKey, TypeData>* minHelper(Node<TypeKey, TypeData>* node) const {
            if (node->left == nullptr) {
                return node;
            }
            else {
                return minHelper(node->left);
            }
        }
        bool operator==(const Iterator& other) const  {
            return current== other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
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
        return Iterator(node);
    }
    Iterator begin() {
        Node<TypeKey, TypeData>* node = root;
        while (node->left != NULL) {
            node = node->left;
        }
        return Iterator(node);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
    void insert(TypeKey key, TypeData value) {
        root = insertHelper(root, key, value);
        size++;
    }

    void remove(TypeKey key, TypeData value) {
        root = deleteHelper(root,key, value);
        size--;
    }

    void inorder() {
        inorderHelper(root);
    }
};