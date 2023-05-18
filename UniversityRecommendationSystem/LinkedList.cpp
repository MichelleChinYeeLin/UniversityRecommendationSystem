#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

template class LinkedList<University>;

template<>
bool LinkedList<University>::display(int min, int max) {

	if (min > size) {
		return true;
	}

	Node<University>* current = head;
	int count = 1;

	//Header
	cout << string(135, '=') << endl;
	cout << left << setw(5) << "No." << setw(5) << "Rank" << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
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
			cout << left << setw(5) << count;
			University university = current->data;
			university.displayUniversitySummarized();
			count++;
		}

		current = current->next;
	}

	return false;
}

template<>
void LinkedList<University>::insertionSort(Criteria criteria, bool isAscOrder) {

	Node<University>* current;
	Node<University>* temp;

	for (int i = 1; i < size - 1; i++) {
		int index = i;
	
		current = getFromPosition(index);
		temp = getFromPosition(index - 1);

		University currentUniversity = current->data;
		University tempUniversity = temp->data;

		if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
			string stringValue1 = toUpperCase(currentUniversity.getUniversityStringValue(criteria));
			string stringValue2 = toUpperCase(tempUniversity.getUniversityStringValue(criteria));

			if (isAscOrder) {
				while (index > 0 && stringValue2 > stringValue1) {
					swapNodePosition(current, temp);

					index -= 1;

					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					stringValue1 = toUpperCase(university1.getUniversityStringValue(criteria));
					stringValue2 = toUpperCase(university2.getUniversityStringValue(criteria));
				}
			}

			else {
				while (index > 0 && stringValue2 < stringValue1) {
					swapNodePosition(current, temp);

					index -= 1;

					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					stringValue1 = toUpperCase(university1.getUniversityStringValue(criteria));
					stringValue2 = toUpperCase(university2.getUniversityStringValue(criteria));
				}
			}
		}

		else {
			double numValue1 = currentUniversity.getUniversityNumValue(criteria);
			double numValue2 = tempUniversity.getUniversityNumValue(criteria);

			if (isAscOrder) {
				while (index > 0 && numValue2 > numValue1) {
					swapNodePosition(current, temp);

					index -= 1;

					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					numValue1 = university1.getUniversityNumValue(criteria);
					numValue2 = university2.getUniversityNumValue(criteria);
				}
			}

			else {
				while (index > 0 && numValue2 < numValue1) {
					swapNodePosition(current, temp);

					index -= 1;

					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					numValue1 = university1.getUniversityNumValue(criteria);
					numValue2 = university2.getUniversityNumValue(criteria);
				}
			}
		}
	}
}

template<>
void LinkedList<University>::quickSort(Criteria criteria, bool isAscOrder) {
	quickSortRecursive(criteria, isAscOrder, 0, size - 1);
}

template<>
void LinkedList<University>::quickSortRecursive(Criteria criteria, bool isAscOrder, int firstIndex, int lastIndex) {
	if (firstIndex < lastIndex) {
		int index = partition(criteria, isAscOrder, firstIndex, lastIndex);
		quickSortRecursive(criteria, isAscOrder, firstIndex, index - 1);
		quickSortRecursive(criteria, isAscOrder, index + 1, lastIndex);
	}
}

template<>
int LinkedList<University>::partition(Criteria criteria, bool isAscOrder, int firstIndex, int lastIndex) {

	Node<University>* pivot = getFromPosition(lastIndex);

	University pivotUniversity = pivot->data;

	string pivotStringValue = "", currentStringValue = "";
	double pivotNumValue = 0, currentNumValue = 0;

	int index = firstIndex - 1;

	for (int i = firstIndex; i <= lastIndex - 1; i++) {
		if (i == 147) {
			int test = 0;
		}

		Node<University>* current = getFromPosition(i);
		University currentUniversity = current->data;

		if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
			pivotStringValue = pivotUniversity.getUniversityStringValue(criteria);
			currentStringValue = currentUniversity.getUniversityStringValue(criteria);

			if (isAscOrder) {

				if (currentStringValue < pivotStringValue) {
					index++;

					Node<University>* temp = getFromPosition(index);
					swapNodePosition(current, temp);
				}
			}

			else {
				if (currentStringValue > pivotStringValue) {
					index++;
					swapNodePosition(current, getFromPosition(index));
				}
			}
		}

		else {
			pivotNumValue = pivotUniversity.getUniversityNumValue(criteria);
			currentNumValue = currentUniversity.getUniversityNumValue(criteria);

			if (isAscOrder) {

				if (currentNumValue < pivotNumValue) {
					index++;
					swapNodePosition(current, getFromPosition(index));
				}
			}

			else {
				if (currentNumValue > pivotNumValue) {
					index++;
					swapNodePosition(current, getFromPosition(index));
				}
			}
		}
	}

	swapNodePosition(getFromPosition(index + 1), getFromPosition(lastIndex));
	return index + 1;
}

template<class T>
string LinkedList<T>::toUpperCase(string value) {
	
	string newString = "";

	for (int i = 0; i < value.size(); i++) {
		char c = value[i];
		c = toupper(c);
		newString += c;
	}

	return newString;
}