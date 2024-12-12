#pragma once
#include<iostream>
#include<fstream>

using namespace std;

struct Node
{
	int value = 0;
	int bf = 0; //balance factor
	Node* left = NULL;
	Node* right = NULL;
};

class BinTree
{
private:
	Node* top;
	int nodeCount = 0;
	bool rotate = true;
	void recInOrder(Node* temp);
	void recClear(Node* trav);
	void balanceCreateTree(int* balanceArr, int low, int high);
	void balanceFillArr(int* balanceArr, int& position, Node* trav);
	void recSave(Node* temp, ofstream& file);
	void RSingleRotate(Node** trav);
	void LSingleRotate(Node** trav);
	void LRDoubleRotate(Node** trav);
	void RlDoubleRotate(Node** trav);

public:
	BinTree();
	~BinTree()
	{
		clear();
	}
	void addItem(int item);
	bool delete_(int value);
	bool search(int value);
	void clear();
	void balance();
	void inOrder();
	void save();
	void load();
	void AVLAddItem(Node** trav, int value);
};

BinTree::BinTree()
{
	top = NULL;
}

void BinTree::addItem(int item)  // 
{
	if (top == nullptr)
	{
		top = new Node;
		top->value = item;
	}
	else // 1+ items
	{
		Node* trav = top;
		while (true)
		{
			if ((item < trav->value) && (trav->left != NULL))
			{
				trav = trav->left;
			}
			else if ((item < trav->value) && (trav->left == NULL))
			{
				trav->left = new Node;
				trav->left->value = item;
				break;
			}
			else if ((item >= trav->value) && (trav->right != NULL))
			{
				trav = trav->right;
			}
			else // greater and right is null
			{
				trav->right = new Node;
				trav->right->value = item;
				break;
			}
		}
	}
	nodeCount++;
}

bool BinTree::delete_(int value) 
{
	Node* parent = NULL;
	Node* child= top;

	while (true)
	{
		if (child == NULL) 
		{
			return false;
		}
		if (value < child->value) 
		{
			parent = child;
			child = child->left;
		}
		else if (value > child->value)
		{
			parent = child;
			child = child->right;
		}
		else 
		{
			//this is where we find the value
			break;
		}
	}
	
	if (child->left == NULL && child->right == NULL)
	{
		if (parent->left == child)
		{
			parent->left == NULL;
		}
		else
		{
			parent->right = NULL;
		}
		delete child;
	}
	else if (child->right == NULL)
	{
		if (parent->left == child)
		{
			parent->left = child->left;
		}
		else
		{
			parent->right = child->left;
		}
		delete child;
	}
	else if (child->left == NULL)
	{
		if (parent->right == child)
		{
			parent->right = child->right;
		}
		else
		{
			parent->left = child->right;
		}
		delete child;
	}
	else  // if there are two children
	{
		Node* parent2 = NULL;
		Node* child2 = child->left;

		while (child2->right)
		{
			parent2 = child2;
			child2 = child2->right;
		}

		child->value = child2->value;

		if (parent2 != NULL)
		{
			parent2->right = child2->left;
		}
		else
		{
			child->left = child2->left;
		}
		delete child2;
	}
}

bool BinTree::search(int value) 
{
	Node* temp = top;
	while (true)
	{
		if (temp == NULL)
		{
			cout << "not found!";
			return false;
		}
		if (value < temp->value)
		{
			temp = temp->left;
		}
		else if (value > temp->value)
		{
			temp = temp->right;
		}
		else
		{
			cout << value << " is found!";
			return true;
		}
	}
}

void BinTree::recClear(Node* trav)
{
	if (trav == NULL)
	{
		return;
	}
	recClear(trav->left);
	recClear(trav->right);
	delete trav;
}

void BinTree::clear()
{
	recClear(top);
}

void BinTree::balanceFillArr(int* balanceArr, int& position, Node* trav)
{
	if (trav->left != NULL)
	{
		balanceFillArr(balanceArr, position, trav->left);
	}

	balanceArr[position] = trav->value;
	position++;

	if (trav->right != NULL)
	{
		balanceFillArr(balanceArr, position, trav->right);
	}
}

void BinTree::balanceCreateTree(int* balanceArr, int low, int high)
{
	int mid = (low + high) / 2;
	addItem(balanceArr[mid]);
	if (mid + 1 <= high)
	{
		balanceCreateTree(balanceArr, mid + 1, high);
	}
	if (mid -1 >= low)
	{
		balanceCreateTree(balanceArr, low, mid-1);
	}
}

void BinTree::balance()
{
	int* balanceArr = new int[nodeCount];
	int position = 0;
	top = NULL;
	int low = 0;
	int high = nodeCount - 1;

	balanceFillArr(balanceArr, position, top);
	balanceCreateTree(balanceArr, low, high);

	delete[] balanceArr;
}

void BinTree::recInOrder(Node* temp)
{
	if (temp->left != NULL)
	{
		recInOrder(temp->left);
	}
	cout << temp->value << " ";
	if (temp->right != NULL)
	{
		recInOrder(temp->right);
	}
}

void BinTree::inOrder()
{
	recInOrder(top);
}

void BinTree::recSave(Node* temp, ofstream& outfile)  // just like recIn Order but instead move the write out to go into a file
{
	if (temp->left != NULL)
	{
		recSave(temp, outfile);
	}
	if (temp->right != NULL)
	{
		recSave(temp, outfile);
	}
	outfile << temp->value << " ";
}

void BinTree::save()
{
	char fileName[25] = " ";
	ofstream outfile(fileName);

	if (top == NULL)
	{
		cout << "The tree is empty, please add values and try again." << endl;
	}

	balance();

	cout << "Name of file: ";
	cin >> fileName;

	recSave(top, outfile);
	clear();
}

void BinTree::load()
{
	char fileName[25];

	cout << "Enter the file name: ";
	cin >> fileName;

	clear();
	
	ifstream inFile(fileName);

	while (!inFile.eof())
	{
		int value;
		inFile >> value;
		addItem(value);
	}

	inFile.close();
}

void BinTree::RSingleRotate(Node** trav)
{
	Node* temp = (*trav)->left;
	(*trav)->left = temp->right;
	temp->right = *trav;
	*trav = temp;

	(*trav)->bf = 0;
	(*trav)->right->bf = 0;
}

void BinTree::LSingleRotate(Node** trav)
{
	Node* temp = (*trav)->right;
	(*trav)->right = temp->left;
	temp->left = *trav;
	*trav = temp;

	(*trav)->bf = 0;
	(*trav)->left->bf = 0;
}

void BinTree::LRDoubleRotate(Node** trav)
{
	Node* temp = (*trav)->left->right;
	(*trav)->left->right = temp->left;
	temp->left = (*trav)->left;
	(*trav)->left = temp->right;
	temp->right = *trav;
	*trav = temp;

	if ((*trav)->bf == 0)
	{
		(*trav)->left->bf = 0;
		(*trav)->right->bf = 0;
	}
	else if ((*trav)->bf == -1)
	{
		(*trav)->bf = 0;
		(*trav)->right->bf = 1;
		(*trav)->left->bf = 0;
	}
	else if ((*trav)->bf == 1)
	{
		(*trav)->bf = 0;
		(*trav)->right->bf = 0;
		(*trav)->left->bf = -1;
		}
}

void BinTree::RlDoubleRotate(Node** trav)
{
	Node* temp = (*trav)->right->left;
	(*trav)->right->left = temp->right;
	temp->right = (*trav)->right;
	(*trav)->right = temp->left;
	temp->left = *trav;
	*trav = temp;

	if ((*trav)->bf == 0)
	{
		(*trav)->left->bf = 0;
		(*trav)->right->bf = 0;
	}
	else if ((*trav)->bf == -1)
	{
		(*trav)->bf = 0;
		(*trav)->left->bf = 1;
		(*trav)->right->bf = 0;
	}
	else if ((*trav)->bf == 1)
	{
		(*trav)->bf = 0;
		(*trav)->left->bf = 0;
		(*trav)->right->bf = -1;
		}

}

void BinTree::AVLAddItem(Node** trav, int value)
{
	rotate = true;
	if (*trav == nullptr)
	{
		Node* temp = new Node;
		temp->value = value;
		*trav = temp;
		return;
	}
	else if ((*trav)->value > value)
	{
		AVLAddItem(&(*trav)->left, value);
		if (rotate == true)
		{
			if ((*trav)->bf == 1)
			{
				(*trav)->bf = 0;
				rotate = false;
			}
			else if ((*trav)->bf == 0)
			{
				(*trav)->bf = -1;
			}
			else  // -1
			{
				if ((*trav)->left->bf < 0)
				{
					RSingleRotate(trav);
					rotate = false;
				}
				else
				{
					LRDoubleRotate(trav);
					rotate = false;
				}
			}
		}
	}
	else if ((*trav)->value < value)
	{
		AVLAddItem(&(*trav)->right, value);

		if (rotate == true)
		{
			if ((*trav)->bf == -1)
			{
				(*trav)->bf = 0;
				rotate = false;
			}
			else if ((*trav)->bf == 0)
			{
				(*trav)->bf = 1;
			}
			else  // 1
			{
				if ((*trav)->right->bf > 0)
				{
					LSingleRotate(trav);
					rotate = false;
				}
				else
				{
					RlDoubleRotate(trav);
					rotate = false;
				}
			}
		}
	}
}