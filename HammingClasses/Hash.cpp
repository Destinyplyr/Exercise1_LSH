#include "Hash.h"


using namespace std;

template <typename T>
Hash<T>::Hash(int k, string metric_space)
{
	int tableSize = power(2, k);
	if (metric_space.compare("vector")) {
		this->hashTable = new Node<vector>*[tableSize];
	}
	else if (metric_space.compare("hamming")) {
		this->hashTable = new Node<string>*[tableSize];
	}
	else if (metric_space.compare("matrix")) {
		this->hashTable = new Node<string>*[tableSize];
	}


	//cout << "Node created successfully!" << endl;
}


template <typename T>
Hash<T>::~Hash()
{
	//cout << "Node deleted." << endl;
}


template <typename T>
Hash<T>* Hash<T>::getHashTable()
{
	return hashTable;
}


template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
}

