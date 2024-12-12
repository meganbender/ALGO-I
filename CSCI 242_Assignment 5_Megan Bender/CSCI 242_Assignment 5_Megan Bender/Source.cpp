#include<fstream>
#include<iostream>
#include"Header.h"
#include<unordered_map>
#include<cstring>

using namespace std;

int main()
{
	char fileName[25];
	int carryWeight = 0; int stuffCount = 0; int rowCount = 0;
	Item StuffToSteal[10];
	// the first value is the NAME, the second is the WEIGHT, and the third is the VALUE, the fourth is the TAKEN COUNT
	unordered_map <int, tuple<string, int, int, int>> hashLookup; // Here we are creating a hashmap with two values per key, this way i can have the weight and the name, more info on why down below
	int hRowCount = 1; //for the hashmap
	int curRow = rowCount;
	int curCol = carryWeight;

	cout << "\t\tJESSE THE BODY-BUILDING BURGLAR" << endl;
	cout << "Enter the name of the file: ";
	cin >> fileName;


	// reading in the information from the file and inputing it into StuffToSteal
	ifstream inFile(fileName);

	hashLookup[0] = make_tuple("N/a", -1, -1, 0); //creating the first row of the hashmap 
	inFile >> carryWeight;
	while (!inFile.eof())
	{
		inFile >> StuffToSteal[stuffCount].name;
		inFile >> StuffToSteal[stuffCount].qty;
		inFile >> StuffToSteal[stuffCount].weight;
		inFile >> StuffToSteal[stuffCount].value;

		//creating the hashmap lookup table that corresponds to the rows so later we know names of which items we have taken right away
		if (StuffToSteal[stuffCount].qty > 1)
		{
			for (int i = rowCount; i < rowCount + StuffToSteal[stuffCount].qty; i++)
			{
				hashLookup[hRowCount] = make_tuple(StuffToSteal[stuffCount].name, StuffToSteal[stuffCount].weight, StuffToSteal[stuffCount].value, 0);
				hRowCount++;
			}
		}
		else
		{
			hashLookup[hRowCount] = make_tuple(StuffToSteal[stuffCount].name, StuffToSteal[stuffCount].weight, StuffToSteal[stuffCount].value, 0);
			hRowCount++;
		}

		rowCount += StuffToSteal[stuffCount].qty;
		stuffCount++;
	}

	//cout << "value 1(name): " << get<0>(hashLookup[9]) << " value 2(weight): " << get<1>(hashLookup[9]) << " value 3(value): " << get<2>(hashLookup[9]) << " value 4(taken count): " << get<2>(hashLookup[9]) << endl;
	inFile.close();

	int** theTable = new int* [rowCount];
	for (int row = 0; row < rowCount + 1; row++)
	{
		theTable[row] = new int[carryWeight + 1];
		for (int col = 0; col < carryWeight + 1; col++)
		{
			theTable[row][col] = 0;
		}
	}


	// I know we talked about using something along th lines of the below code but I choose a different direction
		//	/*for (int i = 0; i < stuffCount; i++)
		// {
		//	(missing stuff here)rowCount += StuffToSteal[i].qty;
		// }
	// creating the look up table in order to know which items are located in each row
	// creating a hashmap as the lookup table since they are used for key-value retrieval and since the entire purpose of the lookup
		// is to simply be a way to retrieve what is in that row I believe this is a more effective way
		// this has actually been moved and added to the initial creation of the 2d arrray "theArray" (2D array)

	//filling in acutal values and adding as such
	for (int row = 1; row < rowCount + 1; row++)
	{
		for (int col = 1; col < carryWeight + 1; col++)
		{
			if (col - get<1>(hashLookup[row]) < 0)
			{
				theTable[row][col] = theTable[row - 1][col];
			}
			else
			{
				if (theTable[row - 1][col] > theTable[row - 1][col - get<1>(hashLookup[row])] + get<2>(hashLookup[row]))
				{
					theTable[row][col] = theTable[row - 1][col];
				}
				else
				{
					theTable[row][col] = theTable[row - 1][col - get<1>(hashLookup[row])] + get<2>(hashLookup[row]);
				}
			}
		}
	}

	int curRow2 = rowCount; 
	int curCol2 = carryWeight; 
	// changing taken count
	while (theTable[curRow2][curCol2] > 0)
	{
		if (theTable[curRow2][curCol2] == theTable[curRow2 - 1][curCol2])
		{
			curRow2 -= 1;
		}
		else
		{
			get<3>(hashLookup[curRow2])++;
			curCol2 -= get<1>(hashLookup[curRow2]);
			curRow2 -= 1;
		}
	}

	for (int stsItem = 0; stsItem < stuffCount; stsItem++) // stsItem (stuffToSteal items)
	{
		for (int key = 0; key < rowCount + 1; key++)
		{
			if ((StuffToSteal[stsItem].name == get<0>(hashLookup[key])) && (get<3>(hashLookup[key]) > 0))
			{
				StuffToSteal[stsItem].takenCount++;
			}
		}
	}

	for (int cur = 0; cur < stuffCount; cur++)
	{
		if (StuffToSteal[cur].takenCount > 0)
		{
			if (cur < stuffCount - 1)
			{
				cout << StuffToSteal[cur].takenCount
					<< " " << StuffToSteal[cur].name
					<< ", ";
			}
			else
			{
				cout << StuffToSteal[cur].takenCount
					<< " " << StuffToSteal[cur].name
					<< " ";
			}
		}
	}
	cout << theTable[rowCount][carryWeight] << endl; 

	return 0;
}