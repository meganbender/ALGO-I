#include<iostream>
#include "Functions.h"

using namespace std;

void main()
{
	BinTree Tree;
	int choice = ' ';
	Node* root = nullptr;
	Node** temp = &root;
	
	//Tree.addItem(25);
	//Tree.addItem(10);
	//Tree.addItem(35);
	//Tree.addItem(5);
	//Tree.addItem(15);
	//Tree.addItem(30);
	//Tree.addItem(40);
	//Tree.addItem(1);
	//Tree.addItem(7);
	//Tree.addItem(12);
	//Tree.addItem(20);

	//Tree.search(10);
	//Tree.delete_(10);
	//Tree.search(7);
	//Tree.search(10);

	//Tree.clear();

	//Tree.addItem(1);
	//Tree.addItem(2);
	//Tree.addItem(3);
	//Tree.addItem(4);
	//Tree.addItem(5);
	//Tree.addItem(6);
	//Tree.addItem(7);
	//Tree.addItem(8);
	//Tree.addItem(9);
	//Tree.addItem(10);
	//Tree.addItem(11);

	//Tree.balance();

	//Tree.AVLAddItem(temp, 49);
	//Tree.AVLAddItem(temp, 17);
	//Tree.AVLAddItem(temp, 71);
	//Tree.AVLAddItem(temp, 8);
	//Tree.AVLAddItem(temp, 4);


	Tree.AVLAddItem(temp, 50);
	Tree.AVLAddItem(temp, 25);
	Tree.AVLAddItem(temp, 75);
	Tree.AVLAddItem(temp, 15);
	Tree.AVLAddItem(temp, 30);
	Tree.AVLAddItem(temp, 65);
	Tree.AVLAddItem(temp, 90);
	Tree.AVLAddItem(temp, 10);
	Tree.AVLAddItem(temp, 20);
	Tree.AVLAddItem(temp, 28);
	Tree.AVLAddItem(temp, 40);
	Tree.AVLAddItem(temp, 60);
	Tree.AVLAddItem(temp, 80);
	Tree.AVLAddItem(temp, 100);
	Tree.AVLAddItem(temp, 12);
	Tree.AVLAddItem(temp, 27);
	Tree.AVLAddItem(temp, 32);
	Tree.AVLAddItem(temp, 45);
	Tree.AVLAddItem(temp, 43);
}