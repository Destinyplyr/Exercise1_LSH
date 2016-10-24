#ifndef LIST_DATA
#define LIST_DATA

#include "Node.h"

template <typename T>
class ListData
{
	public:
		ListData();
		~ListData();
        Node<T>* ReturnHead();
        Node<T>* getNode();
		void PrintData();
		void Insert(T item);
		int Distance(T item1, T item2);
		void initEuclideanList();

	private:
		Node<T>* header;
};


#endif // !LIST_DATA_HAMMING
