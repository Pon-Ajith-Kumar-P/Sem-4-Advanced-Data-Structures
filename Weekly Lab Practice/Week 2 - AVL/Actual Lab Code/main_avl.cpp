#include<iostream>
#include<algorithm>
#include "avl.h"
using namespace std;
int main()
{
	AVL<int> tree;
	int choice, value;
	do
	{
		cout<<"\n---AVL Operations---";
		cout<<"\n1. Insert Element";
		cout<<"\n2. Delete Element";
//		cout<<"\n3. FindMin";
//		cout<<"\n4. FindMax";
		cout<<"\n3. Search Element";
		cout<<"\n4. Print the Tree";
		cout<<"\n5. Family Informations";
		cout<<"\n6. Exit";
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\nEnter the value to insert : ";
				cin>>value;
				tree.insert(value);
				break;
			case 2:
				cout<<"\nEnter the value to delete : ";
				cin>>value;
				tree.remove(value);
				break;
/*
			case 3:
				cout<<"\nMinimum Element = "<<tree.findMin();
				break;
			case 4:
				cout<<"\nMaximum Element = "<<tree.findMax();
				break;
*/			case 3: 
				cout<<"\nEnter the value to search : ";
				cin>>value;
				if(tree.contains(value))
					cout<<"\nValue found in the tree";
				else
					cout<<"\nValue not found in the tree";
				break;
			case 4:
				cout<<"\nDisplaying the Tree\n";
				tree.printTree();
				break;
			case 5:
				cout<<"\nEnter the value to get details : ";
				cin>>value;
	                        tree.familydetails(value);
				break;
			case 6:
				cout<<"\nThank You";
				break;
			default:
				cout<<"\nInvalid choice";
		}
	}while(choice!=6);
}
