#include<iostream>
#include "HashTable.h"
using namespace std;

int HashTableMain(/*int argc, char** argv*/) {
	hashTable hash;
	string name = "";

	hash.addUserAcc("Paul", "Locha");
	hash.addUserAcc("Kim", "Iced Mocha");
	hash.addUserAcc("Annie", "Passion tea");
	hash.addUserAcc("Sarah", "Chai tea");
	hash.addUserAcc("Eleven", "Apple cider");
	hash.addUserAcc("Emma", "Hot Mocha");
	hash.addUserAcc("Bill", "Root bear");
	hash.addUserAcc("Susan", "Skinny Latte");
	hash.addUserAcc("Marie", "Water");
	hash.addUserAcc("Joe", "Green Tea");
	hash.addUserAcc("Max", "Caramel mocha");

	hash.printTable();
	//hash.printItemsInIndex(2);

	/*while (name != "exit") {
		cout << "Search for ";
		cin >> name;
		if (name != "exit") {
			hash.updatePwd(name);
		}
	}*/

	return 0;
}