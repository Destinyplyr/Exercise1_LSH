#include <iostream>
#include <fstream>
#include "ListDataHamming.h"
#include "ListsFunctions.h"
#include "NodeFunctions.h"


using namespace std;

int main(int argc, char **argv)
{
	ifstream read1;
	read1.open("DataHamming.csv");
	
	string myString;
	ListDataHamming<string>* hammingList = new ListDataHamming<string>();

	read1 >> myString;  //read "@metric space"
	read1 >> myString;	//read etc, "hamming"

	while (!read1.eof())
	{
		read1 >> myString;	//item etc
		read1 >> myString;	//data we want to store
		hammingList->Insert(myString);
	}

	hammingList->PrintData();

	delete hammingList;
	cin.get();

	return 0;
}