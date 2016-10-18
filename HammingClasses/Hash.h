#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "Node.h"

using namespace std;

extern "C"
{
	#include <stdlib.h>
}



template <typename T>
class hashNode
{
	public:
		hashNode(int k, string metric_space);
		~hashNode();
		Node<T>* getNext();
		void setNext(Node<T>* next);
		T getKey();
		void setKey(T key);


	private:
	    T key;
		hashNode<T>* next;
};

template <typename T>
class headHashNode
{
	public:
		headHashNode(int k, string metric_space);
		~headHashNode();
		Node<T>* getNext();
		void setNext(Node<T>* next);
		T getKey();
		void setKey(T key);


	private:
	    T bucket_key;
	    string metric_space;
		hashNode<T>* bucket;
};



template <typename T>
class Hash
{
	public:
		Hash(int k, string metric_space);
		Hash();
		~Hash();
		void initHash(int k, string metric_space);
		Node<T>* getNext();
		void setNext(Node<T>* next);
		T getKey();
		void setKey(T key);


	private:
		headHashNode<T>* hashTable;
};



#endif // HASH_H
