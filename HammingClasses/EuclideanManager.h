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
	string genericQuery;
	string exitCode;

	TrickList<int>* trickList = new TrickList<int>();

	queryEuclidean >> genericQuery;	//@Radius
	queryEuclidean >> Radius;	//radius_value
	

	while (!queryEuclidean.eof())
	{
		queryEuclidean >> genericQuery; //item

		while((genericQuery.at(0) != 'i') && (!queryEuclidean.eof()))
		{
			queryEuclidean >> genericQuery; //data we want to store
			if (queryEuclidean.eof())
			{
				break;
			}

			//TAKE THE APPROPTIATE INFO, 


			Node<int>* listIntegerNode = new Node<int>();

			//INITIALIZE THE HELPER LIST 
			/*for (int i = 0; i < L; ++i)
			{

			}*/

			//AND COMPUTE THE DISTANCE
			cout << genericQuery << endl; 


		}
	}



	cout << "IN the manager" << endl;
}