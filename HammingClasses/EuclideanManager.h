#include <iostream>
#include <cstdlib>
#include <math.h>
#include "ListData.h"
#include "TrickFunctions.h"

using namespace std;

void EuclideanManagement()
{
	ifstream queryEuclidean;
	queryEuclidean.open("QueryEuclidean.csv");
	int Radius = 0;
	int gFunct = 22;
	int L = 5;
	int datalength = 102;
	string genericQuery;
	string exitCode;
	double* arr1 = new double[datalength]; 
	int c = 0;
	Node<int>* listIntegerNode = new Node<int>();
	TrickList<int>* trickList = new TrickList<int>();

	queryEuclidean >> genericQuery;	//@Radius
	queryEuclidean >> Radius;	//radius_value
	

	while (!queryEuclidean.eof())
	{
		queryEuclidean >> genericQuery; //item

		while((genericQuery.at(0) != 'i') && (!queryEuclidean.eof()))
		{
			queryEuclidean >> genericQuery; //data we want to store
				
			arr1[c] = strtod(genericQuery.c_str(), NULL);
			++c;
			if (c > datalength)
			{
				break;
			}

			if (queryEuclidean.eof())
			{
				break;
			}
		}


		//INITIALIZE THE HELPER LIST 
		for (int i = 0; i < L; ++i)
		{
			
		}

		//AND COMPUTE THE DISTANCE
		cout << genericQuery << endl; 
	}



	cout << "IN the manager" << endl;
}