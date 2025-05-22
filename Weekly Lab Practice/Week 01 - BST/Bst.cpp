#include <iostream>
#include <cstdlib>
#include "Bst.h"

template <class T>
Bst<T>::Bst() {
    root = nullptr;
}

template <class T>
Bst<T>::node* Bst<T>::createNode(T data) {
    node* newNode = new node();
    if (!newNode) {
        std::cerr << "Memory allocation failed\n";
        exit(1);
    }
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

template <class T>
Bst<T>::node* Bst<T>::insertNode(node* root, T data) {
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

template <class T>
void Bst<T>::inOrderTraversal(node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

template <class T>
void Bst<T>::preOrderTraversal(node* root) {
    if (root != nullptr) {
        std::cout << root->data << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

template <class T>
void Bst<T>::postOrderTraversal(node* root) {
    if (root != nullptr) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        std::cout << root->data << " ";
    }
}

template <class T>
Bst<T>::node* Bst<T>::findMin(node* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

template <class T>
Bst<T>::node* Bst<T>::findMax(node* root) {
    while (root && root->right != nullptr) {
        root = root->right;
    }
    return root;
}

template <class T>
Bst<T>::node* Bst<T>::deleteNode(node* root, T data) {
    if (root == nullptr) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

template <class T>
int Bst<T>::countNodes(node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

template <class T>
int Bst<T>::treeHeight(node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <class T>
void Bst<T>::deleteTree(node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

template <class T>
void Bst<T>::printTree(node* root, int level) {
    if (root == nullptr) {
        return;
    }
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << root->data << std::endl;
    printTree(root->left, level + 1);
}

template <class T>
void Bst<T>::insert(T data) {
    root = insertNode(root, data);
}

template <class T>
void Bst<T>::display() {
    printTree(root, 0);
}

template <class T>
void Bst<T>::preOrder() {
    preOrderTraversal(root);
    std::cout << std::endl;
}

template <class T>
void Bst<T>::inOrder() {
    inOrderTraversal(root);
    std::cout << std::endl;
}

template <class T>
void Bst<T>::postOrder() {
    postOrderTraversal(root);
    std::cout << std::endl;
}

template <class T>
void Bst<T>::findSmallest() {
    if (root != nullptr) {
        node* minNode = findMin(root);
        std::cout << "The smallest element is: " << minNode->data << std::endl;
    } else {
        std::cout << "The tree is empty." << std::endl;
    }
}

template <class T>
void Bst<T>::findLargest() {
    if (root != nullptr) {
        node* maxNode = findMax(root);
        std::cout << "The largest element is: " << maxNode->data << std::endl;
    } else {
        std::cout << "The tree is empty." << std::endl;
    }
}

template <class T>
void Bst<T>::deleteNode(T data) {
    root = deleteNode(root, data);
}

template <class T>
void Bst<T>::countNodes() {
    std::cout << "The total number of nodes is: " << countNodes(root) << std::endl;
}

template <class T>
void Bst<T>::treeHeight() {
    std::cout << "The height of the tree is: " << treeHeight(root) << std::endl;
}

template <class T>
void Bst<T>::deleteTree() {
    deleteTree(root);
    root = nullptr;
}

template <class T>
Bst<T>::~Bst() {
    deleteTree();
}
