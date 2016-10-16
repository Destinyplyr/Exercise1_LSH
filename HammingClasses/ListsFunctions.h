#include <iostream>
#include "ListDataHamming.h"

using namespace std;


template <typename T>
ListDataHamming<T>::ListDataHamming()		
{
	header = NULL;
	cout << "ListDataHamming initialized successfully!" << endl;		
}


template <typename T>
ListDataHamming<T>::~ListDataHamming()
{
	cout << "Finished processing the ListDataHamming" << endl;
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
		//header->setNext(NULL);
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