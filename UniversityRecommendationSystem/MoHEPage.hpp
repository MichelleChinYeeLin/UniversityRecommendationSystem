#ifndef MOHEPAGE_H
#define MOHEPAGE_H

#include <iostream>
#include"HashTable.hpp"
#include"FeedbackLinkedList.hpp"
using namespace std;

void MoHEMenu(hashTable* cus, FeedbackLinkedList* cus1);
void displayUserDetails(hashTable* cus);
void modifyUserDetails(hashTable* cus);
void deleteUserAccounts(hashTable* cus);
void readFeedback(FeedbackLinkedList* admin);
void replyFeedback();

#endif