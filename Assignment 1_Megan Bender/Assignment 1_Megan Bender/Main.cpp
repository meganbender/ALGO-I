#include<iostream>
#include<time.h>
#include<sys/timeb.h>

using namespace std;

void algMenu(char& param);
void fileNameMenu(char& filecChoiceParam);
int* readFile(char fileChoiceParam, int &sizeParam);

int main()
{
	int size = 0;
	int *arrayPtr;
	char algChoice = ' ';
	char fileChoice = ' ';
	int tempValue;
	struct _timeb timebuffer;
	char timeline[26];
	char printChoice = ' ';
	int lowerBound, upperBound;

	cout << "\t\tFun with Algorithms!" << endl;

	algMenu(algChoice);

	while (tolower(algChoice) != 'e')
	{

		if (tolower(algChoice) == 'a')
		{//bubble sort algorithm
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
		}
		else if (tolower(algChoice) == 'b')
		{//selection sort algorithm
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
		}
		else if (tolower(algChoice) == 'c')
		{//insertion sort algorithm
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
		}
		else if (tolower(algChoice) == 'd')
		{//shell sort algorithm
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

			;
		}
		else { break; }

		cout << "\nWould you like to print out a portion of this array? (y/n)" << "=> ";
		cin >> printChoice;
		switch (tolower(printChoice))
		{
		case 'y':
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
			break;

		case 'n':
			break;
		}
		
		delete[] arrayPtr; //deallocating memory

		algMenu(algChoice);
	}

	return 0;
}

void algMenu(char& algChoice)
{
	cout << "\nChoose a sorting algorithm: " 
		<< "\n\ta) Bubble Sort"
		<< "\n\tb) Selection Sort"
		<< "\n\tc) Insertion Sort"
		<< "\n\td) Shell Sort" 
		<< "\n\te) Quit" << "\n\t=> ";
	cin >> algChoice;
}

void fileNameMenu(char& choiceParam)
{
	cout << "\nWhich file would you like to sort?"
		<< "\n\ta) 10 numbers"
		<< "\n\tb) 100 numbers"
		<< "\n\tc) 1000000 numbers sorted"
		<< "\n\td) 1000000 numbers random" << "\n\t=> ";
	cin >> choiceParam;
}

int* readFile(char fileOption, int &sizeParam)
{
	int *arrayToSort;
	string fileName;
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

	FILE* inFile;

	fopen_s(&inFile, fileName.c_str(), "rb");
	fread(&size, sizeof(size), 1, inFile);
	arrayToSort = new int[size+1];

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