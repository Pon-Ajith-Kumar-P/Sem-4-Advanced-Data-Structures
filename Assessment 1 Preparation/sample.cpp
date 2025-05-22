#include <iostream>
 
using namespace std;
 
// Node structure for the Splay Tree
struct Node {
    int key;
    Node* left;
    Node* right;
 
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};
 
// Right rotation (Zig)
Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}
 
// Left rotation (Zag)
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
 
// Splay function: Moves the given key to the root
Node* splay(Node* root, int key) {
    if (!root || root->key == key) return root;
 
    // Left subtree case
    if (key < root->key) {
        if (!root->left) return root;
 
        if (key < root->left->key) { // Zig-Zig (Left Left)
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        } else if (key > root->left->key) { // Zig-Zag (Left Right)
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = rotateLeft(root->left);
        }
 
        return root->left ? rotateRight(root) : root;
    }
 
    // Right subtree case
    if (key > root->key) {
        if (!root->right) return root;
 
        if (key > root->right->key) { // Zag-Zag (Right Right)
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        } else if (key < root->right->key) { // Zag-Zig (Right Left)
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rotateRight(root->right);
        }
 
        return root->right ? rotateLeft(root) : root;
    }
 
    return root;
}
 
// Insert a key into the Splay Tree
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
 
    root = splay(root, key);
 
    if (root->key == key) return root; // Key already exists
 
    Node* newNode = new Node(key);
    if (key < root->key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    
    return newNode;
}
 
// Delete a key from the Splay Tree
Node* deleteKey(Node* root, int key) {
    if (!root) return nullptr;
 
    root = splay(root, key);
 
    if (root->key != key) return root; // Key not found
 
    Node* temp;
    if (!root->left) {
        temp = root->right;
    } else {
        temp = splay(root->left, key);
        temp->right = root->right;
    }
 
    delete root;
    return temp;
}
 
// Search for a key in the Splay Tree
bool search(Node*& root, int key) {
    root = splay(root, key);
    return (root && root->key == key);
}
 
// In-order traversal (for debugging)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
 
// Main function to interact with the user
int main() {
    Node* root = nullptr;
    int choice, key;
 
    while (true) {
        cout << "\n1. Insert\n2. Delete\n3. Search\n4. Display (In-order)\n5. Exit\nEnter choice: ";
        cin >> choice;
 
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                root = insert(root, key);
                inorder(root);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                root = deleteKey(root, key);
                inorder(root);
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                if (search(root, key))
                    cout << key << " found in the tree.\n";
                else
                    cout << key << " not found in the tree.\n";
                break;
            case 4:
                cout << "Tree (In-order): ";
                inorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
 
    return 0;
}