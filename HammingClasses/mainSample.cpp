#include "mainSample.h"

int main(int argc, char **argv)
{
	int k = 4;
	int L = 5;
	int Radius = 0;
	int dataLength;     //used for hamming size, or number of vector attributes
	int choice;
	int hdis;
	int minDistance = 9999;
	ifstream inputFile;
	ifstream queryFile;
	ofstream outputFile;
	string metric_space;
	string genericStr;
	string queryCode;
	string realNN;
	string myString;
	bool turn = false;
	
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
				queryFile.open(argv[i+1]);		//output file comes next on argv
				if (queryFile == NULL)
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
	//CASE: HAMMING
	cout << " 1 : Enter a 64-bit code. " << endl; 
    cout << " 2 : Read Hamming input file." << endl << endl;
    cin >> choice;

    inputFile.open("DataHamming.csv");

    ListDataHamming<string>* hammingList = new ListDataHamming<string>();
    Node<string>* nodeHammingPtr = NULL;        //haming node pointer

    //GIVE A CODE
    if (choice == 1)
   	{
   		/*string code;
   		cout << "------->  Give a 64 bit code : " << endl << endl;
   		cin >> code;
	   	if (code.size() != 64)
	   	{
	   		cout << "------->  You've given a wrong input. " << endl;
	   		exit(0);
	   	}
	   	inputFile >> myString;  //read "@metric space"
	   	inputFile >> myString;	//read etc, "hamming"

	   	clock_t clockStart = clock();
	   	while (!inputFile.eof())
	   	{
	   		inputFile >> myString;	//item etc
	   		inputFile >> myString;	//data we want to store
	   		hammingList->Insert(myString);
	   		hdis = hammingList->Distance(myString, code);
	   		if ((hdis < minDistance) && (hdis != 0))
	   		{
	   			minDistance = hdis;
	   			realNN = myString;
	   		}
	   		//cout << endl;
	   		//cout << "------->  The hamming distance is : " << hdis << endl;
	   	}

	   	cout << "------->  Real NN :  " << realNN << endl;
	   	cout << "------->  The real nearest neighbour for " << code << " is within distance  : " << minDistance << endl;
	   	cout << "------->  Time taken: " << (double)(clock() - clockStart)/CLOCKS_PER_SEC << endl;*/
   	}
   	//READ FROM INPUT FILE
   	else if (choice == 2)
   	{
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

   		inputFile >> genericStr;    //read "@metric space"
   		inputFile >> genericStr;	//read etc, "hamming"

   		//HASTABLE CREATION
   		Hash<string>* hashTableList = new Hash<string>[L];
   		hashTableList->Hash::initHash(k, metric_space);
   		int* miniHashIndex = new int[k];
   		int currentIndex = 0;
   		int hashResult = 0;

   		//which mini-hashing functions should I choose?
   		for (int i=0; i < k; i++) 
   		{
   		    //int r = Μ + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want k numbers from 1 to size of Hamming
   		    miniHashIndex[i] = (int)(1.0+ ((double)rand() / (double)RAND_MAX +1.0)*((double)k));
   		    cout << "miniHashIndex[" << i << "]: " << miniHashIndex[i] <<endl;

   		}
   		cin >> genericStr;      //to wait
   		//LSH works this way for Hamming strings
   		//we pick randomly k bits of the Hamming bitstring (k mini-hash h functions) and use the concatenation of those to find the bucket
   		
   		
   		while (!queryFile.eof())
   		{
   			clock_t begin = clock();
   			while (!inputFile.eof())
   			{
   				cout << "**************************************************************************************" << endl;
	   			if (turn)
	   			{
	   				inputFile >> genericStr;	//item etc
	   		   		inputFile >> genericStr;	//data we want to store
	   			}
	   			else
	   			{
					inputFile >> genericStr;	//item etc
			   		inputFile >> genericStr;	//data we want to store
					inputFile >> genericStr;	//item etc
			   		inputFile >> genericStr;	//data we want to store
	   			}

	   		   

	   		    queryFile >> queryCode;	//item etc
	   		    queryFile >> queryCode;	//data we want to compare
	   		    queryFile >> queryCode;	//item etc
	   		    queryFile >> queryCode;	//data we want to compare

	   		    cout << "------->  QUERY CODE : " << queryCode << endl;

	   		    //add items once
	   		    if (turn)		
	   		    {
	   		    	hammingList->Insert(genericStr);    //add on item list
	   		    }
	   		   
	   		    //nodeHammingPtr = hammingList->ReturnHead();     //return the head of the list
	   		   	
	   		    cout << "------->  GENERIC ST : " << genericStr << endl; 

				cout << endl;
				
	   		    for (int i=0; i < k; i++) 
	   		    {
	   		        currentIndex = miniHashIndex[i];        //current index regarding the Hamming string;
	   		        hashResult += pow (2, i) * (genericStr[currentIndex] - '0');    //creates the binary as an int
	   		        cout << genericStr[currentIndex] - '0';
	   		        //cout << "The (unfinished) hash result: " << hashResult << "("<< pow(2, i)<< "-" << genericStr[currentIndex] - '0' <<")" << endl;
	   		        //cin >>genericStr;
	   		    }
	   		    
	   		    cout << endl << endl << endl;
	   		    cout << "------->  HASH RESULT : " << hashResult <<endl;
	   		    //cin >>genericStr;


	   		    //REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE 
	   		    hdis = hammingList->Distance(genericStr, queryCode);

	   		    cout << "------->  HAMMING DISTANCE :  : " << hdis <<endl;
	   		    if ((hdis < minDistance) && (hdis != 0))
	   		    {
	   		    	minDistance = hdis;
	   		    	realNN = genericStr;
	   		    }

	   		    clock_t end = clock();
	   		    double elapsed_secs = (double)(end - begin) / CLOCKS_PER_SEC;

	   		    cout << "------->  Real NN :  " << realNN << endl;
	   		    cout << "------->  The real nearest neighbour for " << queryCode << " is within distance  : " << minDistance << endl;
	   		    cout << "------->  Time taken: " << elapsed_secs << endl << endl;

	   		    cout << "**************************************************************************************" << endl << endl << endl << endl;

	   		    hashResult = 0;
	   		    begin = clock();
   			}

			inputFile.clear();
		    inputFile.seekg(0, ios::beg);   //data file back from start
		    minDistance = 9999;			//resetting the minimum distance
		    realNN = " ";
		    turn = false;
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
