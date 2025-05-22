#include<iostream>
#include<algorithm>
using namespace std;
template <class T>
class AVL
{
    private:
        struct AvlNode
        {
            T element;
            AvlNode *left;
            AvlNode *right;
            int height;
            AvlNode(const T &e,AvlNode *lt,AvlNode *rt, int h=0)
                : element(e),left(lt),right(rt),height(h) {}
        };
        AvlNode *root;
        void insert(const T &x,AvlNode *&t);
        void remove(const T &x,AvlNode *&t);
        void makeEmpty(AvlNode *&t);
        AvlNode* findMin(AvlNode *t) const;
        AvlNode* findMax(AvlNode *t) const;
        bool contains(const T &x,AvlNode *t) const;
        void printTree(AvlNode *t) const;

        int height(AvlNode *t) const;
        void srl(AvlNode *&k2);
        void srr(AvlNode *&k2);
        void drl(AvlNode *&k3);
        void drr(AvlNode *&k3);
        void balance(AvlNode *&t);

    public:
        AVL();
        ~AVL();
        void insert(const T &x);
        void remove(const T &x);
        bool isEmpty(AvlNode *t) const;
        const T &findMin() const;
        const T &findMax() const;
        bool contains(const T &x) const;
        void printTree() const;
};
template<class T>
AVL<T>::AVL()
{
    root = nullptr;
}

template<class T>
AVL<T>::~AVL()
{
    makeEmpty(root);
}

template<class T>
void AVL<T>::makeEmpty(AVL<T>::AvlNode *&t)
{
    if(t!=nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

template<class T>
bool AVL<T>::isEmpty(AVL<T>::AvlNode *t) const
{
    return t==nullptr;
}

template<class T>
void AVL<T>::insert(const T &x,AVL<T>::AvlNode *&t) 
{
    if(isEmpty(t))
        t = new AvlNode(x,nullptr,nullptr);
    else if(x<t->element)
        insert(x,t->left);
    else if(x>t->element)
        insert(x,t->right);
    else
        {;}
    balance(t);
}
template<class T>
void AVL<T>::insert(const T &x)
{
    insert(x,root);
}

template<class T>
void AVL<T>::remove(const T &x,AVL<T>::AvlNode *&t) 
{
    if(isEmpty(t))
        return;
    else if(x<t->element)
        remove(x,t->left);
    else if(x>t->element)
        remove(x,t->right);
    else if(t->left!=nullptr && t->right!=nullptr)
    {
        t->element = findMin(t->right)->element;
        remove(t->element,t->right);
    }
    else
    {
        AvlNode *oldnode = t;
        t = (t->left!=nullptr)?t->left:t->right;
        delete oldnode;
    }
    balance(t);
}
template<class T>
void AVL<T>::remove(const T &x)
{
    remove(x,root);
}

template<class T>
typename AVL<T>::AvlNode* AVL<T>::findMin(AvlNode *t) const
{
    if(!isEmpty(t))
    {
        while(t->left != nullptr)
        {
            t = t->left;
        }
    }
    return t;
}
template<class T>
const T &AVL<T>::findMin() const
{
    if(isEmpty(root))
    {
        cout<<"\nEmpty Tree";
        return -1;
    }
    return findMin(root)->element;
}

template<class T>
typename AVL<T>::AvlNode* AVL<T>::findMax(AVL<T>::AvlNode *t) const
{
    if(!isEmpty(t))
    {
        while(t->right!=nullptr)
            t = t->right;
    }
    return t;
}
template<class T>
const T &AVL<T>::findMax() const
{
    return findMax(root)->element;
}

template<class T>
bool AVL<T>::contains(const T &x,AVL<T>::AvlNode *t) const
{
    if(isEmpty(t))
        return false;
    else if(x<t->element)
        return contains(x,t->left);
    else if(x>t->element)
        return contains(x,t->right);
    else
        return true;
}
template<class T>
bool AVL<T>::contains(const T &x) const
{
    return contains(x,root);
}

template<class T>
void AVL<T>::printTree(AVL<T>::AvlNode *t) const
{
    if(!isEmpty(t))
    {
        printTree(t->left);
        cout<<t->element<<' ';
        printTree(t->right);
    }
}
template<class T>
void AVL<T>::printTree() const
{
    cout<<"\nInorder Traversal : ";
    printTree(root);
}

template<class T>
int AVL<T>::height(AVL<T>::AvlNode *t) const
{
    return (t==nullptr? -1 : t->height);
}

template<class T>
void AVL<T>::balance(AVL<T>::AvlNode *&t)
{
    if(isEmpty(t))
        return;
    if(height(t->left)-height(t->right)>1)
    {
        if(height(t->left->left)>=height(t->left->right))
        {
            srl(t);
        }
        else
        {
            drl(t);
        }
    }
    else if(height(t->right)-height(t->left)>1)
    {
        if(height(t->right->right)>=height(t->right->left))
        {
            srr(t);
        }
        else
        {
            drr(t);
        }
    }

    t->height = max(height(t->left),height(t->right))+1;
}

template<class T>
void AVL<T>::srl(AVL<T>::AvlNode *&k2)
{
    AVL<T>::AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left),height(k2->right))+1;
    k1->height = max(height(k1->left),k2->height);
    k2 = k1;
}
template<class T>
void AVL<T>::srr(AVL<T>::AvlNode *&k2)
{
    AVL<T>::AvlNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left),height(k2->right))+1;
    k1->height = max(height(k1->right),k2->height);
    k2 = k1;
}
template<class T>
void AVL<T>::drl(AVL<T>::AvlNode *&k3)
{
    srr(k3->left);
    srl(k3);
}
template<class T>
void AVL<T>::drr(AVL<T>::AvlNode *&k3)
{
    srl(k3->right);
    srr(k3);
}

int main()
{
    AVL<int> tree;
    int choice, value;

    do
    {
        cout << "\nAVL Tree Operations Menu:";
        cout << "\n1. Insert";
        cout << "\n2. Remove";
        cout << "\n3. Find Minimum";
        cout << "\n4. Find Maximum";
        cout << "\n5. Search";
        cout << "\n6. Print Tree";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to remove: ";
            cin >> value;
            tree.remove(value);
            break;
        case 3:
            cout << "Minimum value: " << tree.findMin() << endl;
            break;
        case 4:
            cout << "Maximum value: " << tree.findMax() << endl;
            break;
        case 5:
            cout << "Enter value to search: ";
            cin >> value;
            if (tree.contains(value))
                cout << "Value found in the tree." << endl;
            else
                cout << "Value not found." << endl;
            break;
        case 6:
            tree.printTree();
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
            default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}   