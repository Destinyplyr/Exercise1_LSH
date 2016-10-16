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
		int Distance(T item1, T item2);
	
	private:
		Node<T>* header;
};


#endif // !LIST_DATA_HAMMING