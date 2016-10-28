#include <sstream>
#include <time.h>
#include <cstdlib>
#include <time.h>
#include "ListData.h"
#include "Hash.h"
#include "MathFunctions.h"

using namespace std;


template <typename T>
void ListData<T>::initEuclideanList(ifstream& inputFile, ifstream& queryFile, int k, int* dataLength) {
		string genericStr;
		string genericQuery;
		string pointStr;
		string metric;
		string GARBAGE;
		string metric_space; //already declared, just for compilation purposes
		double edis;
		double* lshENN;
		double* realENN;
		double*** v;
		int** r_k;
		double y_1, y_2, r, ID, phi;
		double minEBruteDistance= 99999;
		int h;
		double** t;
		int w = 4;
		int L = 5;	//already declared, just for compilation purposes
		int inputFileSize = 0;
		int Radius = 0;
		int queryCounter = 1;
		clock_t begin, end_ebrute;
		clock_t begin_lshe, end_lshe;
		double elapsed_secs_lshe;
		double elapsed_secs_ebrute;
		//this = new ListData<double*>();     //creation of the list
		//bool turn;	//already declared, just for compilation purposes

		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::cout.precision(20);

		begin = clock();
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
   			//turn = true;
   		}


   		inputFile >> metric_space;    //read "@metric space"      //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric_space;    //read "euclidean"
   		inputFile >> metric;	//read etc, "@metric"       //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric;	//read euclidean
   		inputFile >> genericStr;	//read itemno
   		//cout << "BEFORE MAIN GELINE : "  <<genericStr<< endl;
   		//cin >> genericStr;
   		getline(inputFile, genericStr);
   		//cout << "AFYER MAIN GELINE : "  <<genericStr<< endl;
   		stringstream linestream(genericStr);
   		getline(linestream, pointStr, '\t');
   		while (getline(linestream, pointStr, '\t')) {			//calculate dimension of points
   			//cout << "IN DO BEFORE GELINE : "  << endl;
   			//cout << "THE PIN : " << pointStr << endl;
   			(*dataLength)++;
   		}
   		//inputFile >> genericStr;	//read data size

   		//cout << "The size of each euclidean point is: " << *dataLength << "YEAHHHHHHHHHHHHHHHH132244343dwdwddwdwwwwwwwwd3!!!66666666666666666666666666666666666666664434535wwwww"<< endl;
   		//cin >> genericStr;
   		inputFile.clear();      //restart
   		inputFile.seekg(0, ios::beg);   //data file back from start

   		v = new double**[L];
   		t = new double*[L];
   		r_k = new int*[L];
   		for (int o = 0; o < L; ++o)
   		{
   			v[o] = new double*[k];
   			t[o] = new double[k];
   			r_k[o] = new int[k];
   			for (int j = 0; j < k; j++) {
   				v[o][j] = new double[*dataLength];
   			}
   		}

   		for (int o = 0; o < L; o++) {		//for every hash table
	   		for (int j = 0; j < k; j++) {	//for every h
		   		for (int i = 0; i < *dataLength; i++) {		//[-1,1]
		   			//int r = M + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want v numbers from -1 to 1
		   			r = ((double)rand() / (double)RAND_MAX);		//radius smaller than 1
		   			//cout <<  " R  : " << r << endl;
		   			y_1 = -1 + ((double)rand() / (double)RAND_MAX)*(2);
		   			//cout <<  " y_1  : " << y_1 << endl;
		   			y_2 = sqrt(abs(r - pow(y_1, 2)));			// r = y_1^2 + y_2^2
		   			//cout <<  " y_2  : " << y_2 << endl;
		   			v[o][j][i] = y_1 * sqrt((-2 * log(r))/r);//every coordinate follows a N(0,1) distribution
		   			//cout << "voji = " << v[o][j][i] <<endl;
		   			//cin >> genericStr;
		   			//cin >> genericStr;
		   			//build r
		   		}
		   		t[o][j] = 0 + ((double)rand() / (double)RAND_MAX)*(w);	//[0,w)
		   		r_k[o][j]  = rand();
		   		//cout << "r_k : " << r_k[o][j] << endl;
		   		//cin >> genericStr;
	   		}
   		}


   		if (k > *dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = *dataLength;
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
		double* point;		//new point;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		inputFile >> genericStr;	//read itemno
   		while(getline(inputFile, genericStr)) {					//for every point
   			index = 0;
	   		stringstream linestream(genericStr);
	   		getline(linestream, pointStr, '\t');
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){			//calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			index++;
	   			//cout << "pointstr: " <<point[index] << " index: " << index <<endl;
	   			//cin >> metric_space;
	   		}
	   		euclidList->Insert(point);
	   		inputFileSize++;
	   		inputFile >> genericStr;	//read itemno
   		}
   		//cout << "TA KENIS EW?" << endl;
   		//euclidList->PrintData();
   		long long  tableSize = inputFileSize / 4;
   		//cout << "tableSize :" << tableSize << endl;
   		long long M = pow(2, 32) - 5;
   		//cout << "M :" << M << endl;
   		//cin >> GARBAGE;
   		Hash<double*>* hashTableList = new Hash<double*>[L];
   		for (int o = 0; o < L; ++o)
   		{
   			hashTableList[o].initHash(tableSize, metric);
   		}
   		//cout << "TA KENISdwwdw E?W" << endl;
   		Node<double*>* nodePtr = euclidList->getNode();
   		//cout << "mipws ontws einai lathos edw pera>: " << endl;
   		while (nodePtr != NULL) {				//for every node in the euclidList
    		for (int o = 0; o < L; ++o){		//for every hashtable
				//cout << "mes sthn initHash h stravi " << endl;
				ID = 0;
				for (int j = 0; j < k; ++j)		//for every h
				{
					h =  (int)floor((dot_product(nodePtr->getKey(), v[o][j], *dataLength) + t[o][j]) / w);
					//cout << "h :" << h << endl;
					ID += (r_k[o][j] * h) % M;
					//cout << "ID :" << ID << endl;
					//cin >> GARBAGE;
				}
				phi = abs((long)ID % tableSize);
				//cout << "phi :" << phi << endl;
				//cin >> GARBAGE;
				hashTableList[o].Insert(phi, nodePtr->getKey(), ID);
   			}

   			//cout << "not key : " << nodePtr->getKey() << endl;
   			nodePtr = nodePtr->getNext();
   			//cout << "changin node... :" << endl;
   		}
   		hashTableList[0].printHash();



   		//TO-DO |||||||||||||||||||||||||  TIME TO DUEL MOTHAFACKA |||||||||||||||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		//double* arr1 = new double[*dataLength];
   		TrickList<double*>* trickList = new TrickList<double*>();		//the first item of the TrickList is the info head
   		//cout << "edw ei,ai " << endl;
   		queryFile >> genericQuery;	//@Radius
   		queryFile >> Radius;	//radius_value
   		cout << "Radius : " << Radius << endl;
   		//cout <<"reached" <<endl;
   		queryFile >> genericStr;	//read itemno
   		while(getline(queryFile, genericStr)) {					//for every point
   			index = 0;
	   		//queryFile >> genericStr;	//read itemno
	   		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

	   		begin_lshe = clock();

	   		getline(queryFile, genericStr);
	   		//cout << "genericStr  : " << genericStr << endl;
	   		stringstream linestream(genericStr);
	   		getline(linestream, pointStr, '\t');
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){			//calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			index++;
	   			//cout << "pointstr: " <<point[index] << " index: " << index <<endl;
	   			//cin >> metric_space;
	   		}
	   		for (int o = 0; o < L; ++o){		//for every hashtable
				//hashTableList[o].initHash(tableSize, metric);
				//cout << "mes sthn initHash h stravi " << endl;
				ID = 0;
				for (int j = 0; j < k; ++j)		//for every h
				{
					h =  (int)floor((dot_product(point, v[o][j], *dataLength) + t[o][j]) / w);
					//cout << "h :" << h << endl;
					ID += (r_k[o][j] * h) % M;
					//cout << "ID :" << ID << endl;
					//cin >> GARBAGE;
				}
				phi = abs((long)ID % tableSize);
				//cout << "phi: " << phi <<endl;
				hashTableList[o].getHashTable()[(int)phi].InsertTrick((int)ID, trickList);
				//cout << "THE ENEUFEDNIFUN :" << endl;
				//cin >> GARBAGE;

   			}
   			//cout << "starign ti compuutr the min disrsance " << endl;
   			lshENN = trickList->NNTrickList(point, *dataLength);
   			end_lshe = clock();



   			//************************ ENDED LSH EUCLIDEAN  ************************

   			// ************************ REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE ************************
   			Node<double*>* newNode = euclidList->getNode();

   			while(newNode->getNext() != NULL)
   			{
   				edis = TrickList<T>::Distance(newNode->getKey(), point, *dataLength);
   				//cout << "-------> EUCLIDEAN DISTANCE :  : " << edis <<endl;
   				//cout << "------->  RADIUS :  : " << Radius <<endl;

   				if ((edis < Radius ) && (edis != 0))
   				{
   					cout << "------->  IN RADIUS : " << newNode->getKey() << endl;
   				}

   				if ((edis < minEBruteDistance) && (edis != 0))
   				{
   					minEBruteDistance = edis;
   					realENN = newNode->getKey();
   				}
   				newNode = newNode->getNext();

   				if (newNode == NULL)
   				{
   					break;
   				}
   			}





   			end_ebrute = clock();
   			elapsed_secs_lshe = double (end_lshe - begin) / CLOCKS_PER_SEC;
   			elapsed_secs_ebrute = double (end_ebrute - begin - (end_lshe - begin_lshe)) / CLOCKS_PER_SEC;


   			cout << "------->  LSH NN Euclidean :  " << lshENN[0] << endl;
   			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ item + mindistance
   			//cout << "------->  The lsh nearest neighbour for " << queryCode << " is within distance  : " << minLSHDistance << endl;
   			cout << "------->  Time taken LSH Euclidean : " << elapsed_secs_lshe << endl << endl;

   			cout << "------->  Real NN Euclidean :  " << realENN[0] << endl;
   			//cout << "------->  The real nearest neighbour for " << queryCode << " is within distance  : " << minBruteDistance << endl;
   			cout << "------->  Time taken brute force Euclidean : " << elapsed_secs_ebrute << endl << endl;

   			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER " << queryCounter << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

			minEBruteDistance = 9999;			//resetting the minimum distance
			//minLSHDistance = 9999;
	    	realENN = NULL;
	    	lshENN = NULL;
	    	//turn = false;
	    	++queryCounter;
	    	queryFile >> genericStr;	//read itemno
   		}





   		cout << "IN the manager" << endl;










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
