#include<iostream>
#include<string>
#include "splay.h"
using namespace std;
int main()
{
    Splay<int> tree;
    int choice, value;
    do
    {
        cout<<"\nSplay Tree Menu"<<endl;
        cout<<"1. Insert"<<endl;
        cout<<"2. Remove"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Find Minimum"<<endl;
        cout<<"5. Find Maximum"<<endl;
        cout<<"6. Inorder Traversal"<<endl;
        cout<<"7. Print Tree"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter value to insert : ";
                cin>>value;
                tree.insert(value);
                tree.printTree();
            break;

            case 2:
                cout<<"\nEnter value to remove : ";
                cin>>value;
                tree.insert(value);
                tree.printTree();
            break;
            
            case 3:
                cout<<"\nEnter value to search : ";
                cin>>value;
                tree.search(value);
                tree.printTree();
            break;
            
            case 4:
                cout<<"\nMinimum Element = "<<tree.findMin();
            break;
            
            case 5:
                cout<<"\nMaximum Element = "<<tree.findMax();
            break;
            
            case 6:
                cout<<"\nInorder Traversal : ";
                tree.traverse();
            break;
            
            case 7:
                tree.printTree();
            break;
            
            case 0:
                cout<<"Exiting Program"<<endl;
            break;

            default:
                cout<<"Invalid Choice"<<endl;

        }

    } while (choice!=0);
    
    return 0;
}