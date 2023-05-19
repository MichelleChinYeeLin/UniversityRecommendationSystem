#include<iostream>
#include "HashTable.hpp"
using namespace std;

//int main(/*int argc, char** argv*/) {
//	hashTable hash;
//	string name = "";
//
//	hash.addUserAcc("Paul", "Locha");
//	hash.addUserAcc("Kim", "Iced Mocha");
//	hash.addUserAcc("Annie", "Passion tea");
//	hash.addUserAcc("Sarah", "Chai tea");
//	hash.addUserAcc("Eleven", "Apple cider");
//	hash.addUserAcc("Emma", "Hot Mocha");
//	hash.addUserAcc("Bill", "Root bear");
//	hash.addUserAcc("Susan", "Skinny Latte");
//	hash.addUserAcc("Marie", "Water");
//	hash.addUserAcc("Joe", "Green Tea");
//	hash.addUserAcc("Max", "Caramel mocha");
//
//	hash.printTable();
//	//hash.printItemsInIndex(2);
//
//	/*while (name != "exit") {
//		cout << "Search for ";
//		cin >> name;
//		if (name != "exit") {
//			hash.updatePwd(name);
//		}
//	}*/
//
//	return 0;
//}

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

void hashTable::addUserAcc(string username, string password) {
	int hashValue = hash(username); //hash the username

	// if it is empty
	if (hash_Table[hashValue]->userName == "empty") {
		hash_Table[hashValue]->userName = username;
		hash_Table[hashValue]->password = password;
		// handle collision
	}
	else {
		user* ptr = hash_Table[hashValue];
		user* newUser = new user;
		newUser->userName = username;
		newUser->password = password;
		newUser->next = NULL;

		//tranversal until last item
		while (ptr->next != NULL) {
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
		while (ptr->next != NULL) {
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

void hashTable::printTable() {
	int number;

	for (int i = 0; i < tableSize; i++) {
		number = numberOfItemsInIndex(i);
		cout << "-------------------------\n";
		cout << "index = " << i << endl;
		cout << hash_Table[i]->userName << endl;
		cout << hash_Table[i]->password << endl;
		//cout << "# of users = " << number << endl;
		cout << "-------------------------\n";
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

string hashTable::searchForUsername(string username) {
	int hashValue = hash(username);
	bool found = false;
	string userName;
	string password;

	user* ptr = hash_Table[hashValue]; //pointing to the first item in the bucket
	while (ptr != NULL) {
		if (ptr->userName == username) {
			found = true;
			userName = ptr->userName;
			password = ptr->password;
		}
		ptr = ptr->next;
	}

	if (found == true) {
		cout << "------------------\n";
		cout << "User " << username << " was in the hash table\n";
		cout << "------------------\n";
	}
	else {
		cout << "------------------\n";
		cout << "User " << username << " was not found in the hash table\n";
		cout << "------------------\n";
	}
	return password;
}

void hashTable::removeInactiveAccount() {

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