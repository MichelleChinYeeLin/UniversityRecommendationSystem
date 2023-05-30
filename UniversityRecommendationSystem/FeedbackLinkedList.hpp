#ifndef FEEDBACKLINKEDLIST_H
#define FEEDBACKLINKEDLIST_H

#include <iostream>
using namespace std;

typedef struct feedback {
	string userName;
	time_t feedbackTime;
	string feedbackContent;
	bool replied;
	string replyContent;
	time_t repliedTime;
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
	void insertToEnd(string, time_t, string, bool, string, time_t);
	void removeFromFront(feedback* newNode);
	void display();
	feedBack* getTail();
	feedBack* moveForthAndBack(feedBack*, int steps);
	void replyFeedback(string replyContent);
};

#endif
