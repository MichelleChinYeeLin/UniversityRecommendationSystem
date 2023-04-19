#ifndef FILEIO_H
#define FILEIO_H

#include "LinkedList.h"
//#include "University.h"
#include <iostream>

class FileIO {
public:
	LinkedList<University> readUniversityFile();
	string checkNameValue(ifstream&);
	string checkNumberValue(ifstream&, string);
};

#endif