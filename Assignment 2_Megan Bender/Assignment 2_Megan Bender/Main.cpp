#include<iostream>
#include<time.h>
#include<sys/timeb.h>
#include "Functions.h"
#include<algorithm>

using namespace std;

int main()
{
	char algChoice = ' '; char fileChoice = ' '; char printChoice = ' '; char sortCheckChoice = ' ';
	int size = 0; int lowerBound, upperBound, tempValue;
	int* arrayPtr = NULL; int* srcArrPtr = NULL; int* destArrPtr = NULL;
	struct _timeb timebuffer; char timeline[26];
	

	cout << "\t\tFun with Algorithms x2!" << endl;

	algMenu(algChoice);

	while (tolower(algChoice) != 'g')
	{
		switch (tolower(algChoice))
		{
		case 'a': //bubble sort
		{
			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);

			//time before
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			for (int eol = size; eol > 1; eol--)
			{
				for (int cur = 1; cur < eol; cur++)
				{
					if (arrayPtr[cur] > arrayPtr[cur + 1])
					{
						tempValue = arrayPtr[cur];
						arrayPtr[cur] = arrayPtr[cur + 1];
						arrayPtr[cur + 1] = tempValue;
					}
				}
			}

			//end time
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			cout << "\nDo you want to check if the array is sorted? (y/n)" << endl;
			cin >> sortCheckChoice;
			if (tolower(sortCheckChoice) == 'y')
			{
				if (is_sorted(arrayPtr + 1, arrayPtr + size))
				{
					cout << "Succesfully sorted!!" << endl;
				}
				else
				{
					cout << "Uh ohhh omething went wrong!" << endl;
				}
			}
			else { break; }

			break;
		}

		case 'b': //selection sort
		{
			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);
			int tempValue;

			//start timer
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			for (int eol = size; eol > 1; eol--)
			{
				int bestIdx = 1;
				int cur;
				for (cur = 2; cur <= eol; cur++)
				{
					if (arrayPtr[bestIdx] < arrayPtr[cur])
					{
						bestIdx = cur;
					}
				}
				if (eol != cur)
				{
					tempValue = arrayPtr[bestIdx];
					arrayPtr[bestIdx] = arrayPtr[eol];
					arrayPtr[eol] = tempValue;
				}
			}

			//end time
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			cout << "\nDo you want to check if the array is sorted? (y/n)" << endl;
			cin >> sortCheckChoice;
			if (tolower(sortCheckChoice) == 'y')
			{
				if (is_sorted(arrayPtr + 1, arrayPtr + size))
				{
					cout << "Succesfully sorted!!" << endl;
				}
				else
				{
					cout << "Uh ohhh omething went wrong!" << endl;
				}
			}
			else { break; }

			break;
		}

		case 'c': //insertion sort
		{
			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);
			int uH = 2;

			//start time
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			for (uH = 2; uH <= size; uH++)
			{
				int sH = uH - 1;
				arrayPtr[0] = arrayPtr[uH];
				while (arrayPtr[0] < arrayPtr[sH])
				{
					arrayPtr[sH + 1] = arrayPtr[sH];
					sH--;
				}
				arrayPtr[sH + 1] = arrayPtr[0];
			}

			//end time
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			cout << "\nDo you want to check if the array is sorted? (y/n)" << endl;
			cin >> sortCheckChoice;
			if (tolower(sortCheckChoice) == 'y')
			{
				if (is_sorted(arrayPtr + 1, arrayPtr + size))
				{
					cout << "Succesfully sorted!!" << endl;
				}
				else
				{
					cout << "Uh ohhh omething went wrong!" << endl;
				}
			}
			else { break; }

			break;
		}

		case 'd': //shell sort
		{
			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);
			//add shell
			// zero based array
			int uH = 0;

			//start time
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			int numShells = sqrt(size);

			while (numShells >= 1)
			{
				for (uH = numShells + 1; uH <= size; uH++)
				{
					arrayPtr[0] = arrayPtr[uH];
					int sH = uH - numShells;
					while (sH > 0 && (arrayPtr[0] < arrayPtr[sH]))
					{
						arrayPtr[sH + numShells] = arrayPtr[sH];
						sH -= numShells;
					}
					arrayPtr[sH + numShells] = arrayPtr[0];
				}
				if (numShells == 2)
				{
					numShells = 1;
				}
				else
				{
					numShells = numShells / 3;
				}
			}

			//end time
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			cout << "\nDo you want to check if the array is sorted? (y/n)" << endl;
			cin >> sortCheckChoice;
			if (tolower(sortCheckChoice) == 'y')
			{
				if (is_sorted(arrayPtr + 1, arrayPtr + size))
				{
					cout << "Succesfully sorted!!" << endl;
				}
				else
				{
					cout << "Uh ohhh omething went wrong!" << endl;
				}
			}
			else { break; }

			break;
		}

		case 'e': //merge sort
		{
			fileNameMenu(fileChoice);
			srcArrPtr = readFile(fileChoice, size);
			destArrPtr = new int[size + 1];

			destArrPtr[0] = 0;
			for (int i = 1; i <= size; i++)
			{
				destArrPtr[i] = srcArrPtr[i];
			}

			int lowParam = 1; int highParam = size;

			//Note: create a new array identical in size to the original, becuase we will need two lists
				//one will be the destination and the other will be the source ( in order to fix this i could possibly
				//create an if-else statement in the read file, so when i select option 'e' I can create two identical arrays)

			//start time
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			merge_func(lowParam, highParam, srcArrPtr, destArrPtr);

			//end time
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			cout << "\nDo you want to check if the array is sorted? (y/n)" << endl;
			cin >> sortCheckChoice;
			if (tolower(sortCheckChoice) == 'y')
			{
				if (is_sorted(destArrPtr + 1, destArrPtr + size))
				{
					cout << "Succesfully sorted!!" << endl;
				}
				else
				{
					cout << "Uh ohhh omething went wrong!" << endl;
				}
			}
			else { break; }

			break;
		}

		case 'f': //quick sort
		{
			fileNameMenu(fileChoice);
			arrayPtr = readFile(fileChoice, size);
			int lowParam = 1; int highParam = size;
			//start time
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			//quick sort
			quickSort_func(lowParam, highParam, arrayPtr);

			//start time
			cout << "\nRun time: " << endl;
			_ftime_s(&timebuffer);
			ctime_s(timeline, sizeof(timeline), &(timebuffer.time));
			printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

			cout << "\nDo you want to check if the array is sorted? (y/n)" << endl;
			cin >> sortCheckChoice;
			if (tolower(sortCheckChoice) == 'y')
			{
				if (is_sorted(arrayPtr + 1, arrayPtr + size))
				{
					cout << "Succesfully sorted!!" << endl;
				}
				else
				{
					cout << "Uh ohhh omething went wrong!" << endl;
				}
			}
			else { break; }
			break;
		}
		}

		cout << "\nWould you like to print out a portion of this array? (y/n)" << "=> ";
		cin >> printChoice;
		switch (tolower(printChoice))
		{
		case 'y':
			if (tolower(algChoice) != 'e')
			{
				cout << "Please enter a lower and upper bound index value of the array (i.e. index: 3 - index: 7)" << endl;
				cout << "\tLower Bound: ";
				cin >> lowerBound;
				cout << "\tUpper Bound: ";
				cin >> upperBound;

				if (((tolower(algChoice) == 'a') || (tolower(algChoice) == 'b')) && lowerBound == 0)
				{
					lowerBound++;
					upperBound++;
				}

				for (int i = lowerBound; i <= upperBound; i++)
				{
					cout << arrayPtr[i] << ' ';
					cout << endl;
				}
			}
			else
			{
				cout << "Please enter a lower and upper bound index value of the array (i.e. index: 3 - index: 7)" << endl;
				cout << "\tLower Bound: ";
				cin >> lowerBound;
				cout << "\tUpper Bound: ";
				cin >> upperBound;
				
				lowerBound++; upperBound++;

				for (int i = lowerBound; i <= upperBound; i++)
				{
					cout << destArrPtr[i] << ' ';
					cout << endl;
				}
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