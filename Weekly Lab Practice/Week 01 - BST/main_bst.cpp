#include<iostream>
using namespace std;

template<class T>
class BST
{
    private:
        struct Bnode
        {
            T element;
            Bnode *left;
            Bnode *right;
            Bnode(const T &e, Bnode *lt, Bnode *rt)
                : element(e), left(lt), right(rt) {}
        };
        Bnode *root;
        void insert(const T &x, Bnode *&t) const;
        void remove(const T &x, Bnode *&t) const;
        Bnode *findMin(Bnode *t) const;
        Bnode *findMax(Bnode *t) const;
        bool contains(const T &x, Bnode *t) const;
        void makeEmpty(Bnode *&t);
        void printTree(Bnode *t) const;
    public:
        BST();
        ~BST();
        const T &findMin() const;
        const T &findMax() const;
        bool contains(const T &x) const;
        bool isEmpty() const;
        void printTree() const;
        void insert(const T &x);
        void remove(const T &x);
};

template<class T>
BST<T>::BST()
{
    root = nullptr;
}

template<class T>
BST<T>::~BST()
{
    makeEmpty(root);
}

template<class T>
void BST<T>::insert(const T &x, typename BST<T>::Bnode *&t) const
{
    if(t==nullptr)
        t = new typename BST<T>::Bnode(x,nullptr,nullptr);
    else if(x<t->element)
        insert(x,t->left);
    else if(x>t->element)
        insert(x,t->right);
    else
        {;}
}
template<class T>
void BST<T>::insert(const T &x)
{
    insert(x,root);
}

template<class T>
void BST<T>::remove(const T &x, Bnode *&t) const
{
    if(t==nullptr)
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
        Bnode *oldNode = t;
        t = (t->left!=nullptr)?t->left:t->right;
        delete oldNode;
    }
}
template<class T>
void BST<T>::remove(const T &x)
{ 
    remove(x,root);
}

template<class T>
typename BST<T>::Bnode *BST<T>::findMin(BST<T>::Bnode *t) const
{
    if (t == nullptr)  // Check for empty subtree
        return nullptr;
    while (t->left != nullptr)  // Traverse left to find minimum
        t = t->left;
    return t;
}
template<class T>
const T &BST<T>::findMin() const
{
    if (root == nullptr)  // Check if the tree is empty
        throw runtime_error("Tree is empty!");  // Optionally handle empty tree error
    return findMin(root)->element;  // Call the helper function
}

template<class T>
typename BST<T>::Bnode * BST<T>::findMax(BST<T>::Bnode *t) const
{
    if(t==nullptr)
        t = nullptr;
    else if(t->right==nullptr)
        return t;
    else
        return findMax(t->right);
}
template<class T>
const T &BST<T>::findMax() const
{
    return findMax(root)->element;
}

template<class T>
bool BST<T>::contains(const T &x, typename BST<T>::Bnode *t) const
{
    if(t==nullptr)
        return false;
    else if(x<t->element)
        contains(x,t->left);
    else if(x>t->element)
        contains(x,t->right);
    else
        return true;
}
template<class T>
bool BST<T>::contains(const T &x) const
{
    return contains(x,root);
}

template<class T>
void BST<T>::makeEmpty(Bnode *&t)
{
    if(t!=nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t=nullptr;
}

template<class T>
bool BST<T>::isEmpty() const
{
    return root==nullptr;
}

template<class T>
void BST<T>::printTree(Bnode *t) const
{
    if(t!=nullptr)
    {
        printTree(t->left);
        cout<<t->element<<" ";
        printTree(t->right);
    }
}
template<class T>
void BST<T>::printTree() const
{
    cout<<"Inorder Traversal: ";
    printTree(root);
}

int main()
{
    BST<int> t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);
    t.insert(12);
    t.insert(17);
    t.printTree();
    cout<<endl;
    cout<<"Min: "<<t.findMin()<<endl;
    cout<<"Max: "<<t.findMax()<<endl;
    cout<<"Contains 5: "<<t.contains(5)<<endl;
    cout<<"Contains 6: "<<t.contains(6)<<endl;
    t.remove(5);
    t.printTree();
    cout<<endl;
    return 0;
}