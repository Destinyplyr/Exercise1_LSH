#ifndef TRICK_LIST
#define TRICK_LIST

#include "Node.h"


template <typename T>
class TrickList
{
	public:
		TrickList();
		~TrickList();

		TrickList<T>* getNext();
		void setNext(TrickList<T>* next);
		void Insert(T newItem);
		void setG(Node<T>* gCode);
		int getG();
	

	private:

		Node<T>* gCode;
		TrickList<T>* next;
};


#endif 