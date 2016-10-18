#include "Hash.h"


using namespace std;

template <typename T>
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

    */
	//cout << "Node created successfully!" << endl;
}

template <typename T>
Hash<T>::Hash()
{
	hashTable = NULL;
}

template <typename T>
void Hash<T>::initHash(int k, string metric_space) {
    int tableSize = this->power(2, k);
    this->hashTable = new headHashNode<T>[tableSize];
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
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
}

