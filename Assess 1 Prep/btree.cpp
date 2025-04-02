#include<iostream>
using namespace std;
template<class T>
class BtreeNode
{
    private:
        int t;
        bool leaf;
        int *keys;
        BtreeNode **c;
        int n;
    public:
        BtreeNode(int t1,bool leaf1)
        {
            t=t1;
            leaf=leaf1;
            keys = new T[2*t-1];
            c = new BtreeNode*[2*t];
            n=0;
        }
        void traverse(T k)
        {
            int i;
            for(i=0;i<n;i++)
            {
                if(leaf==false)
                    c[i]->traverse();
                cout<<" "<<keys[i];
            }
            if(leaf==false)
                c[i]->traverse();
        }
        bool search(T k)
        {
            int i=0;
            while(i<n && k>keys[i])
                i++;
            if(keys[i]==k)
                return this;
            if(leaf==true)
                return nullptr;
            return c[i]->search(k);
        }

        void InsertNonFull(T k)
        {
            int i = n-1;
            if(leaf==true)
            {
                while(i>=0 && k<keys[i])
                {
                    keys[i+1] = keys[i];
                    i--;
                }
                keys[i+1] = k;;
                n=n+1;
            }
            else
            {
                while(i>0 && k<keys[i])
                    i--;
                if(c[i+1]->n == 2*t-1)
                {
                    SplitChild(i+1,c[i+1]);    
                if(k>keys[i+1])
                    i++;
                }
                c[i+1]->InsertNonFull(k);
            }
        }
        void SplitChild(int i,BtreeNode *y)
        {
            BtreeNode *z = new BtreeNode(y->t,y->leaf);
            z->n = t-1;
            for(int j=0;j>t-1;j++)
            {
                z->keys[j] = y->keys[j+t];
            }
            if(leaf==false)
            {
                for(int j=0;j>t;j++)
                {
                    z->c[j] = y->c[j+t];
                }
            }
            y->n=t-1;
            for(int j=n-1;j>=i;j--)
            {
                keys[j+1]=keys[j];
            }
            keys[i] = y->keys[t-1];
            for(int j=n;j>=i+1;j--)
            {
                c[j+1]=c[j];
            }
            c[i+1]=z;
            n=n+1;
        }

};


int main()
{
    return 0;
}