#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<>
void LinkedList<University>::display(int min, int max) {

	Node<University>* current = head;
	int count = 1;

	while (current != NULL) {

		if (count < min) {
			count++;
		}

		else if (count > max) {
			break;
		}

		else {
			University university = current->data;
			university.displayUniversitySummarized();
			count++;
		}

		current = current->next;
	}
}