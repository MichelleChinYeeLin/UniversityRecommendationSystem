#include<iostream>
#include"FeedbackLinkedList.hpp"
using namespace std;

FeedbackLinkedList::FeedbackLinkedList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

void FeedbackLinkedList::insertToEnd(string userName, time_t feedbackTime,
	string feedbackContent, bool replied, string repliedContent, time_t repliedTime) {
	feedback* newNode = new feedback;
	newNode->userName = userName;
	newNode->feedbackTime = feedbackTime;
	newNode->feedbackContent = feedbackContent;
	newNode->replied = replied;
	newNode->repliedTime = repliedTime;
	newNode->replyContent = repliedContent;
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
		}
		else {
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

void FeedbackLinkedList::display() {
	feedback* temp = head;
	while (temp != NULL) {
		system("cls");

		char timeString[26];
		ctime_s(timeString, sizeof(timeString), &temp->feedbackTime);
		timeString[strcspn(timeString, "\n")] = '\0';

		cout << "Feedback Time: " << timeString << endl;
		cout << "User Name: " << temp->userName << endl;
		cout << "Feedback Content: " << temp->feedbackContent << endl;

		if (temp->replied) {
			char timeString2[26];
			ctime_s(timeString2, sizeof(timeString2), &temp->repliedTime);
			timeString2[strcspn(timeString2, "\n")] = '\0';
			cout << "Replied Time: " << timeString2 << endl;
			cout << "Reply Content: " << temp->replyContent << endl;
		}
		else {
			cout << "No reply available for this feedback." << endl;
		}

		string userInput;
		cout << endl << endl;
		cout << "Enter 'N' to view next feedback, 'P' to view previous feedback" << endl;
		cout << "Enter any other key to exit" << endl;
		cout << "Option: ";
		cin >> userInput;

		if (userInput == "N") {

			if (temp->next == NULL) {
				cout << "No next feedback!" << endl;
				system("pause");
				system("cls");
				continue;
			}

			temp = temp->next;
		}

		else if (userInput == "P") {

			if (temp->prev == NULL) {
				cout << "No previous feedback!" << endl;
				system("pause");
				system("cls");
				continue;
			}

			temp = temp->prev;
		}

		else {
			break;
		}
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

void FeedbackLinkedList::replyFeedback(string replyContent) {
	if (head == nullptr) {
		cout << "No feedback available to reply." << endl;
		return;
	}

	feedback* oldestFeedback = head;
	feedback* newHead = head->next;
	time_t currentTime = time(nullptr);

	oldestFeedback->replied = true;
	oldestFeedback->replyContent = replyContent;
	oldestFeedback->repliedTime = currentTime;

	cout << "Reply sent successfully!" << endl;

	if (newHead != nullptr) {
		head = newHead;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}
	}
	else {
		if (head != nullptr) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}
	}

	//move the replied feedback to the end of the list
	if (oldestFeedback != tail) {
		tail->next = oldestFeedback;
		oldestFeedback->prev = tail;
		oldestFeedback->next = nullptr;
		tail = oldestFeedback;
	}
}