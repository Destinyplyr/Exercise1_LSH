#include "ListDatahamming.h"

ListDataHamming::initEuclideanList() {
    this = new ListDataHamming<int*>();     //creation of the list


 		queryFile.open("testHamming.txt");

   		if (queryFile == NULL)
   		{
   			cout << "------->  You've given a wrong input file. " << endl;
   			exit(1);
   		}
   		else
   		{
   			cout << "File : testHamming.txt opened successfully!" << endl << endl;
   			turn = true;
   		}


   		inputFile >> genericStr;    //read "@metric space"      //NOT NEEDED
   		inputFile >> genericStr;	//read etc, "hamming"       //NOT NEEDED
   		inputFile >> genericStr;	//read itemno
   		inputFile >> genericStr;	//read data size

   		dataLength = genericStr.length();

   		if (k > dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = dataLength;
   		}

   		cout << "The size of each hamming code is: " << dataLength <<endl;
   		inputFile.clear();      //restart
   		inputFile.seekg(0, ios::beg);   //data file back from start

   		inputFile >> genericStr;    //read "@metric space"
   		inputFile >> genericStr;	//read etc, "hamming"

   		//HASTABLE CREATION
   		Hash<string>* hashTableList = new Hash<string>[L];
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
	   		    //int r = Ì + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want k numbers from 0 to size of Hamming1-1
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


}
