#include <iostream>
#include <cstdlib>

using namespace std;

// Template for node structure
template <typename T>
struct node {
    T data;
    node* left;
    node* right;

    node(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Template for BST class
template <typename T>
class BST {
public:
    node<T>* root;

    BST() : root(nullptr) {}

    // Function to create a new node
    node<T>* createNode(T data) {
        return new node<T>(data);
    }

    // Function to insert a node into the tree
    node<T>* insertNode(node<T>* root, T data) {
        if (root == nullptr) {
            return createNode(data);
        }
        if (data < root->data) {
            root->left = insertNode(root->left, data);
        } else if (data > root->data) {
            root->right = insertNode(root->right, data);
        }
        return root;
    }

    // Function for in-order traversal
    void inOrderTraversal(node<T>* root) {
        if (root != nullptr) {
            inOrderTraversal(root->left);
            cout << root->data << " ";
            inOrderTraversal(root->right);
        }
    }

    // Function for pre-order traversal
    void preOrderTraversal(node<T>* root) {
        if (root != nullptr) {
            cout << root->data << " ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }

    // Function for post-order traversal
    void postOrderTraversal(node<T>* root) {
        if (root != nullptr) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            cout << root->data << " ";
        }
    }

    // Function to find the smallest element
    node<T>* findMin(node<T>* root) {
        while (root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    // Function to find the largest element
    node<T>* findMax(node<T>* root) {
        while (root && root->right != nullptr) {
            root = root->right;
        }
        return root;
    }

    // Function to delete a node
    node<T>* deleteNode(node<T>* root, T data) {
        if (root == nullptr) {
            return root;
        }
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        } else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        } else {
            if (root->left == nullptr) {
                node<T>* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                node<T>* temp = root->left;
                delete root;
                return temp;
            }
            node<T>* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    // Function to count the total number of nodes
    int countNodes(node<T>* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    // Function to count the total number of external nodes (leaf nodes)
    int countExternalNodes(node<T>* root) {
        if (root == nullptr) {
            return 0;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }
        return countExternalNodes(root->left) + countExternalNodes(root->right);
    }

    // Function to count the total number of internal nodes
    int countInternalNodes(node<T>* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return 0;
        }
        return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
    }

    // Function to determine the height of the tree
    int treeHeight(node<T>* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);
        return 1 + max(leftHeight, rightHeight);
    }

    // Function to find the mirror image of the tree
    node<T>* mirrorTree(node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        node<T>* temp = root->left;
        root->left = root->right;
        root->right = temp;
        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }

    // Function to delete the tree
    void deleteTree(node<T>* root) {
        if (root == nullptr) {
            return;
        }
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    // Function to print the tree vertically
    void printTree(node<T>* root, int level) {
        if (root == nullptr) {
            return;
        }

        printTree(root->right, level + 1);

        for (int i = 0; i < level; i++) {
            cout << "    ";
        }
        cout << root->data << endl;

        printTree(root->left, level + 1);
    }
};

// Main function to interact with the BST class
int main() {
    BST<int> tree;
    int choice, value;

    while (1) {
        cout << "\n ******MAIN MENU******* \n";
        cout << "1. Insert Element\n";
        cout << "2. Display Tree Horizontally\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Postorder Traversal\n";
        cout << "6. Find the smallest element\n";
        cout << "7. Find the largest element\n";
        cout << "8. Delete an element\n";
        cout << "9. Count the total number of nodes\n";
        cout << "10. Count the total number of external nodes\n";
        cout << "11. Count the total number of internal nodes\n";
        cout << "12. Determine the height of the tree\n";
        cout << "13. Find the mirror image of the tree\n";
        cout << "14. Delete the tree\n";
        cout << "15. Exit\n";
        cout << "Enter your option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to be inserted: ";
                cin >> value;
                tree.root = tree.insertNode(tree.root, value);
                cout << "Horizontal display of the tree:\n";
                tree.printTree(tree.root, 0);
                break;
            case 2:
                cout << "Horizontal display of the tree:\n";
                tree.printTree(tree.root, 0);
                break;
            case 3:
                cout << "Preorder traversal: ";
                tree.preOrderTraversal(tree.root);
                cout << "\n";
                break;
            case 4:
                cout << "Inorder traversal: ";
                tree.inOrderTraversal(tree.root);
                cout << "\n";
                break;
            case 5:
                cout << "Postorder traversal: ";
                tree.postOrderTraversal(tree.root);
                cout << "\n";
                break;
            case 6:
                if (tree.root != nullptr) {
                    node<int>* minNode = tree.findMin(tree.root);
                    cout << "The smallest element is: " << minNode->data << endl;
                } else {
                    cout << "The tree is empty.\n";
                }
                break;
            case 7:
                if (tree.root != nullptr) {
                    node<int>* maxNode = tree.findMax(tree.root);
                    cout << "The largest element is: " << maxNode->data << endl;
                } else {
                    cout << "The tree is empty.\n";
                }
                break;
            case 8:
                cout << "Enter the value to be deleted: ";
                cin >> value;
                tree.root = tree.deleteNode(tree.root, value);
                cout << "Horizontal display of the tree:\n";
                tree.printTree(tree.root, 0);
                break;
            case 9:
                cout << "The total number of nodes is: " << tree.countNodes(tree.root) << endl;
                break;
            case 10:
                cout << "The total number of external nodes is: " << tree.countExternalNodes(tree.root) << endl;
                break;
            case 11:
                cout << "The total number of internal nodes is: " << tree.countInternalNodes(tree.root) << endl;
                break;
            case 12:
                cout << "The height of the tree is: " << tree.treeHeight(tree.root) << endl;
                break;
            case 13:
                tree.root = tree.mirrorTree(tree.root);
                cout << "The tree has been mirrored.\n";
                cout << "Horizontal display of the tree:\n";
                tree.printTree(tree.root, 0);
                break;
            case 14:
                tree.deleteTree(tree.root);
                tree.root = nullptr;
                cout << "The tree has been deleted.\n";
                break;
            case 15:
                tree.deleteTree(tree.root);
                exit(0);
            default:
                cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}
