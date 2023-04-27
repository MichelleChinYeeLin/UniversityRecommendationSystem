#ifndef FEEDBACKLINKEDLIST_H
#define FEEDBACKLINKEDLIST_H

#include <iostream>
using namespace std;

typedef struct feedback {
	string userName;
	tm* feedbackTime;
	string feedbackContent;
	bool replied;
	tm* repliedTime;
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
	void insertToEnd(string, tm*, string, bool, tm*);
	void removeFromFront(feedback* newNode);
	void display();
	feedBack* getTail();
	feedBack* moveForthAndBack(feedBack*, int steps);
};

#endif