#ifndef LIST_DATA_HAMMING
#define LIST_DATA_HAMMING

#include "Node.h"

template <typename T>
class ListDataHamming
{
	public:
		ListDataHamming();
		~ListDataHamming();

		void PrintData();
		void Insert(T item);
	
	private:
		Node<T>* header;
};


#endif // !LIST_DATA_HAMMING