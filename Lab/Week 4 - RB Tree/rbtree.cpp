#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

enum Color { RED, BLACK };

template <typename T>
class RBTree {
private:
    struct Node {
        T data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;

        Node(T value) : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void rotateLeft(Node*& t) {
        Node* child = t->right;
        t->right = child->left;
        if (child->left) child->left->parent = t;
        child->parent = t->parent;
        if (!t->parent) root = child;
        else if (t == t->parent->left) t->parent->left = child;
        else t->parent->right = child;
        child->left = t;
        t->parent = child;
    }

    void rotateRight(Node*& t) {
        Node* child = t->left;
        t->left = child->right;
        if (child->right) child->right->parent = t;
        child->parent = t->parent;
        if (!t->parent) root = child;
        else if (t == t->parent->right) t->parent->right = child;
        else t->parent->left = child;
        child->right = t;
        t->parent = child;
    }

    void fixInsert(Node*& t) {
        while (t != root && t->parent->color == RED) {
            Node* parent = t->parent;
            Node* grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    t = grandparent;
                } else {
                    if (t == parent->right) {
                        t = parent;
                        rotateLeft(t);
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(grandparent);
                }
            } else {
                Node* uncle = grandparent->left;
                if (uncle && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    t = grandparent;
                } else {
                    if (t == parent->left) {
                        t = parent;
                        rotateRight(t);
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorderHelper(Node* t) {
        if (t) {
            inorderHelper(t->left);
            cout << t->data << " ";
            inorderHelper(t->right);
        }
    }

    int countNodesHelper(Node* t) {
        if (!t) return 0;
        return 1 + countNodesHelper(t->left) + countNodesHelper(t->right);
    }

    Node* findMinHelper(Node* t) {
        while (t->left) t = t->left;
        return t;
    }

    Node* findMaxHelper(Node* t) {
        while (t->right) t = t->right;
        return t;
    }

    bool searchHelper(Node* t, T key) {
        if (!t) return false;
        if (key == t->data) return true;
        if (key < t->data) return searchHelper(t->left, key);
        return searchHelper(t->right, key);
    }

    void printTreeHelper(Node* t, int space) {
        if (!t) return;
        space += 10;
        printTreeHelper(t->right, space);
        cout << endl;
        for (int i = 10; i < space; i++) cout << " ";
        cout << t->data << (t->color == RED ? "(R)" : "(B)") << endl;
        printTreeHelper(t->left, space);
    }

public:
    RBTree() : root(nullptr) {}

    void insert(T value) {
        Node* newNode = new Node(value);
        if (!root) {
            root = newNode;
            root->color = BLACK;
            return;
        }
        Node* parent = nullptr;
        Node* curr = root;
        while (curr) {
            parent = curr;
            if (value < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        newNode->parent = parent;
        if (value < parent->data) parent->left = newNode;
        else parent->right = newNode;
        fixInsert(newNode);
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    int countNodes() {
        return countNodesHelper(root);
    }

    T findMin() {
        if (!root) throw runtime_error("Tree is empty");
        return findMinHelper(root)->data;
    }

    T findMax() {
        if (!root) throw runtime_error("Tree is empty");
        return findMaxHelper(root)->data;
    }

    bool search(T key) {
        return searchHelper(root, key);
    }

    void printTree() {
        printTreeHelper(root, 0);
    }
};

int main() {
    RBTree<int> tree;
    int choice, value;

    do {
        cout << "\nRed-Black Tree Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Find Min\n";
        cout << "4. Find Max\n";
        cout << "5. Count Nodes\n";
        cout << "6. Inorder Traversal\n";
        cout << "7. Print Tree\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                cout << (tree.search(value) ? "Found\n" : "Not Found\n");
                break;
            case 3:
                try { cout << "Minimum value: " << tree.findMin() << endl; }
                catch (runtime_error& e) { cout << e.what() << endl; }
                break;
            case 4:
                try { cout << "Maximum value: " << tree.findMax() << endl; }
                catch (runtime_error& e) { cout << e.what() << endl; }
                break;
            case 5:
                cout << "Total nodes: " << tree.countNodes() << endl;
                break;
            case 6:
                cout << "Inorder Traversal: ";
                tree.inorder();
                break;
            case 7:
                tree.printTree();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}