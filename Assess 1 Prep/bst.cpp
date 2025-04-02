#include<iostream>
using namespace std;
template <class T>
class BST
{
    private:
        struct bstnode
        {
            T element;
            bstnode *left;
            bstnode *right;

            bstnode(const T &e, bstnode *lt=nullptr, bstnode *rt=nullptr)
                : element(e),left(lt),right(rt) {}
        };
        bstnode *root;
        void insert(const T &x,bstnode *&t)
        {
            if(t==nullptr)
                t = new bstnode(x);
            else if(x<t->element)
                insert(x,t->left);
            else if(x>t->element)
                insert(x,t->right);
        }
        void remove(const T &x,bstnode *&t)
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
                bstnode *old = t;
                t = (t->left==nullptr)? t->right : t->left;
                delete old;
            }
        }
        bool search(const T &x, bstnode *t) const
        {
            if(t==nullptr)
                return false;
            else if(x<t->element)
                return search(x,t->left);
            else if(x>t->element)
                return search(x,t->right);
            else 
                return true;
        }
        bstnode *findMin(bstnode *t) const
        {
            if(t!=nullptr)
            {
                while(t->left!=nullptr)
                    t = t->left;
                return t;
            }
        }
        bstnode *findMax(bstnode *t) const
        {
            if(t!=nullptr)
            {
                while(t->right != nullptr)
                    t = t->right;
            }
            return t;
        }
        void inorder(bstnode *t)
        {
            if(t!=nullptr)
            {
                inorder(t->left);
                cout<<t->element<<" ";
                inorder(t->right);
            }
        }
        public:
        BST()
        {
            root = nullptr;
        }
        void insert(const T &x) { insert(x,root); }
        void remove(const T &x) { remove(x,root); }
        bool search(const T &x) { return search(x,root); }
        T &findMin() const { return findMin(root)->element; }
        T &findMax() const { return findMax(root)->element; }
        void inorder() { inorder(root); }
};
int main()
{
    BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.inorder();
    tree.insert(20);
    tree.inorder();
    tree.remove(5);
    tree.inorder();
    cout<<tree.findMax()<<" ";
    cout<<tree.findMin();
    return 0;
}