#include<iostream>
#include<algorithm>
using namespace std;
template<class T>
class AVL 
{
    private:
    struct AvlNode
    {
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;
        AvlNode(const T &e,AvlNode *lt, AvlNode *rt, int ht)
            : element(e),left(lt),right(rt),height(ht) {};
    };
    AvlNode *root;
    void makeEmpty(AvlNode *&t)
    {
        if(!isEmpty(t))
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void insert(const T &x, AvlNode *&t)
    {
        if(isEmpty(t))
            t = new AvlNode(x,nullptr,nullptr,0);
        else if(x<t->element)
            insert(x,t->left);
        else if(x>t->element)
            insert(x,t->right);
        else
            {;}
        t->height = max(height(t->left),height(t->right)) + 1;
        balance(t);
    }
    AvlNode* findMin(AvlNode *t) const
    {
        if(isEmpty(t))
            return nullptr;    
        while(!isEmpty(t->left))
            t = t->left;
        return t;
    }
    AvlNode* findMax(AvlNode *t) const
    {
        if(isEmpty(t))
            return nullptr;    
        while(!isEmpty(t->right))
            t = t->right;
        return t;
    }
    void remove(const T &x, AvlNode *&t)
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
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        if(!isEmpty(t))
        {
            t->height = max(height(t->left),height(t->right)) + 1;
            balance(t);
        }
    }
    bool search(const T &x, AvlNode *t) const
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
    void printTree(AvlNode *t,int level=0) const
    {
        if(isEmpty(t))
            return;
        printTree(t->right,level+1);
        for(int i=0;i<level;i++)
            cout<<"      ";
        int bfactor = height(t->left) - height(t->right);
        cout<<t->element<<"("<< bfactor <<")"<<endl;
        printTree(t->left,level+1);
    }
    int height(AvlNode *t) const
    {
        return (t==nullptr)?-1:t->height;
    }
    void balance(AvlNode *&t)
    {
        if(isEmpty(t))
            return;
        if(height(t->left) - height(t->right) > 1)
        {
            if(height(t->left->left) >= height(t->left->right))
                srl(t);
            else
                drl(t);
        }   
        else if(height(t->right) - height(t->left) > 1)
        {
            if(height(t->right->right) >= height(t->right->left))
                srr(t);
            else
                drr(t);
        }    
        t->height = max(height(t->left),height(t->right)) + 1;
    }
    void srl(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left),height(k2->right)) + 1;
        k1->height = max(height(k1->left),k2->height) + 1;
        k2 = k1;
    }
    void srr(AvlNode *&k2)
    {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left),height(k2->right)) + 1;
        k1->height = max(height(k1->right),k2->height) + 1;
        k2 = k1;
    }
    void drl(AvlNode *&k3)
    {
        srr(k3->left);
        srl(k3);
    }
    void drr(AvlNode *&k3)
    {
        srl(k3->right);
        srr(k3);
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
        bool isEmpty(AvlNode *t) const
        {
            return t==nullptr;
        }
        void insert(const T &x)
        {
            insert(x,root);
        }
        void remove(const T &x)
        {
            remove(x,root);
        }
        const T &findMin() const
        {
            return findMin(root)->element;
        }
        const T &findMax() const
        {
            return findMax(root)->element;
        }
        bool search(const T &x) const
        {
            return search(x,root);
        }
        void printTree()
        {
            printTree(root,0);
        }
};
int main()
{
    AVL<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.printTree();
    cout<<endl;
    tree.remove(3);
    tree.remove(6);
    tree.remove(9);
    tree.printTree();
    cout<<endl;
    bool x = tree.search(10);
    cout<<"Value 10 : "<<x;
    cout<<endl;
    cout<<"Min : "<<tree.findMin();
    cout<<endl;
    cout<<"Max : "<<tree.findMax();
}