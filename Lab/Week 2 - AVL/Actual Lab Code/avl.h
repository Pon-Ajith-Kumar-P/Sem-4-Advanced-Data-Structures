#ifndef AVL_H
#define AVL_H
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
      AvlNode(const T &e, AvlNode *lt, AvlNode *rt, int ht = 0)
          : element(e), left(lt), right(rt), height(ht) {}
    };
    AvlNode *root;
    
    void insert(const T &x, AvlNode *&t)
    {
        if (isEmpty(t))
            t = new AvlNode(x, nullptr, nullptr, 0);
        else if (x < t->element)
            insert(x, t->left);
        else if (x > t->element)
            insert(x, t->right);
        else
            { ; }
		cout<<"Insertion before Balancing \n";
		printTree();
		cout<<"Insertion after Balancing \n";
        balance(t);
		printTree();
    }

    void remove(const T &x, AvlNode *&t)
    {
        if (isEmpty(t))
            return;
        else if (x < t->element)
            remove(x, t->left);
        else if (x > t->element)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
		cout<<"Deletion before Balancing \n";
		printTree();
		cout<<"Deletion after Balancing \n";
        balance(t);
		printTree();
    }

    void makeEmpty(AvlNode *&t)
    {
        if (!isEmpty(t))
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }

    bool isEmpty(AvlNode *t) const
    {
        return t == nullptr;
    }

    AvlNode *findMin(AvlNode *t) const
    {
        if (!isEmpty(t))
        {
            while (t->left != nullptr)
            {
                t = t->left;
            }
        }
        return t;
    }

    AvlNode *findMax(AvlNode *t) const
    {
        if (!isEmpty(t))
        {
            while (t->right != nullptr)
            {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const T &x, AvlNode *t) const
    {
        if (isEmpty(t))
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (x > t->element)
            return contains(x, t->right);
        else
            return true;
    }

    void printTree(AvlNode *t, int level) const
    {
        if (isEmpty(t))
            return;
        printTree(t->right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "      ";

		int bal_fact =  height(t->left) - height(t->right) ;
        cout << t->element << "(" << bal_fact << ")" << endl;
        printTree(t->left, level + 1);
    }

    int height(AvlNode *t) const
    {
        return (t == nullptr) ? -1 : t->height;
    }

    void balance(AvlNode *&t)
    {
        if (isEmpty(t))
            return;
		
		t->height = max(height(t->left),height(t->right)) + 1;

        if (height(t->left) - height(t->right) > 1)
        {
            if (height(t->left->left) >= height(t->left->right))
                srl(t);
            else
                drl(t);
        }
        else if (height(t->right) - height(t->left) > 1)
        {
            if (height(t->right->right) >= height(t->right->left))
                srr(t);
            else
                drr(t);
        }

		if (t != nullptr)
	        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void srl(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height);
        k2 = k1;
    }

    void srr(AvlNode *&k2)
    {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->right), k2->height);
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

void familydetails(const T &x, AvlNode *t) const
{
    if (isEmpty(t))
    {
        cout << "No element in the tree" << endl;
        return;
    }

    // Traverse the tree to find the node containing the element x
    AvlNode *parent = nullptr;
    AvlNode *grandparent = nullptr;
    AvlNode *current = t;

    while (current != nullptr)
    {
        if (x < current->element)
        {
            grandparent = parent;
            parent = current;
            current = current->left;
        }
        else if (x > current->element)
        {
            grandparent = parent;
            parent = current;
            current = current->right;
        }
        else
        {
            break;
        }
    }

    // If element not found
    if (current == nullptr)
    {
        cout << "Element " << x << " not found in the tree" << endl;
        return;
    }

    // Now 'current' points to the node containing the element x
    cout << "Element : " << current->element << endl;

    // Parent
    if (parent != nullptr)
        cout << "Parent : " << parent->element << endl;
    else
        cout << "Parent : None" << endl;

    // Grandparent
    if (grandparent != nullptr)
        cout << "Grandparent : " << grandparent->element << endl;
    else
        cout << "Grandparent : None" << endl;

    // Sibling
    if (parent != nullptr)
    {
        if (parent->left == current && parent->right != nullptr)
            cout << "Sibling : " << parent->right->element << endl;
        else if (parent->right == current && parent->left != nullptr)
            cout << "Sibling : " << parent->left->element << endl;
        else
            cout << "Sibling : None" << endl;
    }
    else
    {
        cout << "Sibling : None" << endl;
    }

    // Children
    if (current->left != nullptr && current->right != nullptr)
        cout << "Children : " << current->left->element << " " << current->right->element << endl;
    else if (current->left != nullptr)
        cout << "Children : " << current->left->element << endl;
    else if (current->right != nullptr)
        cout << "Children : " << current->right->element << endl;
    else
        cout << "Children : None" << endl;

    // Grandchildren
    if (current->left != nullptr)
    {
        if (current->left->left != nullptr)
            cout << "Grandchildren (Left): " << current->left->left->element << " ";
        if (current->left->right != nullptr)
            cout << "Grandchildren (Right): " << current->left->right->element;
    }
    if (current->right != nullptr)
    {
        if (current->right->left != nullptr)
            cout << "Grandchildren (left): " << current->right->left->element << " ";
        if (current->right->right != nullptr)
            cout <<  "Grandchildren (Right): " << current->right->right->element;
    }
    cout << endl;
}

  public:
    AVL() : root(nullptr) {}
    ~AVL() 
	{ 
		makeEmpty(root); 
	}

    void insert(const T &x) 
	{ 
		insert(x, root); 
	}
	void remove(const T &x) 
	{ 
		remove(x, root); 
	}
    
	const T &findMin() const 
	{ 
		return findMin(root)->element; 
	}
    const T &findMax() const 
	{ 
		return findMax(root)->element; 
	}
    
	bool contains(const T &x) const 
	{ 
		return contains(x, root); 
	}
    
	void printTree() const 
	{
		 printTree(root, 0); 
	}
    
	void familydetails(const T &x) const 
	{ 
		familydetails(x,root); 
	}
};

#endif // AVL_H
