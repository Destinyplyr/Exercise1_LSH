#include <iostream>
#include "TrickList.h"

using namespace std;


template <typename T>
TrickList<T>::TrickList()
{
	cout << "TrickList initialized successfully!" << endl;
}


template <typename T>
TrickList<T>::~TrickList()
{
	//
}



template <typename T>
TrickList<T>* TrickList<T>::getNext()
{
	return next;
}



template <typename T>
void TrickList<T>::setNext(TrickList<T>* next)
{
	this->next = next;
}



template <typename T>
int TrickList<T>::getG()
{
	return gCode;
}


template <typename T>
void TrickList<T>::setG(Node<T>* gCode)
{
	this->gCode = gCode;
}


template <typename T>
void TrickList<T>::Insert(T newItem)
{
	Node<T>* node = new Node<T>();
	node->setKey(newItem);
	node->setNext(NULL);

	if (gCode == NULL)
    {
		gCode = node;
    }
	else
	{
		Node<T>* tail = gCode;
		while (tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}
		tail->setNext(node);
	}

	//cout << "Item inserted" << endl;
}
