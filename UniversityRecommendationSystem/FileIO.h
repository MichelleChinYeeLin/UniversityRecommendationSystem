#ifndef FILEIO_H
#define FILEIO_H

//#include "LinkedList.h"
#include "HashTable.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>

class FileIO {
public:
	LinkedList<University> readUniversityFile();
	string checkNameValue(ifstream&);
	string checkNumberValue(ifstream&, string);
};

//Read the CSV file with the university data
LinkedList<University> FileIO::readUniversityFile() {
	//Create empty linked list
	LinkedList<University> uniList;

	//Open the CSV file for reading
	ifstream file("2023 QS World University Rankings.csv");

	//Declaration of variables
	string rank;
	string name, locationCode, location;
	double arScore, erScore, fsrScore, cpfScore, ifrScore, isrScore, irnScore, gerScore, scoreScaled;
	int arRank, erRank, fsrRank, cpfRank, ifrRank, isrRank, irnRank, gerRank;
	int count = 0;

	//Loop if end of file is not reached
	while (file.good()) {
		getline(file, rank, ',');

		//Check if its the first line
		if (rank == "Rank") {
			getline(file, rank);
			continue;
		}

		//Check if end of file
		else if (rank == "") {
			break;
		}

		count++;
		string line = "";

		try {

			//Loop through the other 20 comma delimited values
			for (int i = 0; i < 20; i++) {
				string temp;

				//If the value is name(i==0) or location(i==2)
				if (i == 0 || i == 2) {

					//Get the first char in the value
					char test;
					file.get(test);

					//Value requires formatting if the first char is '"'
					if (test == '"') {
						getline(file, line, '"');
						temp = line;
						temp += checkNameValue(file);
					}

					else {
						//Reset the file cursor to the first char of the value
						int num = file.tellg();
						file.seekg(num - 1);

						//Read the value
						getline(file, temp, ',');
					}
				}

				//If the value is the last value
				else if (i == 19) {
					//Read the value until end line
					getline(file, temp);
				}

				else {
					getline(file, temp, ',');
				}

				//Format the number values
				temp = checkNumberValue(file, temp);

				//Store the corresponding values in the variables
				switch (i) {
				case 0: name = temp;
					break;
				case 1: locationCode = temp;
					break;
				case 2: location = temp;
					break;
				case 3: arScore = stod(temp);
					break;
				case 4: arRank = stoi(temp);
					break;
				case 5: erScore = stod(temp);
					break;
				case 6: erRank = stoi(temp);
					break;
				case 7: fsrScore = stod(temp);
					break;
				case 8: fsrRank = stoi(temp);
					break;
				case 9: cpfScore = stod(temp);
					break;
				case 10: cpfRank = stoi(temp);
					break;
				case 11: ifrScore = stod(temp);
					break;
				case 12: ifrRank = stoi(temp);
					break;
				case 13: isrScore = stod(temp);
					break;
				case 14: isrRank = stoi(temp);
					break;
				case 15: irnScore = stod(temp);
					break;
				case 16: irnRank = stoi(temp);
					break;
				case 17: gerScore = stod(temp);
					break;
				case 18: gerRank = stoi(temp);
					break;
				case 19: scoreScaled = stod(temp);
				}
			}
		}
		catch (...) {
			cout << "Unexpected error. Please try again." << endl;
			system("pause");
			system("cls");
		}

		//Create University object
		University newUniversity(stoi(rank), name, locationCode, location, arScore, arRank,
			erScore, erRank, fsrScore, fsrRank, cpfScore, cpfRank,
			ifrScore, ifrRank, isrScore, isrRank, irnScore, irnRank, gerScore, gerRank, scoreScaled);

		//Insert University object into linked list
		uniList.insertToEnd(newUniversity);
	}

	return uniList;
}

//Check if the data has '"' (quotations)
string FileIO::checkNameValue(ifstream& file) {

	char temp;
	string value;
	//Get the next character in the file
	file.get(temp);

	while (temp == '"') {
		getline(file, value, '"');
		file.get(temp);
	}

	//Move the cursor forward by one character
	//To pass the ',' (comma)
	int num = file.tellg();
	file.seekg(num + 1);

	return value;
}

//Check the numerical data
string FileIO::checkNumberValue(ifstream& file, string value) {

	//If the data read is '501+'
	if (value == "501+") {
		return "501";
	}

	//If the data read is '601+'
	else if (value == "601+") {
		return "601";
	}

	//If the data is empty
	else if (value == "-" || value == "") {
		return "0";
	}

	return value;
}

#endif