#include <sstream>
#include <time.h>
#include <cstdlib>
#include <time.h>
#include "ListData.h"
#include "Hash.h"
#include "MathFunctions.h"

using namespace std;


template <typename T>
void ListData<T>::initEuclideanList(ifstream& inputFile, ifstream& queryFile, int k, int L, ofstream& outputFile, int* dataLength) {
		string genericStr;
		string itemNos;
		string genericQuery;
		string pointStr;
		string metric;
		string GARBAGE;
		string metric_space; //already declared, just for compilation purposes
		double edis;
		//double* lshENN;
		Node<double*>* lshENN;
		Node<double*>* realENN;
		double*** v;
		double minOutsideDistance;
		int itemNumber = 0;
		int** r_k;
		double y_1, y_2, r, ID, phi;
		double minEBruteDistance= 99999;
		int h;
		double** t;
		int w = 4;
		//int L = 5;	//already declared, just for compilation purposes
		int inputFileSize = 0;
		double Radius = 0;
		int queryCounter = 1;
		//int itemNo = 0;
		clock_t begin, begin_brute, end_ebrute, begin_euclidList;
		clock_t begin_lshe_query, end_lshe_query;
		clock_t end_euclidList, begin_lsh_hashing, end_lsh_hashing;
		double elapsed_secs_lshe, elapsed_secs_euclidList, elapsed_secs_hashing, end_h_creation;
		double elapsed_secs_ebrute, elapsed_secs_query;
		//this = new ListData<double*>();     //creation of the list
		//bool turn;	//already declared, just for compilation purposes

		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::cout.precision(20);


		//inputFile.open("DataEuclidean.csv");						//TO BE DELETED
 		//queryFile.open("QueryEuclidean.csv");

   		/*if (queryFile == NULL)
   		{
   			cout << "------->  You've given a wrong input file. " << endl;
   			exit(1);
   		}
   		else
   		{
   			cout << "File : QueryEuclidean.csv opened successfully!" << endl << endl;
   			//turn = true;
   		}*/	
		inputFile.clear();      //restart
		inputFile.seekg(0, ios::beg);   //data file back from start
   		begin = clock();
   		inputFile >> metric_space;    //read "@metric space"      //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric_space;    //read "euclidean"
   		inputFile >> metric;	//read etc, "@metric"       //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric;	//read euclidean
   		inputFile >> itemNos;	//read itemno
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

        end_h_creation = clock();


   		if (k > *dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = *dataLength;
   		}

        begin_euclidList = clock();
   		//cout << "The size of each hamming code is: " << *dataLength <<endl;
   		inputFile.clear();      //restart
   		inputFile.seekg(0, ios::beg);   //data file back from start

   		inputFile >> metric_space;    //read "@metric space"      //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric_space;    //read "euclidean"
   		inputFile >> metric;	//read etc, "@metric"       //NOT NEEDED IF PARAMETERS WORKING
   		inputFile >> metric;	//read euclidean
		int index = 0;
		ListData<double*>* euclidList = new ListData<double*>(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		double* point;		//new point;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//inputFile >> itemNos;	//read itemno
		getline(inputFile, genericStr);
		itemNumber = 0;
   		while(getline(inputFile, genericStr)) {					//for every point
                //cout << "genericStr:" << genericStr << endl;
        //cin>> GARBAGE;
            itemNumber += 1;
   			index = 0;
	   		stringstream linestream(genericStr);
	   		getline(linestream, itemNos, '\t');        //ITEMNO
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){			//calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			//cout << "pointstr:" <<point[index] << " index: " << index <<endl;
	   			index++;
	   			//cin >> metric_space;
	   		}
	   		euclidList->Insert(point, itemNumber, itemNos);
	   		inputFileSize++;
	   		//inputFile >> itemNos;	//read itemno
   		}
   		//cout << "TA KENIS EW?" << endl;
   		//euclidList->PrintData();
   		//cin >> GARBAGE;
   		end_euclidList = clock();
   		elapsed_secs_euclidList = (double) (end_euclidList - begin_euclidList) / CLOCKS_PER_SEC;


   		begin_lsh_hashing = clock();
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
				hashTableList[o].Insert(phi, nodePtr->getKey(), ID, nodePtr->getItemNo(), nodePtr->getItemName());
   			}

   			//cout << "not key : " << nodePtr->getKey() << endl;
   			nodePtr = nodePtr->getNext();
   			//cout << "changin node... :" << endl;
   			//cin >> GARBAGE;
   		}
   		//hashTableList[0].printHash();
   		//cin >>GARBAGE;
   		end_lsh_hashing = clock();
   		elapsed_secs_hashing = (double) (end_lsh_hashing - begin_lsh_hashing) / CLOCKS_PER_SEC;


   		//TO-DO |||||||||||||||||||||||||  TIME TO DUEL MOTHAFACKA |||||||||||||||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   		//double* arr1 = new double[*dataLength];
   		TrickList<double*>* trickList = new TrickList<double*>();		//the first item of the TrickList is the info head
   		//cout << "edw ei,ai " << endl;
   		queryFile >> genericQuery;	//@Radius
   		queryFile >> Radius;	//radius_value
   		outputFile << "Radius : " << Radius << endl;
   		//cout <<"reached" <<endl;
   		//queryFile >> itemNos;	//read itemno
   		//cout << itemNos <<endl;
   		getline(queryFile, genericStr);
   		while(getline(queryFile, genericStr)) {					//for every point
   			index = 0;
	   		//queryFile >> genericStr;	//read itemno
	   		begin_lshe_query = clock();
	   		//getline(queryFile, genericStr);
	   		//cout << "genericStr:" << genericStr << endl;
	   		stringstream linestream(genericStr);
	   		getline(linestream, itemNos, '\t');        //get item no
	   		outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << itemNos <<" $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){			//calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			//cout << "pointstr: " <<point[index] << " index: " << index <<endl;
	   			index++;
	   			//cin >> GARBAGE;
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
				hashTableList[o].getHashTable()[(int)phi].InsertTrick((int)ID, trickList, L);
				//cout << "THE ENEUFEDNIFUN :" << endl;
				//cin >> GARBAGE;

   			}
   			if (Radius > 0) 
            {
   				outputFile << "R NNs : " << endl;
   			}
   			//cout << "daaaaaaaaamn" <<endl;
   			//cout << "starign ti compuutr the min disrsance " << endl;
   			lshENN = trickList->NNTrickList(point, *dataLength, outputFile, Radius, &minOutsideDistance);
   			//cout << "daaaaaaaaamn" <<endl;
   			end_lshe_query = clock();
   			elapsed_secs_query = (double) (end_lshe_query - begin_lshe_query) / CLOCKS_PER_SEC;



   			//************************ ENDED LSH EUCLIDEAN  ************************

   			// ************************ REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE ************************
   			Node<double*>* newNode = euclidList->getNode();
   			/*if (newNode == NULL) {
                cout << "DAAAAAAAAAAMN" <<endl;
   			}*/
   			begin_brute = clock();
   			while(newNode != NULL)
   			{
   				edis = TrickList<T>::Distance(newNode->getKey(), point, *dataLength);
   				//cout << "-------> EUCLIDEAN DISTANCE :  : " << edis <<endl;
   				//cout << "------->  RADIUS :  : " << Radius <<endl;

   				if ((edis < minEBruteDistance) && (edis != 0))
   				{
   				    //cout << "------->  IN RADIUS : " << newNode->getKey() << endl;
   					minEBruteDistance = edis;
   					realENN = newNode;
   				}
   				newNode = newNode->getNext();

   				if (newNode == NULL)
   				{
   					break;
   				}
   			}

   			end_ebrute = clock();

   			//cout << "Time query : " << elapsed_secs_query << endl;
   			//cout << "Time hashing : " << elapsed_secs_hashing << endl;
   			//cout << "Time euclidList : " << elapsed_secs_euclidList << endl;


   			elapsed_secs_lshe = double (elapsed_secs_query + elapsed_secs_hashing + elapsed_secs_euclidList + end_h_creation - begin) / CLOCKS_PER_SEC;
   			elapsed_secs_ebrute = double (end_ebrute - begin_brute + elapsed_secs_euclidList + end_h_creation - begin ) / CLOCKS_PER_SEC;

   			if (lshENN != NULL){
   				outputFile << "------->  LSH NN Euclidean :  " << lshENN->getItemName() << endl;
   				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ item + mindistance
   				outputFile << "------->  The lsh nearest neighbour for query " << queryCounter << " is within distance  : " << minOutsideDistance << endl;
   				outputFile << "------->  Time taken LSH Euclidean : " << elapsed_secs_lshe << endl << endl;
   			}
   			else {
   				outputFile << "------->  LSH NN Euclidean could not return results" << endl;
   				outputFile << "------->  Time taken LSH Euclidean : " << elapsed_secs_lshe << endl << endl;
   			}

   			outputFile << "------->  Real NN Euclidean :  " << realENN->getItemName() << endl;
   			outputFile << "------->  The real nearest neighbour for query " << queryCounter << " is within distance  : " << minEBruteDistance << endl;
   			outputFile << "------->  Time taken brute force Euclidean : " << elapsed_secs_ebrute << endl << endl;

   			outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER " << queryCounter << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

			minEBruteDistance = 9999;			//resetting the minimum distance
			//minLSHDistance = 9999;
	    	//realENN = 0;
	    	//lshENN = 0;
	    	realENN = NULL;
	    	lshENN = NULL;
	    	elapsed_secs_lshe = 0.0f;
	    	elapsed_secs_ebrute = 0.0f;
	    	//turn = false;
	    	++queryCounter;
	    	trickList->setNext(NULL);
	    	//queryFile >> itemNos;	//read itemno
   		}





   		//cout << "IN the manager" << endl;










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
