#include <iostream>
#include <cstdlib>
#include <math.h>
#include "ListData.h"

using namespace std;


template <typename T>
ListData<T>::ListData()
{
	header = NULL;
	cout << "------->  ListData initialized successfully!" << endl << endl;
}


template <typename T>
ListData<T>::~ListData()
{
	cout << "------->  Finished processing the ListData." << endl;
}


template <typename T, size_t N>
inline
size_t sizeOfArray( const T(&)[ N ] )
{
	return N;
}


template <typename T>
Node<T>* ListData<T>::getNode() 
{
	return header;
}

template <typename T>
void ListData<T>::PrintData()
{
	Node<T>* node = new Node<T>();
	node = header;
	int counter = 1;
	while (node->getNext() != NULL)
	{
		cout << "Item " << counter << " in list : " << node->getKey() << endl;
		node = node->getNext();
		++counter;
	}

	cout << "Item " << counter << " in list : " << node->getKey() << endl;
}


template <typename T>
void ListData<T>::Insert(T newItem)
{
	Node<T>* node = new Node<T>();
	node->setKey(newItem);
	node->setNext(NULL);

	if (header == NULL)
    {
		header = node;
    }
	else
	{
		Node<T>* tail = header;
		while (tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}
		tail->setNext(node);
	}

	//cout << "Item inserted" << endl;
}

//int std::size_t size(T(&)[N]) { return N; }


template <typename T>
int ListData<T>::Distance(T item1, T item2)
{
	int distance = 0;
	int i = 0, j = 0;

	while ((i < item1.size()) && (j < item2.size()))
	{
		if (item1[i] == item2[j])
		{
			//cout << "Same bit" << endl;
			++i;
			++j;
		}
		else
		{
			//cout << "Different bit" << endl;
			++distance;
			++i;
			++j;
		}
	}

	return distance;
}


/*double Distance(double x1, double y1, double x2, double y2)
{
	double x, y;

	for (int i = 0; i < n; ++i)
	{
		
	}

	double x = x1 - x2;
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       
	dist = sqrt(dist);                  

	return dist;
}*/




template <typename T>
Node<T>* ListData<T>::ReturnHead() {
    return header;
}
