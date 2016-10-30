#ifndef TRICK_LIST
#define TRICK_LIST

#include "Node.h"
#include <math.h>
#include <fstream>


template <typename T>
class TrickList		//the first of every tricklist is considered an info head
{
	public:
		TrickList();
		~TrickList();

		TrickList<T>* getNext();
		void setNext(TrickList<T>* next);
		void Insert(Node<T>* newItem, int L);
		void setG(Node<T>* gCode);
		Node<T>* getGNode();
		int getL();
		void setL(int table);
		static double Distance(double p1[], double p2[], int size);
		Node<double*>* NNTrickList(double* thePoint, int size, std::ofstream &outputFile, int Radius, double* minOutsideDistance);

	private:

		int table;
		Node<T>* gCode;
		TrickList<T>* next;
};


#endif
