/*#include<iostream>
#include "HashTable.h"
using namespace std;

int HashTableMain(int argc, char** argv) {
	hashTable hash;
	string name = "";

	hash.addUserAcc("Paul", "Locha", "Customer");
	hash.addUserAcc("Kim", "Iced Mocha", "Customer");
	hash.addUserAcc("Annie", "Passion tea", "MoHE");
	hash.addUserAcc("Sarah", "Chai tea", "Customer");
	hash.addUserAcc("Eleven", "Apple cider", "MoHE");
	hash.addUserAcc("Emma", "Hot Mocha", "MoHE");
	hash.addUserAcc("Bill", "Root bear", "Customer");
	hash.addUserAcc("Susan", "Skinny Latte", "Customer");
	hash.addUserAcc("Marie", "Water", "Customer");
	hash.addUserAcc("Joe", "Green Tea", "Customer");
	hash.addUserAcc("Max", "Caramel mocha", "Customer");

	hash.printTable();
	//hash.printItemsInIndex(2);

	while (name != "exit") {
		cout << "Search for ";
		cin >> name;
		if (name != "exit") {
			hash.updatePwd(name);
		}
	}

	return 0;
}
*/