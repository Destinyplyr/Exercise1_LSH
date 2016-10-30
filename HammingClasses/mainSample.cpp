#include "mainSample.h"

int main(int argc, char **argv)
{
	int k = 4;
	int L = 5;
	double Radius = 0;
	int dataLength = 0;     //used for hamming size, or number of vector attributes
	int itemNo = 0;                //how many items?
	//int choice;
	int hdis;
	int lshdis;
	int queryCounter = 1;
	int minBruteDistance = 9999;
	int minLSHDistance = 9999;
	double elapsed_secs_lsh, elapsed_secs_brute;
	double elapsed_secs_hashing, elapsed_secs_query;
	ifstream inputFile;
	ifstream queryFile;
	ofstream outputFile;
	//outputFile.open("metrics.txt");
	string metric_space;
	string filename;
	string choice;
	string metric;
	string genericStr;
	string itemName;
	string queryCode;
	string myString;
	bool turn = false;
	bool outParameter = false, inParameter = false, queryParameter = false;
	//clock_t begin, begin_lsh_query, begin_brute;
	//clock_t end_lsh_hashing, end_lsh_query, end_brute;
	clock_t begin, begin_brute, end_brute, end_List_creation;
	clock_t begin_lsh_hashing, end_lsh_hashing;
	clock_t begin_cosineList, end_cosineList, begin_lsh_query, end_lsh_query;
	Node<string>* minimumNode;
	Node<string>* listNode; //=  new Node<string>();

	//Sample arrays for euclidean tests
	/*double arr1[3] = {6, 4, 4};
	double arr2[3] = {16, 5, 5}; */


	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(20);
	srand (time(NULL));

	if (argc > 1)
	{
		if (argc % 2 == 0)
		{
			cout << "Missing the correct number of parameters" << endl;
			cout << "Suggested use: $./lsh –d <input file> –q <query file> –k <int> -L <int> -ο <output file>" << endl;
			return -1;
		}
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-d") == 0)
			{
				cout << "H xazomara poy edwses : " << argv[i+1] << endl;
				inputFile.open(argv[i+1]);		//input file comes next on argv
				if (inputFile == NULL)
				{
					cout << "You've given a wrong input file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					inParameter = true;
				}
				inputFile >> metric_space;  //read "@metric space"
				inputFile >> metric_space;	//read etc, "hamming"

				if (strcmp(metric_space.c_str(), "euclidean") == 0)
				{
					inputFile >> metric;  //read "@metric space"
					inputFile >> metric;	//read etc, "hamming"
				}

				i++;
			}
			else if (strcmp(argv[i], "-q") == 0)
			{
				queryFile.open(argv[i+1]);		//query file comes next on argv
				if (queryFile == NULL)
				{
					cout << "You've given a wrong query file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					queryParameter = true;
				}
				//queryFile >> genericStr;  //read "@metric space"
				//queryFile >> genericStr;	//read etc, "hamming"
				//Radius = atoi(genericStr.c_str());
				//Radius = stoi(genericStr);

				i++;
			}
			else if (strcmp(argv[i], "-k") == 0)
			{
				//k = stoi(argv[i+1]);
				k = atoi(argv[i+1]);
				i++;
			}
			else if (strcmp(argv[i], "-L") == 0)
			{
				//L = stoi(argv[i+1]);
				L = atoi(argv[i+1]);
				i++;
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				//outputFile.close();
				outputFile.open(argv[i+1]);		//output file comes next on argv
				if (outputFile == NULL)
				{
					cout << "You've given a wrong output file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					outParameter = true;
				}

				i++;
			}
			else
			{
				cout << "You've given wrong input" <<endl;
				return -1;
			}
		}
	}




	cout << "Welcome to LSH testing simulation " << endl << endl;

	do
	{
		if (inParameter) {
			inParameter = false;
		}
		else {
			cout << "Please give an input file: ";
			cin >> filename;
			inputFile.open(filename.c_str());		//input file comes next on argv
			if (inputFile == NULL)
			{
				cout << "You've given a wrong input file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
			inputFile >> metric_space;  //read "@metric space"
			cout << metric_space << endl;
			inputFile >> metric_space;	//read etc, "hamming"

			if (strcmp(metric_space.c_str(), "euclidean") == 0)
			{
				inputFile >> metric;  //read "@metric space"
				inputFile >> metric;	//read etc, "hamming"
			}

		}
		if (outParameter) {
			outParameter = false;
		}
		else
		{
			cout << "Please give an output file: ";
			cin >> filename;
			outputFile.open(filename.c_str());		//input file comes next on argv
			if (outputFile == NULL)
			{
				cout << "You've given a wrong input file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
		}
		if (queryParameter) 
		{
			queryParameter = false;
		}
		else 
		{
			cout << "Please give a query file: ";
			cin >> filename;
			queryFile.open(filename.c_str());		//query file comes next on argv
			if (queryFile == NULL)
			{
				cout << "You've given a wrong query file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
		}









		//  CASE DISTANCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX

		/*ListData<double*>* DBHList = new ListData<double*>();
		DBHList->initDBHManagement(inputFile, queryFile, k, L, outputFile, &dataLength);

		delete DBHList;
		exit(1);*/


		//  CASE COSINE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX

		/*
		ListData<double*>* cosineList = new ListData<double*>();
		cosineList->initCosineList(inputFile, queryFile, k, L, outputFile, &dataLength);

		 //EuclideanManagement();
		cout << "EINAI OK " << endl;

		 delete cosineList;
		exit(1);
		*/

		//  CASE EUCLIDEAN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX
		/*
		ListData<double*>* euclideanList = new ListData<double*>();
		euclideanList->initEuclideanList(inputFile, queryFile, k, L, outputFile, &dataLength);
		//EuclideanManagement();
		cout << "EINAI OK " << endl;
		delete euclideanList;
		exit(1);*/




		/*if (strcmp(metric.c_str(), "hamming") == 0) {
			tableSize = pow(2, k);
		}*/
		//  CASE EUCLIDEAN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX
		if (strcmp(metric.c_str(), "euclidean") == 0)
		{
			ListData<double*>* euclideanList = new ListData<double*>();
			euclideanList->initEuclideanList(inputFile, queryFile, k, L, outputFile, &dataLength);
			cout << "EINAI OK " << endl;
			delete euclideanList;
			exit(1);
		}
		//  CASE COSINE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX
		if (strcmp(metric.c_str(), "cosine") == 0) {

			ListData<double*>* cosineList = new ListData<double*>();
			cosineList->initCosineList(inputFile, queryFile, k, L, outputFile, &dataLength);
			cout << "EINAI OK " << endl;
			delete cosineList;
			exit(1);
		}
		if (strcmp(metric_space.c_str(), "matrix") == 0)
		{
			//  CASE DISTANCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX
			ListData<double*>* DBHList = new ListData<double*>();
			DBHList->initDBHManagement(inputFile, queryFile, k, L, outputFile, &dataLength);
			delete DBHList;
			exit(1);
		}

		//#######################################################################################################################




		//#######################################################################################################################

		//  CASE HAMMING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TO - FIX

		cout << "********************* Hamming space LSH testing ********************* " << endl << endl;

		inputFile.clear();      //restart
		inputFile.seekg(0, ios::beg);   //data file back from start

		ListData<string>* hammingList = new ListData<string>();
		Node<string>* realNN = NULL;
		Node<string>* lshNN= NULL;
		Node<string>* nodeHammingPtr = NULL;        //haming node pointer


		inputFile >> genericStr;    //read "@metric space"      //NOT NEEDED
		inputFile >> genericStr;	//read etc, "hamming"       //NOT NEEDED
		inputFile >> itemName;	    //read itemno
		inputFile >> genericStr;	//read data size

		dataLength = genericStr.length();

		if (k > dataLength)
		{
			cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
			k = dataLength;
		}

		//cout << "The size of each hamming code is: " << dataLength <<endl;
		inputFile.clear();      //restart
		inputFile.seekg(0, ios::beg);   //data file back from start

		inputFile >> genericStr;    //read "@metric space"
		inputFile >> metric_space;	//read etc, "hamming"
		begin = clock();

		//HASTABLE CREATION
		Hash<string>* hashTableList = new Hash<string>[L];
		int** miniHashIndexList = new int*[L];			//miniHashIndexList is used to store the miniHashIndex for every hashTable
		int currentIndex = 0;
		int hashResult = 0;
		for (int l = 0; l < L; l++) //every hash table
		{
			//cout << "metric_space : " << metric_space << endl;
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

			end_List_creation = clock();

			begin_lsh_hashing = clock();
			//cin >> genericStr;      //to wait
			//LSH works this way for Hamming strings
			//we pick randomly k bits of the Hamming bitstring (k mini-hash h functions) and use the concatenation of those to find the bucket
			itemNo = 0;
			while (!inputFile.eof())
		    {
		        //cout << "waduuuuuuuuuuuuuuup" <<endl;
		        itemNo++;
		        if (turn)
		        {
		            inputFile >> itemName;	//item etc
		            inputFile >> genericStr;	//data we want to store
		        }
		        else
		        {
		            inputFile >> genericStr;	//@metric_spaces
		            inputFile >> genericStr;	//hamming
		            inputFile >> itemName;	//item etc
		            inputFile >> genericStr;	//data we want to store
		        }
		        //hammingList->Insert(genericStr, strtod(itemName.c_str(), NULL));    //add on item list
		        hammingList->Insert(genericStr, itemNo, itemName);
		        nodeHammingPtr = hammingList->ReturnHead();     //return the head of the list
		        for (int i=0; i < k; i++) {
		            currentIndex = miniHashIndex[i];        //current index regarding the Hamming string;
		            hashResult += pow (2, i) * (genericStr[currentIndex] - '0');    //creates the binary as an int
		            //cout << "The (unfinished) hash result: " << hashResult << "("<< pow(2, i)<< "-" << genericStr[currentIndex] - '0' <<")" << endl;
		            //cin >>genericStr;
		        }

		        //hashTableList[l].Insert(hashResult, genericStr, hashResult, strtod(itemName.c_str(), NULL));
		        hashTableList[l].Insert(hashResult, genericStr, hashResult, itemNo, itemName);
		        //int hdis = hammingList->Distance(myString, theCode);
		        //cout << "------->  TA KANEI AYTA" << endl;
		        hashResult = 0;
		    }
		    int test;
		    //cout << "------->  TA KANEI AYTA" << endl;
		    //hashTableList[l].printHash();
		    //cin >> test;



		    inputFile.clear();
		    inputFile.seekg(0, ios::beg);   //data file back from start
		    inputFile >> genericStr;	//item etc
		    inputFile >> genericStr;	//data we want to store


		}
		/////////////////////////////////////////////////////////
			end_lsh_hashing = clock();
			elapsed_secs_hashing = (double) (end_lsh_hashing - begin_lsh_hashing) / CLOCKS_PER_SEC;
			//cin >> queryCode;

			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			do 
			{
				queryFile.clear();      //restart
				queryFile.seekg(0, ios::beg);   //data file back from start
				queryFile >> queryCode;	//@Radius
				queryFile >> Radius;	//radius_value

				Node<string>** listBucketTable = new Node<string>*[L];

				while (!queryFile.eof())
				{
					//queryFile >> itemName;	//item
					if (!(queryFile >> itemName))
					{
						break;
					}
					outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << itemName << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
					queryFile >> queryCode;	//data we want to compare
					begin_lsh_query = clock();

					for (int l =0; l < L; l++)
					{		//for every hash table
						hashResult = 0;
						//cout << "**************************************************************************************" << endl;
						//cout << "------->  QUERY CODE : " << queryCode << endl << endl;

						for (int i=0; i < k; i++)
						{
							currentIndex = miniHashIndexList[l][i];        //current index regarding the Hamming string - using the miniHash that was used before
							hashResult += pow (2, i) * (queryCode[currentIndex] - '0');    //creates the binary as an int
							//cout << queryCode[currentIndex] - '0';
							//cout << "The (unfinished) hash result: " << hashResult << "("<< pow(2, i)<< "-" << genericStr[currentIndex] - '0' <<")" << endl;
							//cin >>genericStr;
						}
						//cout << endl;

						//cout << "------->  HASH RESULT IN QUERY : " << hashResult <<endl;
						listNode = hashTableList[l].getHashTable()[hashResult].getBucket();
						listBucketTable[l] = listNode;
						//cout << " IN LIST NODE : " << listNode->getKey() << endl;
						//cout << endl << endl << endl;
					}
					if (Radius > 0) 
			        {
						outputFile << "R NNs: "<<endl;
					}
					for (int i = 0; i < L; ++i)
					{
						if (Radius > 0) 
			            {
							outputFile <<"Table " << i << ":" <<endl;
						}
						listNode = listBucketTable[i];		//we take the bucket
						while (listNode != NULL)
						{
							lshdis = hammingList->Distance(queryCode, listNode->getKey());
							if ((lshdis <= Radius) && (Radius > 0 )) {
								outputFile << "--"<<listNode->getItemName() <<endl;
							}
							if ((lshdis < minLSHDistance) && (lshdis != 0))
							{
								minLSHDistance = lshdis;
								minimumNode = listNode;
							}
							listNode = listNode->getNext();
						}
					}
					lshNN = minimumNode;
					//end_lsh = clock();

					//ENDED LSH
					end_lsh_query = clock();
					elapsed_secs_query = (double) (end_lsh_query - begin_lsh_query) / CLOCKS_PER_SEC;



					//************************ ENDED LSH HAMMING ************************


					Node<string>* newNode = hammingList->getNode();
					begin_brute = clock();
					while(newNode != NULL)
					{
						hdis = hammingList->Distance(queryCode, newNode->getKey());
						//cout << "------->  HAMMING DISTANCE :  : " << hdis <<endl;
						//cout << "------->  RADIUS :  : " << Radius <<endl;
						if ((hdis < minBruteDistance) && (hdis != 0))
						{
							//outputFile << "------->  IN RADIUS : " << newNode->getKey() << endl;
							minBruteDistance = hdis;
							realNN = newNode;
						}
						newNode = newNode->getNext();
					}
					end_brute = clock();



					//cout << "Time query : " << elapsed_secs_query << endl;
					//cout << "Time hashing : " << elapsed_secs_hashing << endl;

					elapsed_secs_lsh = (double) (elapsed_secs_query + elapsed_secs_hashing + end_List_creation - begin)  / CLOCKS_PER_SEC;
					elapsed_secs_brute = (double) (end_brute - begin_brute+ end_List_creation - begin) / CLOCKS_PER_SEC;

					//elapsed_secs_lsh = double (elapsed_secs_query + elapsed_secs_hashing) / CLOCKS_PER_SEC;
					//elapsed_secs_brute = double (end_brute - begin - (end_lsh - begin_lsh)) / CLOCKS_PER_SEC;
					//double elapsed_secs_ = double(end - begin) / CLOCKS_PER_SEC;		//alakse dhlwsh kai balthn panw

					outputFile << "------->  LSH NN :  " << lshNN->getItemName() << endl;
					outputFile << "------->  The lsh nearest neighbour for query " << queryCounter << " is within distance  : " << minLSHDistance << endl;
					outputFile << "------->  Time taken LSH: " << elapsed_secs_lsh << endl << endl;

					outputFile << "------->  Real NN :  " << realNN->getItemName() << endl;
					outputFile << "------->  The real nearest neighbour for query" << queryCounter << " is within distance  : " << minBruteDistance << endl;
					outputFile << "------->  Time taken brute force: " << elapsed_secs_brute << endl << endl;

					outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER " << queryCounter << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

					//inputFile.clear();
					//inputFile.seekg(0, ios::beg);   //data file back from start
					minBruteDistance = 9999;			//resetting the minimum distance
					minLSHDistance = 9999;
					realNN = NULL;
					lshNN = NULL;
					turn = false;
					elapsed_secs_lsh = 0.0f;
					elapsed_secs_brute = 0.0f;
					++queryCounter;
				}
				queryCounter = 1;
				outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
				outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY FILE   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
				outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
				//hammingList->PrintData();

				
				cout << " Press:" <<endl << "'a' - change all files (Rebuild LSH Tables)" <<endl << "'i' - change input(dataset) file (Rebuild LSH Tables)" <<endl << "'o' - change output file" <<endl << "'q' - change query file" << endl << "If you want to exit please type 'exit'" << endl;
				cin >> choice;
				if (choice.compare("a") == 0 || choice.compare("'a'") == 0) {
					break;
				}
				else if (choice.compare("i") == 0 || choice.compare("'i'") == 0) {
					break;
				}
				else if (choice.compare("o") == 0 || choice.compare("'o'") == 0) {
					cout << "Please give output file name: ";
					cin >> filename;
					outputFile.close();
					outputFile.open(filename.c_str());		//input file comes next on argv
					if (outputFile == NULL)
					{
						cout << "You've given a wrong input file. " << endl;
						exit(1);
					}
					else
					{
						cout << "File : " << filename << " opened successfully!" << endl << endl;
					}
				}
				else if (choice.compare("q") == 0 || choice.compare("'q'") == 0) {
					cout << "Please give output file name: ";
					cin >> filename;
					queryFile.close();
					queryFile.open(filename.c_str());		//input file comes next on argv
					if (queryFile == NULL)
					{
						cout << "You've given a wrong input file. " << endl;
						exit(1);
					}
					else
					{
						cout << "File : " << filename << " opened successfully!" << endl << endl;
					}
				}
				else if ((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0)) {
					cout << "Command not recognised. Exiting... You lost your chance..." <<endl;
					exit(-1);
				}
			}while((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0));
		delete hammingList;
		//cin.get();
		
		cout << " If you want to continue please type:" <<endl << "'a' - change all files" <<endl << "'i' - change input(dataset) file" <<endl << "'o' - change output file" <<endl << "'q' - change query file" << endl << "If you want to exit please type 'exit'" << endl;
		cin >> choice;
		if (choice.compare("a") == 0 || choice.compare("'a'") == 0) {
			inputFile.close();
			outputFile.close();
			queryFile.close();
		}
		else if (choice.compare("i") == 0 || choice.compare("'i'") == 0) {
			outParameter = true;
			queryParameter = true;
			inputFile.close();
		}
		else if (choice.compare("o") == 0 || choice.compare("'o'") == 0) {
			inParameter = true;
			queryParameter = true;
			outputFile.close();
		}
		else if (choice.compare("q") == 0 || choice.compare("'q'") == 0) {
			inParameter = true;
			outParameter = true;
			queryFile.close();
		}
		else if ((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0)) {
			cout << "Command not recognised. Exiting... You lost your chance..." <<endl;
			exit(-1);
		}
	}while ((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0) );
	return 0;
}
