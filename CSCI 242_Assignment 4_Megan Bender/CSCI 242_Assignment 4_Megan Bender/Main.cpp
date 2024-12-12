#include <iostream>
#include "Header.h"
#include <cstring>

// make sure the stack is not going over 100

int main()
{
	//Walls walls[6][6];

	char fileStr[25];

	std::cout << "\t\tWelcome to the Marble Game!" << "\nIn order to begin please input the test file name: ";
	std::cin >> fileStr;

	Marbles m1(fileStr);

	m1.solve();
	try
	{
		std::cout << m1.GetBestMoves();
	}
	catch (int)
	{
		std::cout << "No Solution!" << std::endl;
	}

	return 0;
}