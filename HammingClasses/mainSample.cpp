#include <iostream>
#include <fstream>
#include "ListDataHamming.h"
#include "ListsFunctions.h"
#include "NodeFunctions.h"

using namespace std;

extern "C"
{
	#include <stdlib.h>
}


int main(int argc, char **argv)
{
	ifstream read1;
	read1.open("DataHamming.csv");
	int choice;
	string myString;
	cout << "********************* Hamming space LSH testing ********************* " << endl << endl;
	
	ListDataHamming<string>* hammingList = new ListDataHamming<string>();
	cout << " 1 : Enter a 64-bit code. " << endl; 
	cout << " 2 : Enter an input's file name." << endl << endl;
	cin >> choice;

	if (choice == 1)
	{
		string code;
		cout << "------->  Give a 64 bit code : " << endl << endl;
		cin >> code;
		if (code.size() != 64)
		{
			cout << "------->  You've given a wrong input. " << endl;
			exit(0);
		}
		read1 >> myString;  //read "@metric space"
		read1 >> myString;	//read etc, "hamming"

		while (!read1.eof())
		{
			read1 >> myString;	//item etc
			read1 >> myString;	//data we want to store
			hammingList->Insert(myString);
			int hdis = hammingList->Distance(myString, code);
			cout << endl;
			cout << "------->  THE HAMMING DISTANCE IS : " << hdis << endl;
		}
	}
	else if (choice == 2)
	{
		string theCode;
		string fileName;
		ifstream inputFile;
		cout << "Give an input's file name (+ extension) : " << endl << endl;
		cin >> fileName;
		inputFile.open(fileName.c_str());

		if (inputFile == NULL)
		{
			cout << "------->  You've given a wrong input file. " << endl;
			exit(1);
		}
		else
		{	
			cout << "File : " << fileName << " opened successfully!" << endl << endl;
		}

		read1 >> myString;  //read "@metric space"
		read1 >> myString;	//read etc, "hamming"
		
		while (!inputFile.eof())
		{
			inputFile >> theCode;	//item etc
			inputFile >> theCode;	//data we want to compare

			while (!read1.eof())
			{
				read1 >> myString;	//item etc
				read1 >> myString;	//data we want to store
				hammingList->Insert(myString);
				int hdis = hammingList->Distance(myString, theCode);
				cout << "------->  THE HAMMING DISTANCE IS : " << hdis << endl;
			}

			read1.clear();
			read1.seekg(0, ios::beg);   //data file back from start
		}

		inputFile.close();			
	}
	else
	{
		cout << "------->  You've given a wrong input. " << endl;
	}

	//hammingList->PrintData();

	delete hammingList;
	read1.close();
	cin.get();

	return 0;
}