#include<iostream>
#include<fstream>
#include "Functions.h"

void algMenu(char& algChoice)
{
	std::cout << "\nChoose a sorting algorithm: "
		<< "\n\ta) Heap Sort"
		<< "\n\tb) Radix/Bin Sort"
		<< "\n\tc) Quit" << "\n\t=> ";
	std::cin >> algChoice;
}

void fileNameMenu(char& choiceParam)
{
	std::cout << "\nWhich file would you like to sort?"
		<< "\n\ta) 10 numbers"
		<< "\n\tb) 100 numbers"
		<< "\n\tc) 1 million numbers sorted"
		<< "\n\td) 1 million numbers random"
		<< "\n\te) 10 million numbers" << "\n\t=> ";
	std::cin >> choiceParam;
}

int* readFile(char fileOption, int& sizeParam)
{
	int* arrayToSort;
	std::string fileName;
	int size, readVal;

	if (fileOption == 'a')
	{
		fileName = "10numbers.bin";
	}
	else if (fileOption == 'b')
	{
		fileName = "100numbers.bin";
	}
	else if (fileOption == 'c')
	{
		fileName = "1000000almostsorted.bin";
	}
	else if (fileOption == 'd')
	{
		fileName = "1000000numbers.bin";
	}
	else if (fileOption == 'e')
	{
		fileName = "10000000numbers.bin";
	}

	FILE* inFile;

	fopen_s(&inFile, fileName.c_str(), "rb");
	fread(&size, sizeof(size), 1, inFile);
	arrayToSort = new int[size + 1];

	sizeParam = size;

	arrayToSort[0] = 0;

	for (int i = 1; i < size + 1; i++) {
		fread(&readVal, sizeof(readVal), 1, inFile);
		arrayToSort[i] = readVal;
	}

	fclose(inFile);

	return arrayToSort;
}

void heapWalkUp(int *arrayParam, int sizeParam)
{
	for (int cur = 2; cur < sizeParam +1 ; cur++)
	{
		int child = cur;
		int parent = cur / 2;

		while ((arrayParam[child] > arrayParam[parent]))
		{
			arrayParam[0] = arrayParam[parent];
			arrayParam[parent] = arrayParam[child];
			arrayParam[child] = arrayParam[0];

			child = parent;
			parent /= 2;
		}
	}
}

void heapWalkDown(int* arrayParam, int sizeParam)
{
	int parent = -1; int child1 = -1; int child2 = -1;

	for (int eol = sizeParam; eol >= 1; eol--)
	{
		int temp = 0;

		temp = arrayParam[eol];
		arrayParam[eol] = arrayParam[1];
		arrayParam[1] = temp;

		parent = 1;
		child1 = parent * 2;
		child2 = parent * 2 + 1;

		while (child2 < eol || child1 < eol)
		{
			int biggest = -1;

			if ((child2 > eol - 1) || (arrayParam[child1] > arrayParam[child2]))
			{
				biggest = child1;
			}
			else
			{
				biggest = child2;
			}

			if (arrayParam[biggest] > arrayParam[parent])
			{
				temp = arrayParam[biggest];
				arrayParam[biggest] = arrayParam[parent];
				arrayParam[parent] = temp;
			}
			else { break; }

			parent = biggest;
			child1 = parent * 2;
			child2 = parent * 2 + 1;
		}
	}
}

struct Node
{
	int value = -1;
	Node* next = NULL;
};

struct BinNode
{
	Node* front = NULL;
	Node* back = NULL;
};

void radixSort(int* arrayParam, int sizeParam)
{
	BinNode bins[10];
	Node* NodeArray = new Node[sizeParam];
	int biggest = arrayParam[0]; int count = 0; int binNum;

	for (int i = 1; i < sizeParam + 1; i++)
	{
		if (arrayParam[i] > biggest)
		{
			biggest = arrayParam[i];
		}
	}

	while (biggest > 0)
	{
		count++;
		biggest /= 10;
	}

	for (int curDigit = 0; curDigit < count; curDigit++)
	{
		//binning process
		for (int i = 1; i < sizeParam + 1; i++)
		{
			binNum = int (arrayParam[i] / pow(10, curDigit)) % 10;

			if (bins[binNum].front == NULL)  //empty list
			{
				bins[binNum].front = &(NodeArray[i-1]);  //needed since this is a 1-based array
			}
			else
			{
				bins[binNum].back->next = &(NodeArray[i-1]);
			}

			bins[binNum].back = &(NodeArray[i-1]);
			bins[binNum].back->value = arrayParam[i];
		}

		//unbinning process
		int i = 1;
		for (int curBin = 0; curBin < 10; curBin++)
		{
			while (bins[curBin].front != NULL)
			{
				arrayParam[i++] = bins[curBin].front->value;
				Node* temp = bins[curBin].front;
				bins[curBin].front = bins[curBin].front->next;
				temp->next = NULL;
			}
			bins[curBin].back = NULL;
		}
	}
}