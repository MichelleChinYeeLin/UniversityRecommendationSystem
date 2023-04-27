#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <iostream>
#include <string>
#include <ctime>
#include "FileIO.h"
#include"HashTable.hpp"
#include"FeedbackLinkedList.hpp"
#include "University.h"

using namespace std;

void customerMenu(FeedbackLinkedList* cus, string username);
void displayUniversityList();
void registerAsUser(hashTable* cus);
void writeFeedback(string username,FeedbackLinkedList * cus);

#endif