#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>

using namespace std;

class hashTable {
private:
	static const int tableSize = 10;
	typedef struct user {
		string userName;
		string password;
		user* next;
	};user* hash_Table[tableSize]; 
	// bucket to store pointers of linked list

public:
	hashTable();
	int hash(string username);
	void addUserAcc(string username, string password);
	int numberOfItemsInIndex(int index);
	void printTable();
	void printItemsInIndex(int index);
	string searchForUsername(string username);
	void removeUserAcc(string username);
	int updatePwd(string username);
	void removeInactiveAccount();
};

#endif