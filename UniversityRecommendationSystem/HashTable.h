#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

struct user {
	string userName;
	string password;
	string accType;
	time_t lastActiveTime;
	LinkedList<University> favUniList;
	user* next;
};

class hashTable {
private:
	static const int tableSize = 10;

	user* hash_Table[tableSize]; // bucket to store pointers of linked list

public:
	hashTable();
	int hash(string username);
	void addUserAcc(string username, string password, string accType, time_t lastActiveTime);
	int numberOfItemsInIndex(int index);
	void printTable();
	void printItemsInIndex(int index);
	user* searchUser(string username);
	void removeUserAcc(string username);
	int updatePwd(string username);
	void deleteInactiveAccounts();
};

hashTable::hashTable() {
	for (int i = 0; i < tableSize; i++) {
		hash_Table[i] = new user;
		hash_Table[i]->userName = "empty";
		hash_Table[i]->password = "empty";
		hash_Table[i]->next = NULL;
	}
}

int hashTable::hash(string key) {
	int hash = 0;
	int index;
	for (int i = 0; i < key.length(); i++) {
		hash += (int)key[i];
	}
	index = hash % tableSize;
	return index;
}

void hashTable::addUserAcc(string username, string password, string accType, time_t lastActiveTime) {
	int hashValue = hash(username); //hash the username

	// if it is empty
	if (hash_Table[hashValue]->userName == "empty") {
		hash_Table[hashValue]->userName = username;
		hash_Table[hashValue]->password = password;
		hash_Table[hashValue]->accType = accType;
		hash_Table[hashValue]->lastActiveTime = lastActiveTime;
		// handle collision
	}
	else {
		user* ptr = hash_Table[hashValue];
		user* newUser = new user;
		newUser->userName = username;
		newUser->password = password;
		newUser->accType = accType;
		newUser->lastActiveTime = lastActiveTime;
		newUser->next = nullptr;

		//tranversal until last item
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = newUser; // link the new item to the end of the linked list
	}
}

int hashTable::numberOfItemsInIndex(int index) {
	int count = 0;

	if (hash_Table[index]->userName == "empty") {
		return count;
	}
	else {
		user* ptr = hash_Table[index];
		while (/*ptr->next != NULL*/ ptr != nullptr) {
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

//void hashTable::printTable() {
//	int number;
//
//	for (int i = 0; i < tableSize; i++) {
//		number = numberOfItemsInIndex(i);
//		cout << "-------------------------\n";
//		cout << "index = " << i << endl;
//		cout << hash_Table[i]->userName << endl;
//		cout << hash_Table[i]->password << endl;
//		//cout << "# of users = " << number << endl;
//		//cout << "-------------------------\n";
//	}
//}

void hashTable::printTable() {
	for (int i = 0; i < tableSize; i++) {
		cout << "-------------------------\n";
		cout << "index = " << i << endl;

		user* ptr = hash_Table[i];
		while (ptr != nullptr && ptr->userName != "empty") {
			cout << ptr->userName << endl;
			cout << ptr->password << endl;
			ptr = ptr->next;
		}
	}
}


void hashTable::printItemsInIndex(int index) {
	user* ptr = hash_Table[index];

	if (ptr->userName == "empty") {
		cout << "Bucket = " << index << " is empty";
	}
	else {
		cout << "Bucket " << index << " contains the following item\n";
		while (ptr != NULL) {
			cout << "------------------\n";
			cout << ptr->userName << endl;
			cout << ptr->password << endl;
			cout << "------------------\n";
			ptr = ptr->next;
		}
	}
}

user* hashTable::searchUser(string username) {
	int hashValue = hash(username);
	//bool found = false;
	string userName;

	user* ptr = hash_Table[hashValue]; //pointing to the first item in the bucket
	while (ptr != NULL) {
		if (ptr->userName == username) {
			//found = true;
			//cout << "------------------\n";
			//cout << "User " << username << " was in the hash table\n";
			//cout << "------------------\n";
			return ptr;

			//return true;
		}
		ptr = ptr->next;
	}

	user* emptyUser = new user;
	emptyUser->userName = "";

	return emptyUser;

	//cout << "------------------\n";
	//cout << "User " << username << " was not found in the hash table\n";
	//cout << "------------------\n";

	/*if (found == true) {
		cout << "------------------\n";
		cout << "User " << username << " was in the hash table\n";
		cout << "------------------\n";
	}
	else {
		cout << "------------------\n";
		cout << "User " << username << " was not found in the hash table\n";
		cout << "------------------\n";
	}
	return username;*/
}

void hashTable::removeUserAcc(string username) {
	int index = hash(username);
	user* delPtr;
	user* P1;
	user* P2;

	//case 0: bucket is empty
	if (hash_Table[index]->userName == "empty" && hash_Table[index]->password == "empty") {
		cout << username << " was not found in the hash table\n";
		//case 1: only 1 item contained in bucket and that item has matching name
	}
	else if (hash_Table[index]->userName == username && hash_Table[index]->next == NULL) {
		hash_Table[index]->userName = "empty";
		hash_Table[index]->password = "empty";
		cout << username << " was removed from the hash table\n";
		//case 2: match is located in the first item in the bucket but there are more items in the bucket
	}
	else if (hash_Table[index]->userName == username) {
		delPtr = hash_Table[index];
		hash_Table[index] = hash_Table[index]->next;
		delete delPtr;
		cout << username << " was removed from the hash table\n";
		//case 3: bukcet contains items but first item is not a match
	}
	else {
		P1 = hash_Table[index]->next;
		P2 = hash_Table[index];

		while (P1 != NULL && P1->userName != username) {
			P2 = P1;
			P1 = P1->next;
		}

		//case 3.1: no match
		if (P1 == NULL) {
			cout << username << " was not found in the hash table\n";
			//case 3.2: match is found
		}
		else {
			delPtr = P1;
			P1 = P1->next;
			P2->next = P1;
			delete delPtr;
			cout << username << " was removed from the hash table\n";
		}
	}
}

int hashTable::updatePwd(string username) {
	int index = hash(username);
	string newPw;

	//case 0: bucket is empty
	if (hash_Table[index]->userName == "empty" && hash_Table[index]->password == "empty") {
		cout << username << " was not found in the hash table\n";
	}
	//case 1: the item has matching name
	else if (hash_Table[index]->userName == username) {
		cout << "Please enter new password: ";
		cin >> newPw;
		hash_Table[index]->password = newPw;
		cout << username << " was updated its password\n";
		cout << "The new password of " << username << " was " << newPw << "\n";
	}
	//case 3: match not found
	else {
		cout << username << " was not found in the hash table\n";
	}

	return index;
}

//LinkedList<University> hashTable::getFavUniList(string userName) {
//	int hashValue = hash(userName);
//
//	user* ptr = hash_Table[hashValue]; //pointing to the first item in the bucket
//	while (ptr != NULL) {
//		if (ptr->userName == userName) {
//			return ptr->favUniList;
//		}
//		ptr = ptr->next;
//	}
//
//	return LinkedList<University>();
//}

void hashTable::deleteInactiveAccounts() {
	time_t currentTime = time(nullptr);
	time_t oneYearAgo = currentTime - (365 * 24 * 60 * 60); // 1 year in seconds

	for (int i = 0; i < tableSize; i++) {
		user* currentUser = hash_Table[i];
		user* prevUser = nullptr;

		while (currentUser != nullptr) {
			if (currentUser->lastActiveTime <= oneYearAgo && currentUser->userName != "empty") {
				// Ask the admin for confirmation
				cout << "User " << currentUser->userName << " has been inactive for more than a year. Do you want to delete this account? (Y/N): ";
				string choice;
				cin >> choice;

				if (choice == "Y") {
					// Delete the inactive user account
					if (prevUser == nullptr) {
						// If it's the first element
						hash_Table[i] = currentUser->next;
						delete currentUser;
						currentUser = hash_Table[i];
					}
					else {
						// If it's not the first element
						prevUser->next = currentUser->next;
						delete currentUser;
						currentUser = prevUser->next;
					}
				}
				else {
					// Admin chose not to delete the account
					prevUser = currentUser;
					currentUser = currentUser->next;
				}
			}
			else {
				prevUser = currentUser;
				currentUser = currentUser->next;
			}
		}
	}
}

#endif