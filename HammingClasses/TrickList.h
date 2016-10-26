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
		int getG();
		void Insert(T newItem);
		//void setKey(T key);
	

	private:

		Node<T>* gCode;
		TrickList<T>* next;
};


#endif 