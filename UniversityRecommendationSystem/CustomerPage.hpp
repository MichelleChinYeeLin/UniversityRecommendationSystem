#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <iostream>
#include <iomanip>
#include <limits>
#include "FileIO.h"
#include"HashTable.hpp"
#include "FileIO.h"
#include"LinkedList.h"
#include "University.h"

using namespace std;

bool customerLogin(hashTable* cus);
void customerMenu();
void displayUniversityList();
void registerAsUser(hashTable* cus);
void writeFeedback();

#endif