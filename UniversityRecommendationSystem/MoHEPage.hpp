#ifndef MOHEPAGE_H
#define MOHEPAGE_H

#include <iostream>
#include"HashTable.hpp"
#include"FeedbackLinkedList.hpp"
using namespace std;

bool MoHELogin(hashTable* admin, hashTable* cus);
void MoHEMenu(hashTable* cus);
void displayUserDetails(hashTable* cus);
void modifyUserDetails(hashTable* cus);
void deleteUserAccounts(hashTable* cus);
void readFeedback(FeedbackLinkedList* admin);
void replyFeedback();

#endif