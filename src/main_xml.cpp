#pragma once

#include <string>
#include <fstream>
#include "parser.h"

using namespace std;

int xmain(int argc, char * argv[])
{
	string infilename;
	string outfilename;
	ifstream input;
	ofstream output;
	vector<XMLSerializable*> vObjects;

	cout << "What is the input filename? ";
	cin >> infilename;
	input.open(infilename.c_str());
	parseXML(input, vObjects);
	input.close();

	cout << endl;
	for (size_t i=0; i<vObjects.size(); i++)
	{
		vObjects[i]->dumpObject();
	}
	cout << endl;

	cout << "What is the output filename? ";
	cin >> outfilename;
	output.open(outfilename.c_str());
	outputXML(vObjects, output);
	output.close();

	return 0;
}
