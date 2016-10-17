#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <fstream>
#include <math.h>
#include "Node.h"

using namespace std;

extern "C"
{
	#include <stdlib.h>
}


template <typename T>
class Hash
{
	public:
		Hash(int k, string metric_space);
		~Hash();
		Node<T>* getNext();
		void setNext(Node<T>* next);
		T getKey();
		void setKey(T key);


	private:
		Node<T>** hashTable;
};

#endif // HASH_H
