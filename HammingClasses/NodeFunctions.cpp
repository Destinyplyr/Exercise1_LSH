#include <iostream>
#include "Node.h"

using namespace std;


template <typename T>
Node<T>::Node()
{
	//cout << "Node created successfully!" << endl;
}

template <typename T>
Node<T>::Node(T key)
{
	this->key = key;			//works for both Hamming (T = string) and Vector (T = double*)
	this->next = NULL;
	//cout << "Node created successfully!" << endl;
}


template <typename T>
Node<T>::Node(T key, int g)
{
	this->key = key;			//works for both Hamming (T = string) and Vector (T = double*)
	this->next = NULL;
	this->g = g;
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