#ifndef STACK_H
#define STACK_H
#include <iostream>

using namespace std;

//Structure for a node in the stack
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

//Create a new node for the stack
template<class T>
StackNode<T>* Stack<T>::createNewNode(T data) {
	StackNode<T>* newNode = new StackNode<T>(data);

	return newNode;
}

//Insert a new node to the front of the stack
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

//Remove the node at the front of the stack
template<class T>
T Stack<T>::pop() {
	StackNode<T>* current = head;
	head = current->next;

	size--;

	return current->data;
}

//Return the data in the node at the front of the stack
template<class T>
T Stack<T>::peek() {
	return head->data;
}

//Return the size of the stack
template<class T>
int Stack<T>::getSize() {
	return size;
}

//Check if the stack is empty
template<class T>
bool Stack<T>::isEmpty() {
	if (size == 0) {
		return true;
	}

	return false;
}

#endif