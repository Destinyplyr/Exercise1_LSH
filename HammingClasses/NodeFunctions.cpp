#include <iostream>
#include "Node.h"

using namespace std;


template <typename T>
Node<T>::Node()
{
	this->itemno = -1;
    this->next = NULL;
	//cout << "Node created successfully!" << endl;
}

template <typename T>
Node<T>::Node(T key)
{
	this->itemno = -1;
	this->key = key;			//works for both Hamming (T = string) and Vector (T = double*)
	this->next = NULL;
	//cout << "Node created successfully!" << endl;
}


template <typename T>
Node<T>::Node(T key, int g, int itemno, string itemName)
{
    this->itemno = itemno;
	this->key = key;			//works for both Hamming (T = string) and Vector (T = double*)
	this->next = NULL;
	this->g = g;
	this->itemName = itemName;
	//cout << "Node created successfully!" << endl;
}

template <typename T>
Node<T>::~Node()
{
	//cout << "Node deleted." << endl;
}


template <typename T>
Node<T>* Node<T>::getNext()
{
	return next;
}


template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
}


template <typename T>
T Node<T>::getKey()
{
	return key;
}


template <typename T>
void Node<T>::setKey(T key)
{
	this->key = key;
}


template <typename T>
int Node<T>::getG()
{
	return g;
}


template <typename T>
void Node<T>::setG(int g)
{
	this->g = g;
}


template <typename T>
int Node<T>::getItemNo()
{
	return itemno;
}

template <typename T>
void Node<T>::setItemName(std::string itemName)
{
	this->itemName = itemName;
}
		
template <typename T>
string Node<T>::getItemName()
{
	return itemName;
}
