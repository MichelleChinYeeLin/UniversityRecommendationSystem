#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
LinkedList<T>::LinkedList<T>() {
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}

template<class T>
Node<T>* LinkedList<T>::createNewNode(T)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;

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
void LinkedList<T>::displayList(int min, int max) {
	//Header
	cout << string(135, '=') << endl;
	cout << left << setw(5) << "Rank" << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
	cout << string(135, '=') << endl;

	Node<T>* current = head;
	int count = 1;

	while (current != NULL) {

		if (count < min) {
			count++;
		}

		else if (count > max) {
			break;
		}

		else {
			cout << left << setw(5) << current->rank << setw(90) << current->name << setw(10) << current->locationCode << setw(30) << current->location << endl;
			count++;
		}

		current = current->next;
	}
}