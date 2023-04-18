#ifndef STACK_H
#define STACK_H

template<class T>
struct Node {
	T data;
	Node* next;
};

template<class T>
class Stack {
private:
	Node<T>* head;
	int size;

public:
	Stack();
	Node<T>* createNewNode(T);
	void push(T);
	T pop();
	T peek();

	int getSize();
};
#endif