#include<iostream>
#include<fstream>
#include"Functions.h"
#include<time.h>
#include<sys/timeb.h>
#include<algorithm>

int main()
{
	char algChoice = ' '; char fileChoice = ' '; char printChoice = ' '; char sortCheckChoice = ' ';
	int size = 0; int lowerBound, upperBound, tempValue;
	int* arrayPtr = NULL; int* destArrPtr = NULL;
	struct _timeb timebuffer; char timeline[26];


	std::cout << "\t\tSorting Algorithms"
		<< "\n\t      ~~Heap and Radix/Bin~~" << std::endl;

	algMenu(algChoice);

	while (tolower(algChoice) != 'c')
	{
		if (tolower(algChoice) == 'a')
		{ // heap sort

			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);

			//start time
			std::cout << "\nRun time: " << std::endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			// --- heap sort algorithm --- //
			heapWalkUp(arrayPtr, size);
			heapWalkDown(arrayPtr, size);

			//end time
			std::cout << "\nRun time: " << std::endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			//checking if the list is sorted
			if (std::is_sorted(arrayPtr + 1, arrayPtr + size))
			{
				std::cout << "Succesfully sorted!!" << std::endl;
			}
			else
			{
				std::cout << "Error, not sorted!" << std::endl;
			}
		}
		else
		{ // radix sort
			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);

			//start time
			std::cout << "\nRun time: " << std::endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			// --- radix sort algorithm --- //
			radixSort(arrayPtr, size);

			//end time
			std::cout << "\nRun time: " << std::endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			//checking if the list is sorted
			if (std::is_sorted(arrayPtr + 1, arrayPtr + size))
			{
				std::cout << "Succesfully sorted!!" << std::endl;
			}
			else
			{
				std::cout << "Error, not sorted!" << std::endl;
			}
		}

		std::cout << "\nWould you like to print out a portion of this array? (y/n)" << "=> ";
		std::cin >> printChoice;
		switch (tolower(printChoice))
		{
		case 'y':
			std::cout << "Please enter a lower and upper bound index value of the array (i.e. index: 3 - index: 7). " << std::endl;
			std::cout << "\tLower Bound: ";
			std::cin >> lowerBound;
			std::cout << "\tUpper Bound: ";
			std::cin >> upperBound;

			for (int i = lowerBound; i <= upperBound; i++)
			{
				std::cout << arrayPtr[i] << ' ';
				std::cout << std::endl;
			}
			break;

		case 'n':
			break;
		}



		//delete[] arrayPtr; delete[] srcArrPtr; delete[] destArrPtr;  //deallocating memory

		algMenu(algChoice);

	}

	return 0;
}