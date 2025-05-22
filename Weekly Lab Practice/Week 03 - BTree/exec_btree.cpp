#include <iostream>
using namespace std;
template<class T>
class BtreeNode
{
    private:
        int t;
        bool leaf;
        T *keys;
        BtreeNode **c;
        int n;
    public:
        BtreeNode(int t1,bool leaf1)
        {
            t=t1; 
            leaf = leaf1;
            keys = new T[2*t-1];
            c = new BtreeNode*[2*t];
        }
        void traverse()
        {
            for(int i=0;i<n;i++)
            {
                if(leaf==false)
                    c[i]->traverse();
                cout<<keys[i]<<" ";
            }
            if(leaf==false)
                c[i]->traverse();
        }
        BtreeNode* search(T k)
        {
            int i=0;
            while (i<n && keys[i] > k)
                k++;
            if(keys[i]==k)
                return this;
            if(leaf==true)
                return NULL;
            return c[i]->search(k);            
        }
        
        void InsertNonFull(T k)
        {
            int i=n-1;
            if(leaf==true)
            {
                while (i>=0 && keys[i]>k)
                {
                    keys[i+1]=keys[i];
                    i--;
                }
                keys[i+1]=k;
                n++;
            }
            else
            {
                while (i>=0 && keys[i]>k)
                    i--;
                if(c[i+1]->n==2*t-1)
                {
                    SplitChild(i+1,c[i+1]);
                    if(keys[i+1]<k)
                        i++;
                }
                c[i+1]->InsertNonFull(k);
            }
        }
        template<class T>
        friend class Btree;
};
template <class T>
class Btree
{
    private:
        BtreeNode<T> *root;
        int t;
    public:
        Btree(int t1)
        {
            root = nullptr;
            t = t1;
        }
        void traverse()
        {
            if(root!=NULL)
                root->traverse();
        }
        BtreeNode *search(T k)
        {
            return (root==nullptr)?nullptr:root->search(k);
        }
        void insert(T k)
        {
            if(root=nullptr)
            {
                root = new BtreeNode<T> (t,true);
                root->keys[0] = k;
                root->n = 1;
            }
            else if (root->n == 2*t=1)
            {
                BtreeNode<T> *s = new BtreeNode<T> (t,false);
                s->c[i] = root;
                s->SplitChild(0,root);
                int i=0;
                while(k > s->keys[0])
                    i++;
                s->c[i]->InsertNonFull(k);
                s = root;
            }
            else
            {
                root->InsertNonFull(k);
            }
        }
};