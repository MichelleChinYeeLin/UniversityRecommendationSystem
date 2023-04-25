#ifndef STACK_H
#define STACK_H
#include <iostream>

using namespace std;

template<class T>
struct StackNode {
	T data;
	StackNode<T>* next;

	StackNode(T data) {
		this->data = data;
		this->next = NULL;
	}
};

template<class T>
class Stack {
private:
	StackNode<T>* head = NULL;
	int size = 0;

public:
	Stack() {};
	StackNode<T>* createNewNode(T);
	void push(T);
	T pop();
	T peek();
	int getSize();
	bool isEmpty();
};

template<class T>
StackNode<T>* Stack<T>::createNewNode(T data) {
	StackNode<T>* newNode = new StackNode<T>(data);

	return newNode;
}

template<class T>
void Stack<T>::push(T data) {
	StackNode<T>* newNode = createNewNode(data);

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
	StackNode<T>* current = head;
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

template<class T>
bool Stack<T>::isEmpty() {
	if (size == 0) {
		return true;
	}

	return false;
}

#endif