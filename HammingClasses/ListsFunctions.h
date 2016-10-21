#include <iostream>
#include "ListDataHamming.h"

using namespace std;


template <typename T>
ListDataHamming<T>::ListDataHamming()
{
	header = NULL;
	cout << "------->  ListDataHamming initialized successfully!" << endl << endl;
}


template <typename T>
ListDataHamming<T>::~ListDataHamming()
{
	cout << "------->  Finished processing the ListDataHamming." << endl;
}


template <typename T>
Node<T>* ListDataHamming<T>::getNode() 
{
	return header;
}

template <typename T>
void ListDataHamming<T>::PrintData()
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
void ListDataHamming<T>::Insert(T newItem)
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


template <typename T>
int ListDataHamming<T>::Distance(T item1, T item2)
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

template <typename T>
Node<T>* ListDataHamming<T>::ReturnHead() {
    return header;
}
