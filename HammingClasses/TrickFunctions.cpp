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
Node<T>* TrickList<T>::getGNode()
{
	return gCode;
}


template <typename T>
void TrickList<T>::setG(Node<T>* gCode)
{
	this->gCode = gCode;
}


template <typename T>
void TrickList<T>::Insert(Node<T>* newItem)
{
	TrickList<T>* node = new TrickList<T>();
	//cout << "heheheh" <<endl;
	node->setG(newItem);
	node->setNext(NULL);

	if (this->next == NULL)
    {
		this->next = node;
    }
	else
	{
		TrickList<T>* tail = this->next;
		while (tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}
		tail->setNext(node);
	}

	//cout << "Item inserted" << endl;
}



template <typename T>
double TrickList<T>::Distance(double item1[], double item2[], int size)
{
	double distance = 0.0f;
	double sum = 0.0f, square;
	double x, y;
	int i = 0, j = 0;

	while ((i < size) && (j < size))
	{
		x = item1[i];
		y = item2[j];
		square = pow((x - y), 2);
		sum += square;
		++i;
		++j;
		//cout << " number pos : " << i << endl;
	}
	return sqrt(sum);
}



template <typename T>
double* TrickList<T>::NNTrickList(double* thePoint, int size)
{
	double minDistance = 999999;
	TrickList<T>* currentNode = this->next;
	double euclDis;
	double* lshNN;

	while (currentNode != NULL)
	{

		euclDis = Distance(currentNode->getGNode()->getKey(), thePoint, size);
		if (euclDis < minDistance)
		{
			minDistance = euclDis;
			lshNN = currentNode->getGNode()->getKey();
			//cout << " this time : " << endl;
		}

		currentNode = currentNode->getNext();
	}

	return lshNN;
}











