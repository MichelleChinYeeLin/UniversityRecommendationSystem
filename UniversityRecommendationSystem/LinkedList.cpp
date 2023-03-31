#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

UniList::UniList() {
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}
UniList::UniNode* UniList::createNewNode(int rank, string name, string locationCode, string location, double arScore, int arRank, double erScore, int erRank,
	double fsrScore, int fsrRank, double cpfScore, int cpfRank, double ifrScore, int ifrRank, double isrScore, int isrRank,
	double irnScore, int irnRank, double gerScore, int gerRank, double scoreScaled) {
	UniNode* newNode = new UniNode;
	newNode->rank = rank;
	newNode->name = name;
	newNode->locationCode = locationCode;
	newNode->location = location;
	newNode->arScore = arScore;
	newNode->arRank = arRank;
	newNode->erScore = erScore;
	newNode->erRank = erRank;
	newNode->fsrScore = fsrScore;
	newNode->fsrRank = fsrRank;
	newNode->cpfScore = cpfScore;
	newNode->cpfRank = cpfRank;
	newNode->ifrScore = ifrScore;
	newNode->ifrRank = ifrRank;
	newNode->isrScore = isrScore;
	newNode->isrRank = isrRank;
	newNode->irnScore = irnScore;
	newNode->irnRank = irnRank;
	newNode->gerScore = gerScore;
	newNode->gerRank = gerRank;
	newNode->scoreScaled = scoreScaled;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

void UniList::insertToFront(int rank, string name, string locationCode, string location, double arScore, int arRank, double erScore, int erRank,
				   double fsrScore, int fsrRank, double cpfScore, int cpfRank, double ifrScore, int ifrRank, double isrScore, int isrRank,
				   double irnScore, int irnRank, double gerScore, int gerRank, double scoreScaled) {
	UniNode* newNode = createNewNode(rank, name, locationCode, location, arScore, arRank, erScore, erRank, fsrScore, fsrRank, cpfScore, cpfRank,
									 ifrScore, ifrRank, isrScore, isrRank, irnScore, irnRank, gerScore, gerRank, scoreScaled);

	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}

	size++;
}

void UniList::insertToEnd(int rank, string name, string locationCode, string location, double arScore, int arRank, double erScore, int erRank,
				 double fsrScore, int fsrRank, double cpfScore, int cpfRank, double ifrScore, int ifrRank, double isrScore, int isrRank,
				 double irnScore, int irnRank, double gerScore, int gerRank, double scoreScaled) {
	UniNode* newNode = createNewNode(rank, name, locationCode, location, arScore, arRank, erScore, erRank, fsrScore, fsrRank, cpfScore, cpfRank,
									 ifrScore, ifrRank, isrScore, isrRank, irnScore, irnRank, gerScore, gerRank, scoreScaled);

	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	size++;
}

void UniList::deleteFromFront() {
	if (head == NULL) {
		return;
	}

	UniNode* current = head;
	head = current->next;
	
	delete current;
	size--;
}

void UniList::deleteFromEnd() {
	if (head == NULL) {
		return;
	}

	UniNode* current = tail;
	tail = current->prev;
		
	delete current;
	size--;
}

void UniList::displayList() {
	//Header
	cout << string(135, '=') << endl;
	cout << left << setw(5) << "Rank" << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
	cout << string(135, '=') << endl;

	UniNode* current = head;

	while (current != NULL) {
		cout << left << setw(5) << current->rank << setw(90) << current->name << setw(10) << current->locationCode << setw(30) << current->location << endl;

		current = current->next;
	}
}