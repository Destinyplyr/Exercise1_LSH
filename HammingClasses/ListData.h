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
		void Insert(T item, int itemno);
		int Distance(T item1, T item2);
		double CosineDistance(double p1[], double p2[], int size);
		void initEuclideanList(std::ifstream& inputFile, std::ifstream& queryFile, int k, int* dataLength);
		//std::size_t sizeArr(T(&)[]);
		void initCosineList(std::ifstream& inputFile, std::ifstream& queryFile, int k, int* dataLength);
		void initDBHManagement(std::ifstream& inputFile, std::ifstream& queryFile, int k, int* dataLength);

	private:
		Node<T>* header;
};


#endif // !LIST_DATA_HAMMING
