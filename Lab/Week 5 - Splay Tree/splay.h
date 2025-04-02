#ifndef SPLAY_H
#define SPLAY_H
#include<iostream>
using namespace std;
template<class T>
class Splay
{
    private:
        struct BinaryNode
        {
            T element;
            BinaryNode *left;
            BinaryNode *right;
            BinaryNode(const T &elt = T(), BinaryNode *lt=nullptr, BinaryNode *rt=nullptr)
                :element(elt),left(lt),right(rt) {}
        };
        BinaryNode *root;
        BinaryNode *nullNode;

        void makeEmpty()
        {
            while(root!=nullNode)
                remove(root->element);
        }

        void insertNode(const T &x)
        {
            //Setting up the newNode
            static BinaryNode *newNode = nullptr;
            if(newNode==nullptr)
                newNode = new BinaryNode;
            newNode->element = x;
            //Performing Actual Insertion
            if(root == nullNode)
            {
                newNode->left = nullNode;
                newNode->right = nullNode;
                root = newNode;
            }
            else
            {
                splay(x,root);
                if(x<root->element)
                {
                    newNode->left = root->left;
                    newNode->right = root;
                    root->right = nullNode;
                    root = newNode;
                }
                else if(x>root->element)
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
            if(!containsNode(x))
                return;
            BinaryNode *newTree;
            if(root->left == nullNode)
                newTree = root->right;
            else
            {
                newTree = root->left;
                splay(x,root);
                newTree->right = root->right;
            }
            delete root;
            root = newTree;
        }

        bool containsNode(const T &x)
        {
            if(root==nullNode)
                return false;
            splay(x,root);
            return (x==root->element);
        }

        T findMinElt() const
        {
            if(root==nullNode)
                return T();
            BinaryNode *t = root;
            while(t->left != nullNode)
                t=t->left;
            return t->element;
        }

        T findMaxElt() const
        {
            if(root==nullNode)
                return T();
            BinaryNode *t = root;
            while(t->right != nullNode)
                t=t->right;
            return t->element;
        }

        void inorder(BinaryNode *t) const
        {
            if(t!=nullNode)
            {
                inorder(t->left);
                cout<<t->element<<" ";
                inorder(t->right);
            }
        }

        void printTree(BinaryNode *t, int space) const
        {
            if(t==nullNode)
                return;
            space+=5;
            printTree(t->right,space);
            cout<<endl;
            for(int i=5;i<space;i++)
                cout<<" ";
            cout<<t->element<<endl;
            printTree(t->left,space);
        }

        void splay(const T &x, BinaryNode *&t)
        {
            BinaryNode *leftMax, *rightMin;
            static BinaryNode header;
            header.right = header.left = nullNode;
            leftMax = rightMin = &header;
            
            nullNode->element = x;
            while(true)
            {
                if(x<t->element)
                {
                    if(x < t->left->element)
                        rotatewithLchild(t);
                    if(t->left==nullNode)
                        break;
                    rightMin->left = t;
                    rightMin = t;
                    t = t->left;
                }
                else if(x>t->element)
                {
                    if(x < t->right->element)
                        rotatewithRchild(t);
                    if(t->right==nullNode)
                        break;
                    leftMax->right = t;
                    leftMax = t;
                    t = t->right;
                }
                else
                    break;
            }
            rightMin->left = t->right;
            leftMax->right = t->left;
            t->right = header.left;
            t->left = header.right;
        }

        void rotatewithLchild(BinaryNode *&k2)
        {
            BinaryNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        void rotatewithRchild(BinaryNode *&k2)
        {
            BinaryNode *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2 = k1;
        }

    public:
        Splay()
        {
            nullNode = new BinaryNode;
            nullNode->left = nullNode;
            nullNode->right = nullNode;
            root=nullNode;
        }
        ~Splay()
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

        void search(const T &x)
        {
            containsNode(x);
        }

        T findMin() const
        {
            return findMinElt();
        }
 
        T findMax() const
        {
            return findMaxElt();
        }

        void traverse() const
        {
            inorder(root);
        }

        void printTree() const
        {
            printTree(root,0);
        }
};

#endif