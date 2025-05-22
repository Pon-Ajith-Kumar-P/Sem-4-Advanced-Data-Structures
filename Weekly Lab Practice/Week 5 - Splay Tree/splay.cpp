#include <iostream>
#include <string>
using namespace std;
template <typename T>
class SplayTree 
{
    private:
    struct BinaryNode 
    {
        T element;
        BinaryNode *left, *right;
        BinaryNode(const T &ele = T(), BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
            : element(ele), left(lt), right(rt) {}
    };
    BinaryNode *root;
    BinaryNode *nullNode;

    void insertNode(const T &x) 
    {
        static BinaryNode *newNode = nullptr;
        if (newNode == nullptr)
            newNode = new BinaryNode;
        newNode->element = x;
        if (root == nullNode) 
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        } 
        else 
        {
            splay(x, root);
            if (x < root->element) 
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            } 
            else if (root->element < x) 
            {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullNode;
                root = newNode;
            } 
            else 
            {
                return;
            }
        }
        newNode = nullptr;
    }

    void removeNode(const T &x) 
    {
        if (!containsNode(x)) 
            return;
        BinaryNode *newTree;
        if (root->left == nullNode)
            newTree = root->right;
        else 
        {
            newTree = root->left;
            splay(x, newTree);
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
    }

    bool containsNode(const T &x) 
    {
        if (root == nullNode)
            return false;
        splay(x, root);
        return root->element == x;
    }

    T findMinNode() const 
    {
        if (root == nullNode) return T();
        BinaryNode *node = root;
        while (node->left != nullNode)
            node = node->left;
        return node->element;
    }

    T findMaxNode() const 
    {
        if (root == nullNode) return T();
        BinaryNode *node = root;
        while (node->right != nullNode)
            node = node->right;
        return node->element;
    }

    void printTreeStructure(BinaryNode *node, int space) const 
    {
        if (node == nullNode)
            return;
        space += 5;
        printTreeStructure(node->right, space);
        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << node->element << endl;
        printTreeStructure(node->left, space);
    }

    void inorderTraversal(BinaryNode *t) const 
    {
        if (t != nullNode) 
        {
            inorderTraversal(t->left);
            cout << t->element << " ";
            inorderTraversal(t->right);
        }
    }

    void splay(const T &x, BinaryNode *&t) 
    {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;
        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;
        nullNode->element = x;
        
        while (true) 
        {
            if (x < t->element) 
            {
                if (x < t->left->element)
                    rotateWithLeftChild(t);
                if (t->left == nullNode)
                    break;
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            } 
            else if (t->element < x) 
            {
                if (t->right->element < x)
                    rotateWithRightChild(t);
                if (t->right == nullNode)
                    break;
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            } 
            else 
            {
                break;
            }
        }
        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }

    void rotateWithLeftChild(BinaryNode *&k2) 
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild(BinaryNode *&k2) 
    {
        BinaryNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2 = k1;
    }

    void makeEmpty() 
    {
        while (root != nullNode)
            removeNode(root->element);
    }

    public:
    SplayTree() 
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }

    ~SplayTree() 
    {
        makeEmpty();
        delete nullNode;
    }

    void insert(const T &x) 
    { 
        insertNode(x); 
    }
    void remove(const T &x) 
    { 
        removeNode(x); 
    }
    bool search(const T &x) 
    { 
        return containsNode(x); 
    }
    T findMin() const 
    { 
        return findMinNode(); 
    }
    T findMax() const 
    { 
        return findMaxNode(); 
    }
    void traversal() const 
    { 
        inorderTraversal(root); 
        cout << endl; 
    }
    void printTreeStructure() const 
    {
        if (root == nullNode) 
            cout << "Empty tree" << endl;
        else 
            printTreeStructure(root, 0);
    }

};

int main() 
{
    SplayTree<int> tree;
    int choice, value;
    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Insert\n2. Remove\n3. Search\n4. Minimum Element\n5. Maximum Element\n6. Traversal\n7. Tree Structure\n0. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                tree.printTreeStructure();
                break;
            case 2:
                cout << "Enter value to remove: ";
                cin >> value;
                tree.remove(value);
                tree.printTreeStructure();
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                cout << (tree.search(value) ? "Found" : "Not found") << endl;
                tree.printTreeStructure();
                break;
            case 4:
                cout << "Minimum element: " << tree.findMin() << endl;
                break;
            case 5:
                cout << "Maximum element: " << tree.findMax() << endl;
                break;
            case 6:
                tree.traversal();
                break;
            case 7:
                tree.printTreeStructure();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}