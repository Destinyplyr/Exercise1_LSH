#include "mainSample.h"

int main(int argc, char **argv)
{
	int k = 4;
	int L = 5;
	int Radius = 0;
	int dataLength;     //used for hamming size, or number of vector attributes
	int choice;
	int hdis;
	int lshdis;
	int queryCounter = 1;
	int minBruteDistance = 9999;
	int minLSHDistance = 9999;
	double elapsed_secs_lsh, elapsed_secs_brute;
	ifstream inputFile;
	ifstream queryFile;
	ofstream outputFile;
	string metric_space;
	string genericStr;
	string queryCode;
	string realNN;
	string lshNN;
	string myString;
	bool turn = false;
	clock_t begin, begin_lsh, end_brute, end_lsh;
	Node<string>* minimumNode;
	Node<string>* listNode; //=  new Node<string>();

	//Sample arrays for euclidean tests
	/*double arr1[3] = {6, 4, 4}; 
	double arr2[3] = {16, 5, 5}; */

	cout << "********************* Hamming space LSH testing ********************* " << endl << endl;

	srand (time(NULL));

	if (argc > 1) {
		if (argc % 2 == 0) {
			cout << "Missing the correct number of parameters" << endl;
			cout << "Suggested use: $./lsh –d <input file> –q <query file> –k <int> -L <int> -ο <output file>" << endl;
			return -1;
		}
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-d") == 0) {
				inputFile.open(argv[i+1]);		//input file comes next on argv
				if (inputFile == NULL)
				{
					cout << "You've given a wrong input file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
				}
				inputFile >> metric_space;  //read "@metric space"
				inputFile >> metric_space;	//read etc, "hamming"

				i++;
			}
			else if (strcmp(argv[i], "-q") == 0) {
				queryFile.open(argv[i+1]);		//query file comes next on argv
				if (queryFile == NULL)
				{
					cout << "You've given a wrong query file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
				}
				queryFile >> genericStr;  //read "@metric space"
				queryFile >> genericStr;	//read etc, "hamming"
				Radius = atoi(genericStr.c_str());
				//Radius = stoi(genericStr);

				i++;
			}
			else if (strcmp(argv[i], "-k") == 0) {
				//k = stoi(argv[i+1]);
				k = atoi(argv[i+1]);
				i++;
			}
			else if (strcmp(argv[i], "-L") == 0) {
				//L = stoi(argv[i+1]);
				L = atoi(argv[i+1]);
				i++;
			}
			else if (strcmp(argv[i], "-o") == 0) {
				outputFile.open(argv[i+1]);		//output file comes next on argv
				if (outputFile == NULL)
				{
					cout << "You've given a wrong output file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
				}

				i++;
			}
			else {
				cout << "You've given wrong input" <<endl;
				return -1;
			}
		}
	}

	//  CASE EUCLIDEAN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX

    ListData<double>* euclideanList;
    //euclideanList->initEuclideanList();


    EuclideanManagement();


    exit(1);

    //#######################################################################################################################

    // double result =  euclideanList->Distance(arr1, arr2, 2);
    // cout << "DISTANCE EUCLIDES iS : " << result << endl;

    // exit(1);

	//if (case hamming)
	//CASE: HAMMING
	cout << " 1 : Enter a 64-bit code. " << endl;
    cout << " 2 : Read Hamming input file." << endl << endl;
    cin >> choice;

    inputFile.open("DataHamming.csv");

    ListData<string>* hammingList = new ListData<string>();
    Node<string>* nodeHammingPtr = NULL;        //haming node pointer
    //GIVE A CODE-------------------------------------------------------------------------------------------------------------
    if (choice == 1)
   	{
   		string queryCode;
   		cout << "------->  Give a 64 bit queryCode : " << endl << endl;
   		cin >> queryCode;

   		begin = clock();

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
	   		    //int r = Μ + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want k numbers from 0 to size of Hamming1-1
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


		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

   		while (!inputFile.eof())
   		{
   			inputFile >> genericStr;	//item
   			inputFile >> genericStr;	//data we want to compare
			Node<string>** listBucketTable = new Node<string>*[L];

   			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

			begin_lsh = clock();

			for (int l =0; l < L; l++) 
			{		//for every hash table
				cout << "**************************************************************************************" << endl;
	   			cout << "------->  QUERY CODE : " << queryCode << endl << endl;
				
		   		for (int i=0; i < k; i++) 
		   		{
				   		currentIndex = miniHashIndexList[l][i];        //current index regarding the Hamming string - using the miniHash that was used before
				        hashResult += pow (2, i) * (queryCode[currentIndex] - '0');    //creates the binary as an int
				        cout << queryCode[currentIndex] - '0';
				        //cout << "The (unfinished) hash result: " << hashResult << "("<< pow(2, i)<< "-" << genericStr[currentIndex] - '0' <<")" << endl;
				        //cin >>genericStr;
		   		}
	   			cout << endl;

			    cout << "------->  HASH RESULT IN QUERY : " << hashResult <<endl;
			    hashResult = 0;
			    listNode = hashTableList[l].getHashTable()->getBucket();		   		  	
			    listBucketTable[l] = listNode;
				//cout << " IN LIST NODE : " << listNode->getKey() << endl;	   		    
			    cout << endl << endl << endl;
			}

			for (int i = 0; i < L; ++i) 
			{
				listNode = listBucketTable[i];		//we take the bucket
				while (listNode != NULL)
				{
					lshdis = hammingList->Distance(queryCode, listNode->getKey());
					if ((lshdis < minLSHDistance) && (lshdis != 0)) 
					{
						minLSHDistance = lshdis;
						minimumNode = listNode;
					}
					listNode = listNode->getNext();
				}
			}
			
			lshNN = minimumNode->getKey();
			end_lsh = clock();


			//ENDED LSH

			//REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE 
		
			Node<string>* newNode = hammingList->getNode();
   			
			while(newNode != NULL) 
			{
				hdis = hammingList->Distance(queryCode, newNode->getKey());
				//cout << "------->  HAMMING DISTANCE :  : " << hdis <<endl;
				//cout << "------->  RADIUS :  : " << Radius <<endl;

				if ((hdis < Radius ) && (hdis != 0))
				{
					cout << "------->  IN RADIUS : " << newNode->getKey() << endl;
				}

				if ((hdis < minBruteDistance) && (hdis != 0))
				{
					minBruteDistance = hdis;
					realNN = newNode->getKey();
				}
				newNode = newNode->getNext();
			}
		    
		   	end_brute = clock();
		   	elapsed_secs_lsh = double (end_lsh - begin) / CLOCKS_PER_SEC;
		   	elapsed_secs_brute = double (end_brute - begin - (end_lsh - begin_lsh)) / CLOCKS_PER_SEC;
		   	//double elapsed_secs_ = double(end - begin) / CLOCKS_PER_SEC;		//alakse dhlwsh kai balthn panw



		    cout << "------->  LSH NN :  " << lshNN << endl;
		    cout << "------->  The lsh nearest neighbour for " << queryCode << " is within distance  : " << minLSHDistance << endl;    
		    cout << "------->  Time taken LSH: " << elapsed_secs_lsh << endl << endl;	
	   		

		    cout << "------->  Real NN :  " << realNN << endl;
		    cout << "------->  The real nearest neighbour for " << queryCode << " is within distance  : " << minBruteDistance << endl;
		    cout << "------->  Time taken brute force: " << elapsed_secs_brute << endl << endl;

		    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

			//inputFile.clear();
		    //inputFile.seekg(0, ios::beg);   //data file back from start
			minBruteDistance = 9999;			//resetting the minimum distance
			minLSHDistance = 9999;
	    	realNN.clear();
	    	lshNN.clear();
	    	turn = false;
	    }
 
   	}
   	//READ FROM INPUT FILE-------------------------------------------------------------------------------------------------------------
   	else if (choice == 2)
   	{
   		begin = clock();
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
	   		    //int r = Μ + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want k numbers from 0 to size of Hamming1-1
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
		//cin >> queryCode;

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		queryFile >> queryCode;	//@Radius
		queryFile >> Radius;	//radius_value

		Node<string>** listBucketTable = new Node<string>*[L];

   		while (!queryFile.eof())
   		{
   			queryFile >> queryCode;	//item
   			queryFile >> queryCode;	//data we want to compare

   			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

   			begin_lsh = clock();

   			for (int l =0; l < L; l++)
   			{		//for every hash table
	   			cout << "**************************************************************************************" << endl;
	   		    cout << "------->  QUERY CODE : " << queryCode << endl << endl;

	   		    for (int i=0; i < k; i++)
	   		    {
	   		        currentIndex = miniHashIndexList[l][i];        //current index regarding the Hamming string - using the miniHash that was used before
	   		        hashResult += pow (2, i) * (queryCode[currentIndex] - '0');    //creates the binary as an int
	   		        cout << queryCode[currentIndex] - '0';
	   		        //cout << "The (unfinished) hash result: " << hashResult << "("<< pow(2, i)<< "-" << genericStr[currentIndex] - '0' <<")" << endl;
	   		        //cin >>genericStr;
	   		    }
	   		    cout << endl;

	   		    cout << "------->  HASH RESULT IN QUERY : " << hashResult <<endl;
	   		    hashResult = 0;
	   		    listNode = hashTableList[l].getHashTable()->getBucket();
	   		    listBucketTable[l] = listNode;
				//cout << " IN LIST NODE : " << listNode->getKey() << endl;
	   		    cout << endl << endl << endl;
   			}

   			for (int i = 0; i < L; ++i)
   			{
   				listNode = listBucketTable[i];		//we take the bucket
   				while (listNode != NULL)
   				{
   					lshdis = hammingList->Distance(queryCode, listNode->getKey());
   					if ((lshdis < minLSHDistance) && (lshdis != 0))
   					{
   						minLSHDistance = lshdis;
   						minimumNode = listNode;
   					}
   					listNode = listNode->getNext();
   				}
   			}
   			lshNN = minimumNode->getKey();
   			end_lsh = clock();

   			//ENDED LSH

   			//REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE

   			Node<string>* newNode = hammingList->getNode();

   			while(newNode != NULL)
   			{
   				hdis = hammingList->Distance(queryCode, newNode->getKey());
   				//cout << "------->  HAMMING DISTANCE :  : " << hdis <<endl;
   				//cout << "------->  RADIUS :  : " << Radius <<endl;

   				if ((hdis < Radius ) && (hdis != 0))
   				{
   					cout << "------->  IN RADIUS : " << newNode->getKey() << endl;
   				}

   				if ((hdis < minBruteDistance) && (hdis != 0))
   				{
   					minBruteDistance = hdis;
   					realNN = newNode->getKey();
   				}
   				newNode = newNode->getNext();
   			}

		   	end_brute = clock();
		   	elapsed_secs_lsh = double (end_lsh - begin) / CLOCKS_PER_SEC;
		   	elapsed_secs_brute = double (end_brute - begin - (end_lsh - begin_lsh)) / CLOCKS_PER_SEC;
		   	//double elapsed_secs_ = double(end - begin) / CLOCKS_PER_SEC;		//alakse dhlwsh kai balthn panw



		    cout << "------->  LSH NN :  " << lshNN << endl;
		    cout << "------->  The lsh nearest neighbour for " << queryCode << " is within distance  : " << minLSHDistance << endl;
		    cout << "------->  Time taken LSH: " << elapsed_secs_lsh << endl << endl;

		    cout << "------->  Real NN :  " << realNN << endl;
		    cout << "------->  The real nearest neighbour for " << queryCode << " is within distance  : " << minBruteDistance << endl;
		    cout << "------->  Time taken brute force: " << elapsed_secs_brute << endl << endl;

		    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER " << queryCounter << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

    		//inputFile.clear();
    	    //inputFile.seekg(0, ios::beg);   //data file back from start
    		minBruteDistance = 9999;			//resetting the minimum distance
    		minLSHDistance = 9999;
        	realNN.clear();
        	lshNN.clear();
        	turn = false;
        	++queryCounter;
   		}

   		//hammingList->PrintData();
   	}
   	else
   	{
   		cout << "------->  You've given a wrong input. " << endl;
   	}



   	delete hammingList;
   	inputFile.close();
   	queryFile.close();
   	cin.get();

	return 0;
}
