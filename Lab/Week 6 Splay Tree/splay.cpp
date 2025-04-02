#include<iostream>
#include<string>
using namespace std;
template<class T>
class SplayTree
{
    struct BinaryNode
    {
        T element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const T &e = T(), BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
            : element(e),left(lt),right(rt) {}
    };
    BinaryNode *root;
    BinaryNode *nullNode;
    void insertNode(const T &x)
    {
        static BinaryNode *newNode = nullptr;
        if(newNode==nullptr)
            newNode = new BinaryNode;
        newNode->element = x;
        if(root==nullNode)
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        }
        else
        {
            splay(x,root);
            if(x<root->element)
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
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
                return;
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
        return x==root->element;
    }

    void splay(const T &x,BinaryNode *&t)
    {
        BinaryNode *leftMax, *rightMin;
        static BinaryNode *header;
        header.left = header.right = nullNode;
        leftMax = rightMin = &header;

        nullNode->element = x;

        while(true)
        {
            if(x<t->element)
            {
                if(x<t->left->element)
                    srl(t);
                if(t->left==nullNode)
                    break;
                rightMin->left = t;
                rightMin = t;
                t = t->left;
            }
            else if(x>t->element)
            {
                if(x>t->right->element)
                    srr(t);
                if(t->right==nullNode)
                    break;
                leftMax->right = t;
                leftMax = t;
                t = t->right;
            }
            else
            {
                break;
            }    
        }
    }

    void srl(BinaryNode *&k2)
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void srr(BinaryNode *&k2)
    {
        BinaryNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2 = k1;
    }

    
};

int main()
{
    return 0;
}