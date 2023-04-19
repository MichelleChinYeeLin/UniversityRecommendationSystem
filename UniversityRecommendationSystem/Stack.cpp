#include "Stack.h"
#include <iostream>

using namespace std;

template<class T>
Stack<T>::Stack() {
	head = NULL;
	size = 0;
}

template<class T>
Node<T>* Stack<T>::createNewNode(T data) {
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

template<class T>
void Stack<T>::push(T data) {
	Node* newNode = createNewNode(data);

	size++;

	if (head == NULL) {
		head = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
}

template<class T>
T Stack<T>::pop() {
	if (head == NULL) {
		return NULL;
	}

	Node* current = head;
	head = current->next;

	size--;

	return current->data;
}

template<class T>
T Stack<T>::peek() {
	return head->data;
}

template<class T>
int Stack<T>::getSize() {
	return size;
}