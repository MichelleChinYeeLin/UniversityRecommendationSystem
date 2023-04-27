#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "University.h"
#include <iostream>
#include <iomanip>
#include<string>

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
	Node<T>* getFromPosition(int);
	Node<T>* middle(Node<T>* node1, Node<T>* node2);
	Node<T>* binarySearch(T key);
	Node<T>* linearSearch(T key);
	//Node<T>* jumpSearch(T key);
	bool display(int, int);
	void insertionSort(Criteria, bool);
	void quickSort(Criteria, bool);
	void quickSortRecursive(Criteria, bool, int, int);
	int partition(Criteria, bool, int, int);
	void swapNodePosition(Node<T>*, Node<T>*);
	string toUpperCase(string);
	int getSize();
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

template<class T>
Node<T>* LinkedList<T>::getFromPosition(int position) {

	if (position == 0) {
		return head;
	}

	else if (position == size - 1) {
		return tail;
	}

	int count = 0;
	Node<T>* current = head;

	while (count < position) {

		if (position == 147) {
			int num = 0;
		}

		current = current->next;
		count++;
	}

	return current;
}

template<class T>
void LinkedList<T>::swapNodePosition(Node<T>* node1, Node<T>* node2) {

	if (node1 == node2) {
		return;
	}

	if (node1 == head) {
		head = node2;

	}

	else if (node2 == head) {
		head = node1;
	}

	if (node1 == tail) {
		tail = node2;
	}

	else if (node2 == tail) {
		tail = node1;
	}

	if (node1->next == node2) {
		Node<T>* leftmost = node1->prev;
		Node<T>* rightmost = node2->next;

		node1->prev = node2;
		node1->next = rightmost;
		node2->next = node1;
		node2->prev = leftmost;

		if (leftmost != NULL) {
			leftmost->next = node2;
		}

		if (rightmost != NULL) {
			rightmost->prev = node1;
		}
	}

	else if (node2->next == node1) {
		Node<T>* leftmost = node2->prev;
		Node<T>* rightmost = node1->next;

		node1->next = node2;
		node1->prev = leftmost;
		node2->prev = node1;
		node2->next = rightmost;

		if (leftmost != NULL) {
			leftmost->next = node1;
		}

		if (rightmost != NULL) {
			rightmost->prev = node2;
		}
	}

	else {

		Node<T>* node1Left = node1->prev;
		Node<T>* node1Right = node1->next;
		Node<T>* node2Left = node2->prev;
		Node<T>* node2Right = node2->next;

		node1->next = node2Right;
		node1->prev = node2Left;
		node2->next = node1Right;
		node2->prev = node1Left;

		if (node1Left != NULL) {
			node1Left->next = node2;
		}

		if (node2Left != NULL) {
			node2Left->next = node1;
		}

		if (node1Right != NULL) {
			node1Right->prev = node2;
		}
		
		if (node2Right != NULL) {
			node2Right->prev = node1;
		}
	}
}

template<class T>
int LinkedList<T>::getSize() {
	return size;
}

template<class T>
Node<T>* LinkedList<T>::middle(Node<T>* start, Node<T>* last) {
	if (start == NULL) {
		return NULL;
	}

	Node<T>* first = start;
	Node<T>* second = start->next;

	while (first != last) {
		first = first->next;
		if (first != last) {
			second = second->next;
			first = first->next;
		}
	}
	return second;
}

template<class T>
Node<T>* LinkedList<T>::linearSearch(T key) {
	Node<T>* cur = head;
	while (cur){
		if (cur->data.getName() == key.getName()) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

template<class T >
Node<T>* LinkedList<T>::binarySearch(T key) {
	int size = this->getSize();
	if (size == 0) {
		return NULL;
	}

	int low = 0;
	int high = size - 1;

	while (low <= high) {
		int mid = (low + high) / 2;
		Node<T>* node = this->getFromPosition(mid);
		string nodeValue = node->data.getName();

		if (nodeValue == key.getName()) {
			return node;
		}
		else if (nodeValue < key.getName()) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return NULL;
}

//template<class T>
//Node<T>* LinkedList<T>::jumpSearch(T key) {
//	int n = 0;
//	Node<T>* curr = head;
//
//	while (curr != nullptr) {
//		n++;
//		curr = curr->next;
//	}
//
//	int jump = sqrt(n);
//	curr = head;
//	Node<T>* prev = nullptr;
//
//	while (curr != nullptr && curr->data.getName() < key.getName()) {
//		prev = curr;
//		for (int i = 0; i < jump && curr != nullptr; i++) {
//			curr = curr->next;
//		}
//	}
//
//	while (prev != nullptr && prev->data.getName() < key.getName()) {
//		prev = prev->next;
//	}
//
//	if (prev != nullptr && prev->data.getName() == key.getName()) {
//		return prev;
//	}
//
//	return nullptr;
//}

template<>
bool LinkedList<University>::display(int min, int max);

template<>
void LinkedList<University>::insertionSort(Criteria, bool);

template<>
void LinkedList<University>::quickSort(Criteria, bool);

template<>
void LinkedList<University>::quickSortRecursive(Criteria, bool, int, int);

template<>
int LinkedList<University>::partition(Criteria, bool, int, int);

#endif