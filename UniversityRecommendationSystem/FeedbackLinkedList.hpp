#ifndef FEEDBACKLINKEDLIST_H
#define FEEDBACKLINKEDLIST_H

#include <iostream>
using namespace std;

typedef struct feedback {
	int feedbackID;
	string feedbackContent;
	feedback* prev;
	feedback* next;
}feedBack;

class FeedbackLinkedList {
private:
	feedback* head;
	feedback* tail;
	int size;
public:
	FeedbackLinkedList();
	void insertToEnd(int feedbackID, string feedbackContent);
	void removeFromFront(feedback* newNode);
	void display();
	feedBack* getTail();
	feedBack* moveForthAndBack(feedBack*, int steps);
};

#endif