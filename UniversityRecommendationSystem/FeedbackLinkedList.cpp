#include<iostream>
#include"FeedbackLinkedList.hpp"
using namespace std;

FeedbackLinkedList::FeedbackLinkedList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

void FeedbackLinkedList::insertToEnd(int feedbackID, string feedbackContent) {
	feedback*newNode = new feedback;
	newNode->feedbackID = feedbackID;
	newNode->feedbackContent = feedbackContent;
	newNode->prev = NULL;
	newNode->next = NULL;

	if (head == NULL) {
		head = tail = newNode;
		size += 1;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	size++;
}

feedBack* FeedbackLinkedList::getTail() {
	return tail;
}

feedBack* FeedbackLinkedList::moveBack(feedBack*current, int steps) {
	feedback* p = current;
	while (p->prev) {
		if (steps == 0) {
			current = p;
			cout << p->feedbackContent;
			return current;
		}
		p = p->prev;
		steps--;
	}
	current = p;
	cout << p->feedbackContent;
	return current;
}

feedBack* FeedbackLinkedList::moveForward(feedBack* current, int steps) {
	feedback* p = current;
	while (p->next) {
		if (steps == 0) {
			current = p;
			cout << p->feedbackContent;
			return current;
		}
		p = p->next;
		steps--;
	}
	current = p;
	cout << p->feedbackContent;
	return current;
}

void FeedbackLinkedList::removeFromFront(feedback* newNode) {
	if (head == NULL) {
		return;
	}
	feedback* temp = head;
	head = head->next;
	if (head == NULL) {
		tail = NULL;
	}
	delete temp;
	size -= 1;
}

void FeedbackLinkedList::display(){
	feedback* temp = head;
	while (temp != NULL) {
		cout << temp->feedbackID << endl;
		cout << temp->feedbackContent << endl;
		temp = temp->next;
	}
}

int main() {
	FeedbackLinkedList* f = new FeedbackLinkedList();
	f->insertToEnd(1, "hi");
	f->insertToEnd(2, "hello");
	f->insertToEnd(3, "nihao");
	feedBack* a = f->getTail();
	f->moveBack(a,0);
}