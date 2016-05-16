#include <vector>
#include <iostream>
#include "DungeonLevel.h"

using namespace std;

int ymain()
{
	int int_NumLevels;
	cout << "How many levels to generate: ";
	cin >> int_NumLevels;
	cin.ignore();

	for (int i = 0; i < int_NumLevels; i++)
	{
		DungeonLevel DL_1;

		cout << "Level: " << i+1 << endl;
		DL_1.unitTestReqs(true);

		cout << endl << "Press Enter to continue to next Level";
		cin.ignore();
		cout << endl << endl;
	}

	return 0;
}