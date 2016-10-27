#include <cmath>
#include <sstream>
#include "ListData.h"
#include "MathFunctions.h"

using namespace std;


template <typename T>
void ListData<T>::initEuclideanList(ifstream& inputFile, ifstream& queryFile, int k, int* dataLength) {
		string genericStr;
		string pointStr;
		string metric;
		string metric_space; //already declared, just for compilation purposes
		double*** v;
		double y_1, y_2, r, t;
		int w = 4;
		int L = 5;	//already declared, just for compilation purposes
		int inputFileSize = 0;
		//this = new ListData<double*>();     //creation of the list
		bool turn;	//already declared, just for compilation purposes

		inputFile.open("DataEuclidean.csv");						//TO BE DELETED
 		queryFile.open("QueryEuclidean.csv");

   		if (queryFile == NULL)
   		{
   			cout << "------->  You've given a wrong input file. " << endl;
   			exit(1);
   		}
   		else
   		{
   			cout << "File : QueryEuclidean.csv opened successfully!" << endl << endl;
   			turn = true;
   		}


   		inputFile >> metric_space;    //read "@metric space"      //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric_space;    //read "euclidean"
   		inputFile >> metric;	//read etc, "@metric"       //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric;	//read euclidean
   		inputFile >> genericStr;	//read itemno
   		cout << "BEFORE MAIN GELINE : "  <<genericStr<< endl;
   		cin >> genericStr;
   		getline(inputFile, genericStr);
   		cout << "AFYER MAIN GELINE : "  <<genericStr<< endl;
   		stringstream linestream(genericStr);
   		getline(linestream, pointStr, '\t');
   		while (getline(linestream, pointStr, '\t')) {			//calculate dimension of points
   			cout << "IN DO BEFORE GELINE : "  << endl;
   			cout << "THE PIN : " << pointStr << endl;	
   			(*dataLength)++;
   		}
   		//inputFile >> genericStr;	//read data size

   		cout << "The size of each euclidean point is: " << *dataLength <<endl;
   		cin >> genericStr;
   		inputFile.clear();      //restart
   		inputFile.seekg(0, ios::beg);   //data file back from start

   		v = new double**[L];
   		for (int o = 0; o < L; ++o)
   		{
   			v[o] = new double*[k];
   			for (int j = 0; j < k; j++) {
   				v[o][j] = new double[*dataLength];
   			}
   		}
   		for (int o = 0; o < L; o++) {		//for every hash table
	   		for (int j = 0; j < k; j++) {	//for every h
		   		for (int i = 0; i < *dataLength; i++) {		//[-1,1]
		   			//int r = M + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want v numbers from -1 to 1
		   			r = (rand() / RAND_MAX + 1.0)*(1+1);		//radius smaller than 1
		   			y_1 = -1 + ((double)rand() / (double)RAND_MAX + 1.0)*(1 +1 +1);
		   			y_2 = sqrt(r - (y_1*y_1));			// r = y_1^2 + y_2^2
		   			v[o][j][i] = y_1 * sqrt((-2 * log(r))/r);//every coordinate follows a N(0,1) distribution
		   			cout << "voji = " <<v[o][j][i] <<endl;
		   			//build t
		   			//build r
		   		}
	   		}
   		}


   		t = 0 + (rand() / RAND_MAX + 1.0)*(w +1);	//[0,w]


   		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		if (k > *dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = *dataLength;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		}

   		cout << "The size of each hamming code is: " << *dataLength <<endl;
   		inputFile.clear();      //restart
   		inputFile.seekg(0, ios::beg);   //data file back from start

   		inputFile >> metric_space;    //read "@metric space"      //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric_space;    //read "euclidean"
   		inputFile >> metric;	//read etc, "@metric"       //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric;	//read euclidean
		int index = 0;
		ListData<double*>* euclidList = new ListData<double*>(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		double* point = new double[*dataLength];		//new point;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		Hash<int*>* hashTableList = new Hash<int*>[L];
   		while(!inputFile.eof()) {					//for every point
   			index = 0;
	   		inputFile >> genericStr;	//read itemno
	   		getline(inputFile, genericStr);
	   		stringstream linestream(genericStr);
	   		do {			//calculate dimension of points
	   			getline(linestream, pointStr, '\t');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			index++;
	   		}while(!pointStr.empty());
	   		euclidList->Insert(point);
	   		inputFileSize++;
   		}
   		long long  tableSize = inputFileSize / 2;
   		long long M = pow(2, 32) - 5;
   		Node<double*>* nodePtr = euclidList->getNode(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		while (nodePtr != NULL) {				//for every node in the euclidList
    		for (int i = 0; i < L; ++i){		//for every hashtable
			
   			}
   			nodePtr = nodePtr->getNext();
   		}


   		//TO-DO |||||||||||||||||||||||||  ABOUT TO CHANGE |||||||||||||||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

   		/*
   		//HASTABLE CREATION
   		//Hash<int*>* hashTableList = new Hash<int*>[L];
   		int** miniHashIndexList = new int*[L];			//miniHashIndexList is used to store the miniHashIndex for every hashTable
	   	int currentIndex = 0;
   		int hashResult = 0;
   		for (int l = 0; l < L; l++)
   		{		//every hash table
	   		hashTableList[l].initHash(k, metric_space);
	   		int* miniHashIndex = new int[k];		//don't delete it until end of program

	   		//which mini-hashing functions should I choose?
	   		for (int i=0; i < k; i++)
	   		{
	   		    //int r = M + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want k numbers from 0 to size of Hamming1-1
	   		    miniHashIndex[i] = (int)(((double)rand() / (double)RAND_MAX)*((double)dataLength-1));
	   		    //cout << "miniHashIndex[" << i << "]: " << miniHashIndex[i] <<endl;
	   		}


	   		miniHashIndexList[l] = miniHashIndex;		//add it for use on queryFile


	   		//cin >> genericStr;      //to wait
	   		//LSH works this way for Hamming strings
	   		//we pick randomly k bits of the Hamming bitstring (k mini-hash h functions) and use the concatenation of those to find the bucket
			while (!inputFile.eof())
			{
				//cout << "waduuuuuuuuuuuuuuup" <<endl;
	   			if (turn)
	   			{
	   				inputFile >> genericStr;	//item etc
	   		   		inputFile >> genericStr;	//data we want to store
	   			}
	   			else
	   			{
					inputFile >> genericStr;	//@metric_spaces
			   		inputFile >> genericStr;	//hamming
					inputFile >> genericStr;	//item etc
			   		inputFile >> genericStr;	//data we want to store
	   			}
			    hammingList->Insert(genericStr);    //add on item list
			    nodeHammingPtr = hammingList->ReturnHead();     //return the head of the list
			    for (int i=0; i < k; i++) {
			        currentIndex = miniHashIndex[i];        //current index regarding the Hamming string;
			        hashResult += pow (2, i) * (genericStr[currentIndex] - '0');    //creates the binary as an int
			        //cout << "The (unfinished) hash result: " << hashResult << "("<< pow(2, i)<< "-" << genericStr[currentIndex] - '0' <<")" << endl;
			        //cin >>genericStr;
			    }

			    hashTableList[l].Insert(hashResult, genericStr);









			    //int hdis = hammingList->Distance(myString, theCode);
			    //cout << "------->  THE HAMMING DISTANCE IS : " << hdis << endl;
			    hashResult = 0;
			}
			int test;
			//hashTableList[l].printHash();
			//cin >> test;
			inputFile.clear();
			inputFile.seekg(0, ios::beg);   //data file back from start
	   		inputFile >> genericStr;	//item etc
	   		inputFile >> genericStr;	//data we want to store

		*/
}
