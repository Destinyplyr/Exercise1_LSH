#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <cmath>
#include <vector>
#include "Node.h"
#include "TrickList.h"

using namespace std;

extern "C"
{
	#include <stdlib.h>
}



template <typename T>
class headHashNode
{
	public:
		headHashNode()
		{
			bucket_key = -1;
			bucket = NULL;
			//at this stage metric_space is unassigned
		}
		//headHashNode(int k, string metric_space);
		~headHashNode() {
		}
		Node<T>* getNext();
		void initHeadHashNode(string metric);
		int Insert(int hashResult, Node<T>* newItem);
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int Insert(int hashResult, Node<T>* newItem, int g);
		void InsertTrick(int g, TrickList<T>* trickList);
		int getBucketKey();
		void setBucketKey(int key);
		void printHash();
		Node<T>* getBucket();
		void setBucket(Node<T>* bucket);


	private:
	    int bucket_key;
		Node<T>* bucket;
};



template <typename T>
class Hash
{
	public:
		Hash(int k, string metric_space);
		Hash();
		~Hash();
		void initHash(int k, string metric_space);
		void setNext(Node<T>* next);
		T getKey();
		void setKey(T key);
		void Insert(int hashResult, T newItem);
		void Insert(int hashResult, T newItem, int g);
		void printHash();
		headHashNode<T>* getHashTable();

	private:
		int tableSize;
		string metric_space;
		headHashNode<T>* hashTable;
};



#endif // HASH_H
