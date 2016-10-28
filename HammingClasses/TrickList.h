#ifndef TRICK_LIST
#define TRICK_LIST

#include "Node.h"
#include <math.h>


template <typename T>
class TrickList		//the first of every tricklist is considered an info head
{
	public:
		TrickList();
		~TrickList();

		TrickList<T>* getNext();
		void setNext(TrickList<T>* next);
		void Insert(Node<T>* newItem);
		void setG(Node<T>* gCode);
		Node<T>* getGNode();
		static double Distance(double p1[], double p2[], int size);
		double* NNTrickList(double* thePoint, int size);

	private:

		Node<T>* gCode;
		TrickList<T>* next;
};


#endif 