#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

using namespace std;

template<class T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;
};

template<class T>
class LinkedList {
	Node<T>* head = NULL;
	Node<T>* tail = NULL;
	int size = 0;

public:
	LinkedList();
	Node<T>* createNewNode(T);
	void insertToFront(T);
	void insertToEnd(T);
	void deleteFromFront();
	void deleteFromEnd();
	void displayList(int, int);
};

#endif