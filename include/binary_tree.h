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
    int height;

    Node(TypeKey nkey, TypeData val) {
        key = nkey;
        value = val;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 0;

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
        if (key <= node->key) {
            node->left = insertHelper(node->left, key, value);
            node->left->parent = node;
        }
        else {
            node->right = insertHelper(node->right, key, value);
            node->right->parent = node;
        }
        updateHeight(node);
        return node;
    }

    Node<TypeKey, TypeData>* minValueNode(Node<TypeKey, TypeData>* node) {
        Node<TypeKey, TypeData>* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node<TypeKey, TypeData>* deleteHelper(Node<TypeKey, TypeData>* node, TypeKey key) {
        if (node == NULL) {
            return node;
        }
        if (key < node->key) {
            node->left = deleteHelper(node->left, key);
            if (node->left != nullptr) {
                node->left->parent = node;
            }
        }
        else if (key > node->key) {
            node->right = deleteHelper(node->right, key);
            if (node->right != nullptr) {
                node->right->parent = node;
            }
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
            node->right = deleteHelper(node->right, temp->key);
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
    int heightHelper(Node<TypeKey, TypeData>* node) const {
        return node == nullptr ? 0 : node->height;
    }
    void updateHeight(Node<TypeKey, TypeData>* node) {
        node->height = std::max(heightHelper(node->left), heightHelper(node->right)) + 1;
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
    TypeData& operator[](TypeKey fkey) {
        Node<TypeKey, TypeData>* node = root;
        while (node->key != fkey) {
            if (fkey <= node->key && node->left != NULL) {
                node = node->left;
            }
            else if (fkey > node->key && node->right != NULL) {
                node = node->right;
            }
            else {
                throw "Invalid key";
            }
        }
        return node->value;
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

    void remove(TypeKey key) {
        root = deleteHelper(root,key);
        size--;
    }

    void inorder() {
        inorderHelper(root);
    }
    int getsize() {
        return size;
    }
    int getheight() {
        return root->height;
    }
};