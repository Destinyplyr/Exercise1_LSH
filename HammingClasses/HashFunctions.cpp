#include "Hash.h"


using namespace std;

//HEADHASHNODE FUNCTIONS

/*
template <typename T>       //just assign the metric space
void headHashNode<T>::initHeadHashNode(string metric_space) {
    this->metric_space = metric_space;
/*
    if (metric_space.compare("hamming") == 0) {
        bucket_key = -1;
        this->
    }
    else if (metric_space.compare("vector") == 0) {
        for (i = 0; i < tableSize; i++) {
            hashTable[].initHeadHashNode(metric_space);
        }
    }
    else if (metric_space.compare("matrix") == 0) {
        for (i = 0; i < tableSize; i++) {
            hashTable[].initHeadHashNode(metric_space);
        }
    }
}*/

template <typename T>
int headHashNode<T>::getBucketKey() {
    return bucket_key;
}

template <typename T>
void headHashNode<T>::setBucketKey(int bucket_key) {
    this->bucket_key = bucket_key;
}


template <typename T>
Node<T>* headHashNode<T>::getBucket()
{
    return bucket;
}


template <typename T>
void headHashNode<T>::setBucket(Node<T>* bucket)
{
    this->bucket = bucket;
}

template <typename T>
int headHashNode<T>::Insert(int hashResult, Node<T>* newItem, int g)
{
    newItem->setNext(this->bucket);
    newItem->setG(g);
    this->bucket = newItem;
    //cout <<"ADDED IT MOTHAFUCKA!" <<endl;
    return 0;
}

template <typename T>
void headHashNode<T>::InsertTrick(int g, TrickList<T>* trickList) {
    cout << "in tric g : " << g << endl;
    Node<T>* currentNode;
    currentNode = this->bucket;
    cout << currentNode <<endl;
    while(currentNode != NULL) {
        if (currentNode->getG() == g) {
            trickList->Insert(currentNode);
            cout << "Added in trickList : " << currentNode->getKey()[0] << endl;
        }
        cout << "NodeID: " << currentNode->getG() << " - g: " <<g <<endl;
        currentNode = currentNode->getNext();
    }
}

template <typename T>
void headHashNode<T>::printHash() {
    cout << endl;
    cout << ">>>>> Printing Bucket" <<endl;
    if (this->bucket_key == -1) {
        cout << "Bucket empty" << endl;
    }
    else {
        cout << ">> Bucket key: " << bucket_key << endl;
        Node<T>* current;
        current = this->bucket;

        while (current != NULL) {
            cout << "Item:" << current->getKey() <<endl;
            current = current->getNext();
        }

        cout << ">>>>> " <<endl;
        cout << endl;
    }
}



//HASH FUNCTIONS

/*template <typename T>
Hash<T>::Hash(int k, string metric_space)       //unusable -- must mimic operations elsewhere
{
/*
	int tableSize = this->power(2, k);
	if (metric_space.compare("vector")) {
		this->hashTable = new headHashNode<T>*[tableSize];
	}
	else if (metric_space.compare("hamming")) {
		this->hashTable = new headHashNode<T>*[tableSize];
	}
	else if (metric_space.compare("matrix")) {
		this->hashTable = new headHashNode<T>*[tableSize];
	}


	//cout << "Node created successfully!" << endl;
}*/

template <typename T>
Hash<T>::Hash()
{
	hashTable = NULL;
}

template <typename T>
void Hash<T>::initHash(int k, string metric) {
    int tableSize;
    cout << "metric_space " << metric << endl;
    //cout << "FUCIENFM ET : " << metric << endl;
    //cout << "FUCIENFM ET str : " << metric.c_str() << endl;
    if (strcmp(metric.c_str(), "hamming") == 0) {
        tableSize = pow(2, k);
    }
    if (strcmp(metric.c_str(), "euclidean") == 0) {
        tableSize = k;
    }
    if (strcmp(metric.c_str(), "cosine") == 0) {
        tableSize = pow(2, k);
    }
    if (strcmp(metric.c_str(), "matrix") == 0) {
        tableSize = pow(2, k);
    }
    this->tableSize = tableSize;
   // cout << "GINETAI AYTO XXAXAXAXA " << tableSize << endl;
	this->hashTable = new headHashNode<T>[tableSize]();
    //cout << "bad alloc init" << endl;
    this->metric_space = metric;

/*
    //initializing hashTable headHashNodes
    if (metric_space.compare("hamming") == 0) {
        for (i = 0; i < tableSize; i++) {
            hashTable[].initHeadHashNode(metric_space);
        }
    }
    else if (metric_space.compare("vector") == 0) {
        for (i = 0; i < tableSize; i++) {
            hashTable[].initHeadHashNode(metric_space);
        }
    }
    else if (metric_space.compare("matrix") == 0) {
        for (i = 0; i < tableSize; i++) {
            hashTable[].initHeadHashNode(metric_space);
        }
    }*/
}

template <typename T>
headHashNode<T>* Hash<T>::getHashTable()
{
    return hashTable;
}


template <typename T>
void Hash<T>::Insert(int hashResult, T newItem, int g, int itemno) {
    if (this->hashTable[hashResult].getBucketKey() == -1) {       //first item on this bucket
        this->hashTable[hashResult].setBucketKey(hashResult);
    }

    Node<T>* newNode = new Node<T>(newItem, g, itemno);
    this->hashTable[hashResult].Insert(hashResult, newNode, g);
}

template <typename T>
Hash<T>::~Hash()
{
	//cout << "Node deleted." << endl;
}


/*template <typename T>
Hash<T>* Hash<T>::getHashTable()
{
	return hashTable;
}*/

template <typename T>
void Hash<T>::printHash() {
    cout << endl;
    cout << "------- Printing Hash Table -------" <<endl;
    for (int i = 0; i < tableSize; i++) {
        this->hashTable[i].printHash();
    }
    cout << "------- ------------------- -------" <<endl;
    cout << endl;
}

