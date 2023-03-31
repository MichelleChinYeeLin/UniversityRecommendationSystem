#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

using namespace std;

class UniList {
private:
	struct UniNode {
		int rank;
		string name, locationCode, location;
		double arScore, erScore, fsrScore, cpfScore, ifrScore, isrScore, irnScore, gerScore, scoreScaled;
		int arRank, erRank, fsrRank, cpfRank, ifrRank, isrRank, irnRank, gerRank;

		UniNode* prev = NULL;
		UniNode* next = NULL;
	};

	UniNode* head;
	UniNode* tail;
	int size;

public:
	UniList();
	UniNode* createNewNode(int, string, string, string, double, int, double, int, double, int, double, int, double,
						   int, double, int, double, int, double, int, double);
	void insertToFront(int, string, string, string, double, int, double, int, double, int, double, int, double,
					   int, double, int, double, int, double, int, double);
	void insertToEnd(int, string, string, string, double, int, double, int, double, int, double, int, double,
					 int, double, int, double, int, double, int, double);
	void deleteFromFront();
	void deleteFromEnd();
	void displayList();
};

#endif