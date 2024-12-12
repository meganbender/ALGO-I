#include<iostream>
#include "Functions.h"

void algMenu(char& algChoice)
{
	std::cout << "\nChoose a sorting algorithm: "
		<< "\n\ta) Bubble Sort"
		<< "\n\tb) Selection Sort"
		<< "\n\tc) Insertion Sort"
		<< "\n\td) Shell Sort"
		<< "\n\te) Merge Sort"
		<< "\n\tf) Quick Sort"
		<< "\n\tg) Quit" << "\n\t=> ";
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

	//since I made the read file a function I am going to make everything a 
	//one based array and modify whats needed above
	arrayToSort[0] = 0;

	for (int i = 1; i < size + 1; i++) {
		fread(&readVal, sizeof(readVal), 1, inFile);
		arrayToSort[i] = readVal;
	}

	fclose(inFile);

	return arrayToSort;
}

void innerMerge(int low, int mid, int high, int* src, int* dest)
{
	int curList1 = low; int endList1 = mid;
	int curList2 = mid + 1; int endList2 = high;
	int curDest = low;

	while ((curList1 <= endList1) && (curList2 <= endList2))
	{
		if (src[curList1] <= src[curList2])
		{
			dest[curDest] = src[curList1];
			curDest++;
			curList1++;
		}
		else
		{
			dest[curDest++] = src[curList2++];
		}
	}
	if (curList1 > endList1) //firt list is empty
	{
		while(curList2 <= endList2)
		{
			dest[curDest] = src[curList2];
			curDest++; curList2++;
		}
	}
	else if (curList2 > endList2) //second list is empty
	{
		while (curList1 <= endList1)
		{
			dest[curDest] = src[curList1];
			curDest++; curList1++;
		}
	}
}

void merge_func(int low, int high, int* src, int* dest)
{
	if (low == high)
	{
		return;
	}
	int mid = (low + high) / 2;

	//left
	merge_func(low, mid, dest, src);
	
	//right
	merge_func(mid+1, high, dest, src);

	//final merge
	innerMerge(low, mid, high, src, dest);
}

int partition(int start, int end, int* arrParam)  //this could be shorter by possibly using boolean operators
{
	int mid = (start + end) / 2;

	arrParam[0] = arrParam[mid];
	arrParam[mid] = arrParam[start];

	while (start != end)
	{
		while ((start != end) && (arrParam[end] > arrParam[0]))
		{
			end--;
		}
		if (start == end)
		{
			break;
		}
		arrParam[start] = arrParam[end];
		start++;
		while ((start != end) && (arrParam[start] < arrParam[0]))
		{
			start++;
		}
		if (start == end)
		{
			break;
		}
		arrParam[end] = arrParam[start];
		end--;
	}
	arrParam[start] = arrParam[0];
	return start;
}

void quickSort_func(int low, int high, int* arrParam2)
{
	int pivot = partition(low, high, arrParam2);  // note: pivot is already sorted

	if (low < pivot-1)  //if we have more than 1 element to the left
	{
		quickSort_func(low, pivot - 1, arrParam2);
	}
	if (high > pivot+1)  //if there is 1 or more elements to the right
	{
		quickSort_func(pivot + 1, high, arrParam2);
	}
}