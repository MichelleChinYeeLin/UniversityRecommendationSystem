#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "University.h"
#include <iostream>
#include <iomanip>
#include<string>

using namespace std;

//Structure for a node in the linked list
template<class T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;

	Node(T data) {
		this->data = data;
		this->prev = NULL;
		this->next = NULL;
	}
};

template<class T>
class LinkedList {
	Node<T>* head = NULL;
	Node<T>* tail = NULL;
	int size = 0;

public:
	LinkedList() {};
	Node<T>* createNewNode(T);
	void insertToFront(T);
	void insertToEnd(T);
	void deleteFromFront();
	void deleteFromEnd();
	Node<T>* getFromPosition(int);
	LinkedList<University> binarySearch(Criteria, const double&);
	Node<T>* linearSearch(T key);
	//Node<T>* jumpSearch(T key);
	bool display(int, int);
	void insertionSort(Criteria, bool);
	void quickSort(Criteria, bool);
	void quickSortRecursive(Criteria, bool, int, int);
	int partition(Criteria, bool, int, int);
	void swapNodePosition(Node<T>*, Node<T>*);
	string toUpperCase(string);
	int getSize();
};

//Create a new node for the linked list
template<class T>
Node<T>* LinkedList<T>::createNewNode(T data)
{
	Node<T>* newNode = new Node<T>(data);

	return newNode;
}

//Insert a new node to the front of the linked list
template<class T>
void LinkedList<T>::insertToFront(T data) {
	Node<T>* newNode = createNewNode(data);

	//If the linked list is empty
	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}

	//Increment linked list size
	size++;
}

//Insert a new node to the end of the linked list
template<class T>
void LinkedList<T>::insertToEnd(T data) {
	Node<T>* newNode = createNewNode(data);

	//If the linked list is empty
	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	//Increment linked list size
	size++;
}

//Delete a node from the front of the linked list
template<class T>
void LinkedList<T>::deleteFromFront() {
	if (head == NULL) {
		return;
	}

	Node<T>* current = head;
	head = current->next;

	delete current;
	size--;
}

//Delete a node from the end of the linked list
template<class T>
void LinkedList<T>::deleteFromEnd() {
	if (head == NULL) {
		return;
	}

	Node<T>* current = tail;
	tail = current->prev;

	delete current;
	size--;
}

//Get the node from a specific position in the linked list
//Node position starts from 0
template<class T>
Node<T>* LinkedList<T>::getFromPosition(int position) {

	//If position is the first node in the linked list
	if (position == 0) {
		return head;
	}

	//If position is the last node in the linked list
	else if (position == size - 1) {
		return tail;
	}

	int count = 0;
	Node<T>* current = head;

	//Traverse the linked list until the count matches the position
	while (count < position) {
		current = current->next;
		count++;
	}

	return current;
}

//Swap the position of node1 with node2
template<class T>
void LinkedList<T>::swapNodePosition(Node<T>* node1, Node<T>* node2) {

	//If both nodes have the same data
	if (node1 == node2) {
		return;
	}

	//If node1 is the head, change the head to node2
	if (node1 == head) {
		head = node2;

	}

	//If node2 is the head, change the head to node1
	else if (node2 == head) {
		head = node1;
	}

	//If node1 is the tail, change the tail to node2
	if (node1 == tail) {
		tail = node2;
	}

	//If node2 is the tail, change the tail to node1
	else if (node2 == tail) {
		tail = node1;
	}

	//Assume 'left' is the previous node, and 'right' is the next node
	//If node1 is to the left of node2
	if (node1->next == node2) {
		Node<T>* leftmost = node1->prev;
		Node<T>* rightmost = node2->next;

		node1->prev = node2;
		node1->next = rightmost;
		node2->next = node1;
		node2->prev = leftmost;

		if (leftmost != NULL) {
			leftmost->next = node2;
		}

		if (rightmost != NULL) {
			rightmost->prev = node1;
		}
	}

	//If node2 is to the left of node1
	else if (node2->next == node1) {
		Node<T>* leftmost = node2->prev;
		Node<T>* rightmost = node1->next;

		node1->next = node2;
		node1->prev = leftmost;
		node2->prev = node1;
		node2->next = rightmost;

		if (leftmost != NULL) {
			leftmost->next = node1;
		}

		if (rightmost != NULL) {
			rightmost->prev = node2;
		}
	}

	//If node1 and node2 are separated
	else {

		Node<T>* node1Left = node1->prev;
		Node<T>* node1Right = node1->next;
		Node<T>* node2Left = node2->prev;
		Node<T>* node2Right = node2->next;

		node1->next = node2Right;
		node1->prev = node2Left;
		node2->next = node1Right;
		node2->prev = node1Left;

		if (node1Left != NULL) {
			node1Left->next = node2;
		}

		if (node2Left != NULL) {
			node2Left->next = node1;
		}

		if (node1Right != NULL) {
			node1Right->prev = node2;
		}
		
		if (node2Right != NULL) {
			node2Right->prev = node1;
		}
	}
}

//Get the size of the linked list
template<class T>
int LinkedList<T>::getSize() {
	return size;
}

//Linear search to find a value
template<class T>
Node<T>* LinkedList<T>::linearSearch(T key) {
	// assign cur pointer points to head
	Node<T>* cur = head;

	//loop through linked list
	while (cur){
		// found
		if (cur->data.getName() == key.getName()) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

//template<class T >
//Node<T>* LinkedList<T>::binarySearch(Criteria criteria,T key) {
//	// get the size of linked list
//	int size = this->getSize();
//
//	// if the linked list is empty
//	if (size == 0) {
//		return NULL;
//	}
//
//	// set boundaries (low: the first index, high: the last index)
//	int low = 0;
//	int high = size - 1;
//
//	if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
//		while (low <= high) {
//			// find the middle
//			int mid = (low + high) / 2;
//
//			Node<T>* node = this->getFromPosition(mid);
//			string nodeValue = node->data.getName();
//
//			// found
//			if (nodeValue == key.getName()) {
//				return node;
//			}
//
//			// nodeValue < key
//			else if (nodeValue < key.getName()) {
//				low = mid + 1;
//			}
//
//			// nodeValue > key
//			else {
//				high = mid - 1;
//			}
//		}
//	}
//	else {
//		while (low <= high) {
//			// find the middle
//			int mid = (low + high) / 2;
//
//			Node<T>* node = this->getFromPosition(mid);
//			University currentUniversity = node->data;
//			double nodeValue = currentUniversity.getUniversityNumValue(criteria);
//
//			// found
//			if (nodeValue == key.getName()) {
//				return node;
//			}
//
//			// nodeValue < key
//			else if (nodeValue < key.getName()) {
//				low = mid + 1;
//			}
//
//			// nodeValue > key
//			else {
//				high = mid - 1;
//			}
//		}
//	}
//	// not found
//	return NULL;
//}

//template<class T>
//Node<T>* LinkedList<T>::binarySearch(Criteria criteria, const string& key) {
//	// get the size of linked list
//	int size = this->getSize();
//
//	// if the linked list is empty
//	if (size == 0) {
//		return NULL;
//	}
//
//	// set boundaries (low: the first index, high: the last index)
//	int low = 0;
//	int high = size - 1;
//
//	while (low <= high) {
//		// find the middle
//		int mid = (low + high) / 2;
//
//		Node<T>* node = this->getFromPosition(mid);
//		University currentUniversity = node->data;
//		string nodeValue = currentUniversity.getUniversityStringValue(criteria);
//
//		// found
//		if (nodeValue == key) {
//			return node;
//		}
//
//		// nodeValue < key
//		else if (nodeValue < key) {
//			low = mid + 1;
//		}
//
//		// nodeValue > key
//		else {
//			high = mid - 1;
//		}
//	}
//
//	// not found
//	return NULL;
//}

//Binary search to find a value
template<>
LinkedList<University> LinkedList<University>::binarySearch(Criteria criteria, const double& key) {
	LinkedList<University> matchesList;  // Linked list to store matches

	// get the size of linked list
	int size = this->getSize();

	// if the linked list is empty
	if (size == 0) {
		return matchesList;
	}

	// set boundaries (low: the first index, high: the last index)
	int low = 0;
	int high = size - 1;

	while (low <= high) {
		// find the middle
		int mid = (low + high) / 2;

		Node<University>* node = this->getFromPosition(mid);
		University currentUniversity = node->data;
		double nodeValue = currentUniversity.getUniversityNumValue(criteria);

		if (currentUniversity.getName() == "University of Oxford") {
			int test = 0;
		}

		// found
		if (nodeValue == key) {
			matchesList.insertToEnd(currentUniversity);

			Node<University>* nextUniversityNode = node->next;
			University nextUniversity = nextUniversityNode->data;
			nodeValue = nextUniversity.getUniversityNumValue(criteria);

			while (nodeValue == key) {
				matchesList.insertToEnd(nextUniversity);

				if (nextUniversityNode->next != NULL) {
					nextUniversityNode = nextUniversityNode->next;
					nextUniversity = nextUniversityNode->data;
					nodeValue = nextUniversity.getUniversityNumValue(criteria);
				}

				else {
					break;
				}
			}

			Node<University>* prevUniversityNode = node->prev;
			University prevUniversity = prevUniversityNode->data;
			nodeValue = prevUniversity.getUniversityNumValue(criteria);

			while (nodeValue == key) {
				matchesList.insertToEnd(prevUniversity);

				if (prevUniversityNode->prev != NULL) {
					prevUniversityNode = prevUniversityNode->prev;
					prevUniversity = prevUniversityNode->data;
					nodeValue = prevUniversity.getUniversityNumValue(criteria);
				}

				else {
					break;
				}
			}

			return matchesList;
		}

		// nodeValue < key
		else if (nodeValue < key) {
			low = mid + 1;
		}

		// nodeValue > key
		else {
			high = mid - 1;
		}
	}

	return matchesList;
}

//template<class T >
//Node<T>* LinkedList<T>::binarySearch(T key) {
//	// get the size of linked list
//	int size = this->getSize();
//
//	// if the linked list is empty
//	if (size == 0) {
//		return NULL;
//	}
//
//	// set boundaries (low: the first index, high: the last index)
//	int low = 0;
//	int high = size - 1;
//
//	while (low <= high) {
//		// find the middle
//		int mid = (low + high) / 2;
//
//		Node<T>* node = this->getFromPosition(mid);
//		string nodeValue = node->data.getName();
//
//		// found
//		if (nodeValue == key.getName()) {
//			return node;
//		}
//
//		// nodeValue < key
//		else if (nodeValue < key.getName()) {
//			low = mid + 1;
//		}
//
//		// nodeValue > key
//		else {
//			high = mid - 1;
//		}
//	}
//
//	// not found
//	return NULL;
//}

//template<class T>
//Node<T>* LinkedList<T>::jumpSearch(T key) {
//	int n = 0;
//	Node<T>* curr = head;
//
//	while (curr != nullptr) {
//		n++;
//		curr = curr->next;
//	}
//
//	int jump = sqrt(n);
//	curr = head;
//	Node<T>* prev = nullptr;
//
//	while (curr != nullptr && curr->data.getName() < key.getName()) {
//		prev = curr;
//		for (int i = 0; i < jump && curr != nullptr; i++) {
//			curr = curr->next;
//		}
//	}
//
//	while (prev != nullptr && prev->data.getName() < key.getName()) {
//		prev = prev->next;
//	}
//
//	if (prev != nullptr && prev->data.getName() == key.getName()) {
//		return prev;
//	}
//
//	return nullptr;
//}

//Display univeristy values in the linked list
template<>
bool LinkedList<University>::display(int min, int max) {

	if (min > size) {
		cout << "No universities in the list!" << endl;
		return true;
	}

	Node<University>* current = head;
	int count = 1;

	//Display header
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
			university.display();
			count++;
		}

		current = current->next;
	}

	return false;
}

//Insertion sort to sort by criteria in ascending or descending order
template<>
void LinkedList<University>::insertionSort(Criteria criteria, bool isAscOrder) {

	Node<University>* current;
	Node<University>* temp;

	for (int i = 1; i < size; i++) {
		int index = i;

		//Get current node
		current = getFromPosition(index);

		//Get previous node
		temp = getFromPosition(index - 1);

		//Get data from nodes
		University currentUniversity = current->data;
		University tempUniversity = temp->data;

		//If criteria is name, location code, or location
		if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
			//Get the string value of the criteria of the university
			string stringValue1 = toUpperCase(currentUniversity.getUniversityStringValue(criteria));
			string stringValue2 = toUpperCase(tempUniversity.getUniversityStringValue(criteria));

			//Sort by ascending order
			if (isAscOrder) {
				//If the next node has a larger value than the current node
				while (index > 0 && stringValue2 > stringValue1) {
					swapNodePosition(current, temp);

					index -= 1;

					//Get the values from the sorted part to perform comparison
					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					stringValue1 = toUpperCase(university1.getUniversityStringValue(criteria));
					stringValue2 = toUpperCase(university2.getUniversityStringValue(criteria));
				}
			}

			//Sort by descending order
			else {
				//If the current node has a larger value than the next node
				while (index > 0 && stringValue1 > stringValue2) {
					swapNodePosition(current, temp);

					index -= 1;

					//Get the values from the sorted part to perform comparison
					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					stringValue1 = toUpperCase(university1.getUniversityStringValue(criteria));
					stringValue2 = toUpperCase(university2.getUniversityStringValue(criteria));
				}
			}
		}

		//If the criteria is the total number of favourites for the university
		else if (criteria == TOTAL_FAV_NUM) {
			int numValue1 = currentUniversity.getTotalFavNum();
			int numValue2 = tempUniversity.getTotalFavNum();

			while (index > 0 && numValue2 < numValue1) {
				swapNodePosition(current, temp);

				index -= 1;

				//Get the values from the sorted part to perform comparison
				current = getFromPosition(index);
				temp = getFromPosition(index - 1);

				University university1 = current->data;
				University university2 = temp->data;

				numValue1 = university1.getTotalFavNum();
				numValue2 = university2.getTotalFavNum();
			}
		}

		else {
			double numValue1 = currentUniversity.getUniversityNumValue(criteria);
			double numValue2 = tempUniversity.getUniversityNumValue(criteria);

			if (numValue1 == 0) {
				numValue1 = 701;
			}

			if (numValue2 == 0) {
				numValue2 = 701;
			}

			//Sort by ascending order
			if (isAscOrder) {
				while (index > 0 && numValue2 >= numValue1) {

					swapNodePosition(current, temp);

					index -= 1;

					//Get the values from the sorted part to perform comparison
					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					numValue1 = university1.getUniversityNumValue(criteria);
					numValue2 = university2.getUniversityNumValue(criteria);

					//Validation for universities that do not have a rank
					if (numValue1 == 0) {
						numValue1 = 701;
					}

					if (numValue2 == 0) {
						numValue2 = 701;
					}
				}
			}

			//Sort by descending order
			else {
				while (index > 0 && numValue1 >= numValue2) {

					swapNodePosition(current, temp);

					index -= 1;

					//Get the values from the sorted part to perform comparison
					current = getFromPosition(index);
					temp = getFromPosition(index - 1);

					University university1 = current->data;
					University university2 = temp->data;

					numValue1 = university1.getUniversityNumValue(criteria);
					numValue2 = university2.getUniversityNumValue(criteria);

					//Validation for universities that do not have a rank
					if (numValue1 == 0) {
						numValue1 = 701;
					}

					if (numValue2 == 0) {
						numValue2 = 701;
					}
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

		//Sort the values to the left of the index
		quickSortRecursive(criteria, isAscOrder, firstIndex, index - 1);

		//Sort the values to the right of the index
		quickSortRecursive(criteria, isAscOrder, index + 1, lastIndex);
	}
}

template<>
int LinkedList<University>::partition(Criteria criteria, bool isAscOrder, int firstIndex, int lastIndex) {

	//Set the last element as the pivot point
	Node<University>* pivot = getFromPosition(lastIndex);

	University pivotUniversity = pivot->data;
	string pivotStringValue = "", currentStringValue = "";
	double pivotNumValue = 0, currentNumValue = 0;

	int index = firstIndex - 1;

	for (int i = firstIndex; i <= lastIndex - 1; i++) {
		//Get the university from the current node
		Node<University>* current = getFromPosition(i);
		University currentUniversity = current->data;

		//If the criteria is name, location code or location
		if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
			pivotStringValue = pivotUniversity.getUniversityStringValue(criteria);
			currentStringValue = currentUniversity.getUniversityStringValue(criteria);

			//Sort by ascending order
			if (isAscOrder) {

				if (currentStringValue < pivotStringValue) {
					index++;

					Node<University>* temp = getFromPosition(index);
					swapNodePosition(current, temp);
				}
			}

			//Sort by descending order
			else {
				if (currentStringValue > pivotStringValue) {
					index++;
					swapNodePosition(current, getFromPosition(index));
				}
			}
		}

		//If criteria is total favourites for a university
		else if (criteria == TOTAL_FAV_NUM) {
			pivotNumValue = pivotUniversity.getTotalFavNum();
			currentNumValue = currentUniversity.getTotalFavNum();

			if (currentNumValue > pivotNumValue) {
				index++;
				swapNodePosition(current, getFromPosition(index));
			}
		}

		else {
			pivotNumValue = pivotUniversity.getUniversityNumValue(criteria);
			currentNumValue = currentUniversity.getUniversityNumValue(criteria);

			//Validate for universities without ranks
			if (pivotNumValue == 0) {
				pivotNumValue = 701;
			}

			if (currentNumValue == 0) {
				currentNumValue = 701;
			}

			//Sort by ascending order
			if (isAscOrder) {

				if (currentNumValue < pivotNumValue) {
					index++;
					swapNodePosition(current, getFromPosition(index));
				}
			}

			//Sort by descending order
			else {
				if (currentNumValue > pivotNumValue) {
					index++;
					swapNodePosition(current, getFromPosition(index));
				}
			}
		}
	}

	//Swap the index node with the pivot node
	swapNodePosition(getFromPosition(index + 1), getFromPosition(lastIndex));
	return index + 1;
}

//Change the string into upper case
template<class T>
string LinkedList<T>::toUpperCase(string value) {

	string newString = "";

	//Loop through all characters in the string
	for (int i = 0; i < value.size(); i++) {
		char c = value[i];
		c = toupper(c);
		newString += c;
	}

	return newString;
}
#endif