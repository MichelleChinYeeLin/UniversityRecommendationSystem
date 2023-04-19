#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "University.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;

	Node(T data) {
		this->data = data;
		this->prev = NULL;
		this->next = NULL;
	}
};

template<class T>
class LinkedList {
	Node<T>* head = NULL;
	Node<T>* tail = NULL;
	int size = 0;

public:
	LinkedList() {};

	Node<T>* createNewNode(T);
	void insertToFront(T);
	void insertToEnd(T);
	void deleteFromFront();
	void deleteFromEnd();
	bool display(int, int);
};

template<class T>
Node<T>* LinkedList<T>::createNewNode(T data)
{
	Node<T>* newNode = new Node<T>(data);

	return newNode;
}

template<class T>
void LinkedList<T>::insertToFront(T data) {
	Node<T>* newNode = createNewNode(data);

	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}

	size++;
}

template<class T>
void LinkedList<T>::insertToEnd(T data) {
	Node<T>* newNode = createNewNode(data);

	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	size++;
}

template<class T>
void LinkedList<T>::deleteFromFront() {
	if (head == NULL) {
		return;
	}

	Node<T>* current = head;
	head = current->next;

	delete current;
	size--;
}

template<class T>
void LinkedList<T>::deleteFromEnd() {
	if (head == NULL) {
		return;
	}

	Node<T>* current = tail;
	tail = current->prev;

	delete current;
	size--;
}

template<>
bool LinkedList<University>::display(int min, int max);

#endif