#include<iostream>
#include"FeedbackLinkedList.hpp"
using namespace std;

FeedbackLinkedList::FeedbackLinkedList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

void FeedbackLinkedList::insertToEnd(string userName, tm* feedbackTime, 
	string feedbackContent, bool replied, tm* repliedTime) {
	feedback*newNode = new feedback;
	newNode->userName = userName;
	newNode->feedbackTime = feedbackTime;
	newNode->feedbackContent = feedbackContent;
	newNode->replied = replied;
	newNode->repliedTime = repliedTime;
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

feedBack* FeedbackLinkedList::moveForthAndBack(feedBack* current, int steps) {
	//back
	if (steps == 0) {
		if (current->prev != NULL) {
			current = current->prev;
			cout << current->feedbackContent;
		}else{
			cout << "This is the earliest feedback!";
		}
	}
	else if (steps == 1) {
		if (current->next != NULL) {
			current = current->next;
			cout << current->feedbackContent;
		}
		else {
			cout << "This is the latest feedback!";
		}
	}
	else {
		cout << "Invalid option! " << endl;
	}
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
		cout << temp->feedbackTime << endl;
		cout << temp->feedbackContent << endl;
		temp = temp->next;
	}
}

//int main() {
//	FeedbackLinkedList* f = new FeedbackLinkedList();
//	f->insertToEnd(1, "hi");
//	f->insertToEnd(2, "hello");
//	f->insertToEnd(3, "nihao");
//	feedBack* a = f->getTail();
//	a = f->moveForthAndBack(a, 0); //this will print hello
//	cout << "\n"<<a<<"\n";
//	a = f->moveForthAndBack(a, 0); //this will print hi
//	cout << "\n" << a<< "\n";
//	a = f->moveForthAndBack(a, 0); // this will print this is the earliest feedback
//	cout << "\n" << a << "\n";
//}