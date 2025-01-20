#ifndef BST_H
#define BST_H

template <class T>
class Bst {
private:
    struct node {
        T data;
        node* left;
        node* right;
    };
    node* root;

    node* createNode(T data);
    node* insertNode(node* root, T data);
    void inOrderTraversal(node* root);
    void preOrderTraversal(node* root);
    void postOrderTraversal(node* root);
    node* findMin(node* root);
    node* findMax(node* root);
    node* deleteNode(node* root, T data);
    int countNodes(node* root);
    int treeHeight(node* root);
    void deleteTree(node* root);
    void printTree(node* root, int level);

public:
    Bst();
    void insert(T data);
    void display();
    void preOrder();
    void inOrder();
    void postOrder();
    void findSmallest();
    void findLargest();
    void deleteNode(T data);
    void countNodes();
    void treeHeight();
    void deleteTree();
    ~Bst();
};

#endif //BST_H
