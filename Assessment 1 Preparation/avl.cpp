#include<iostream>
#include<algorithm>
using namespace std;
template <class T>
class AVL
{
    struct AvlNode
    {
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;
        AvlNode(const T &e,AvlNode *lt = nullptr,AvlNode *rt = nullptr, int ht = 0)
            : element(e),left(lt),right(rt),height(ht) {}
    };
    AvlNode *root;
    void makeEmpty(AvlNode *&t)
    {
        if(isEmpty(t))
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }
    void insert(const T &x,AvlNode *&t)
    {
        if(isEmpty(t))
            t = new AvlNode(x);
        else if(x<t->element)
            insert(x,t->left);
        else if(x>t->element)
            insert(x,t->right);
        t->height = max(height(t->left),height(t->right)) + 1;
        balance(t);
    }
    void remove(const T &x,AvlNode *&t)
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
            AvlNode *old = t;
            t = (t->left==nullptr)?t->right:t->left;
            delete old;
        }
        if(!isEmpty(t))
        {
            t->height = max(height(t->left),height(t->right))+1;
            balance(t);
        }
    }
    bool search(const T &x, AvlNode *t)
    {
        if(isEmpty(t))
            return false;
        else if(x<t->element)
            return search(x,t->left);
        else if(x>t->element)
            return search(x,t->right);
        else
            return true;
    }
    AvlNode *findMin(AvlNode *t) const
    {
        if(!isEmpty(t))
        {
            while(!isEmpty(t->left))
                t = t->left;
        }
        return t;
    }
    AvlNode *findMax(AvlNode *t) const
    {
        if(!isEmpty(t))
        {
            while(!isEmpty(t->right))
                t = t->right;
        }
        return t;
    }
    void balance(AvlNode *&t)
    {
        if(isEmpty(t))
            return;
        if(height(t->left)-height(t->right)>1)
        {
            if(height(t->left->left) >= height(t->left->right))
                srl(t);
            else
                drl(t);
        }
        else if(height(t->right)-height(t->left)>1)
        {
            if(height(t->right->right) >= height(t->right->left))
                srr(t);
            else
                drr(t);
        }
    }
    bool isEmpty(AvlNode *t) const
    {
        return t==nullptr;
    }
    void srl(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left),height(k2->right)) + 1;
        k1->height = max(height(k1->left),k2->height) + 1;        
        k2=k1;
    }
    void srr(AvlNode *&k2)
    {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k1->height = max(height(k1->left),height(k1->right)) + 1;
        k2->height = max(height(k2->left),k1->height) + 1;        
        k2=k1;
    }
    void drl(AvlNode *&t)
    {
        srr(t);
        srl(t);
    }
    void drr(AvlNode *&t)
    {
        srl(t);
        srr(t);
    }
    void inorder(AvlNode *t) const
    {
        if(t!=nullptr)
        {
            inorder(t->left);
            cout<<t->element<<" ";
            inorder(t->right);
        }

    }
    int height(AvlNode *t)
    {
        return (t==nullptr)?-1:t->height;
    }
    public:
    AVL()
    {
        root = nullptr;
    }
    ~AVL()
    {
        makeEmpty(root);
    }
    void insert(const T &x) {insert(x,root);}
    void remove(const T &x) {remove(x,root);}
    bool search(const T &x) {return search(x,root);}
    T &findMin() {return findMin(root)->element;}
    T &findMax() {return findMax(root)->element;}
    void inorder() {inorder(root);}
};
int main()
{
    AVL<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.inorder();
    tree.remove(10);
    tree.inorder();
    return 0;
}