#ifndef NODE_H
#define NODE_H

#include <string>

template <typename T>
class Node
{
	public:
		Node();
		Node(T key);
		Node(T key, int g, int itemno);
		~Node();
		Node<T>* getNext();
		void setNext(Node<T>* next);
		T getKey();
		void setKey(T key);
		int getG();
		void setG(int g);
		int getItemNo();


	private:
	    int itemno;
		int g;
		T key;
		Node<T>* next;
};

#endif // NODE_H
