#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<>
bool LinkedList<University>::display(int min, int max) {

	if (min > size) {
		return true;
	}

	Node<University>* current = head;
	int count = 1;

	//Header
	cout << string(135, '=') << endl;
	cout << left << setw(5) << "Rank" << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
	cout << string(135, '=') << endl;
 
	while (current != NULL)
{
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

	return false;
}