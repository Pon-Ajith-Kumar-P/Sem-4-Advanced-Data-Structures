#include <iostream>
#include "Bst.h"

int main() {
    Bst<int> tree;
    int choice, value;

    while (true) {
        std::cout << "\n ******MAIN MENU******* \n";
        std::cout << "\n 1. Insert Element";
        std::cout << "\n 2. Display Tree Horizontally";
        std::cout << "\n 3. Preorder Traversal";
        std::cout << "\n 4. Inorder Traversal";
        std::cout << "\n 5. Postorder Traversal";
        std::cout << "\n 6. Find the smallest element";
        std::cout << "\n 7. Find the largest element";
        std::cout << "\n 8. Delete an element";
        std::cout << "\n 9. Count the total number of nodes";
        std::cout << "\n 10. Determine the height of the tree";
        std::cout << "\n 11. Delete the tree";
        std::cout << "\n 12. Exit";
        std::cout << "\n\n Enter your option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to be inserted: ";
                std::cin >> value;
                tree.insert(value);
                std::cout << "Horizontal display of the tree:\n";
                tree.display();
                break;
            case 2:
                std::cout << "Horizontal display of the tree:\n";
                tree.display();
                break;
            case 3:
                std::cout << "Preorder traversal: ";
                tree.preOrder();
                break;
            case 4:
                std::cout << "Inorder traversal: ";
                tree.inOrder();
                break;
            case 5:
                std::cout << "Postorder traversal: ";
                tree.postOrder();
                break;
            case 6:
                tree.findSmallest();
                break;
            case 7:
                tree.findLargest();
                break;
            case 8:
                std::cout << "Enter the value to be deleted: ";
                std::cin >> value;
                tree.deleteNode(value);
                std::cout << "Horizontal display of the tree:\n";
                tree.display();
                break;
            case 9:
                tree.countNodes();
                break;
            case 10:
                tree.treeHeight();
                break;
            case 11:
                tree.deleteTree();
                std::cout << "The tree has been deleted.\n";
                break;
            case 12:
                exit(0);
            default:
                std::cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}
