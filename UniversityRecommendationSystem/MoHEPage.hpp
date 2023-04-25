#ifndef MOHEPAGE_H
#define MOHEPAGE_H

#include <iostream>
#include"HashTable.hpp"
#include"LinkedList.h"
using namespace std;

bool MoHELogin(hashTable* admin, hashTable* cus);
void MoHEMenu(hashTable* cus);
void displayUserDetails(hashTable* cus);
void modifyUserDetails(hashTable* cus);
void deleteUserAccounts(hashTable* cus);
void readFeedback();
void replyFeedback();

#endif