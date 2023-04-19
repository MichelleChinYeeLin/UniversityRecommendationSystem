#include "FileIO.h"
//#include "LinkedList.h"
//#include "University.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

LinkedList<University> FileIO::readUniversityFile() {
	LinkedList<University> uniList;
	ifstream file("2023 QS World University Rankings.csv");
	
	string rank;
	string name, locationCode, location;
	double arScore, erScore, fsrScore, cpfScore, ifrScore, isrScore, irnScore, gerScore, scoreScaled;
	int arRank, erRank, fsrRank, cpfRank, ifrRank, isrRank, irnRank, gerRank;
	int count = 0;

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
			for (int i = 0; i < 20; i++) {
				string temp;

				if (i == 0 || i == 2) {
					char test;
					file.get(test);

					if (test == '"') {
						getline(file, line, '"');
						temp = line;
						temp += checkNameValue(file);
					}

					else {
						int num = file.tellg();
						file.seekg(num - 1);
						getline(file, temp, ',');
					}
				}

				else if (i == 19) {
					getline(file, temp);
				}

				else {
					getline(file, temp, ',');
				}

				
				temp = checkNumberValue(file, temp);

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

		University newUniversity(stoi(rank), name, locationCode, location, arScore, arRank,
			erScore, erRank, fsrScore, fsrRank, cpfScore, cpfRank,
			ifrScore, ifrRank, isrScore, isrRank, irnScore, irnRank, gerScore, gerRank, scoreScaled);

		uniList.insertToEnd(newUniversity);
	}

	return uniList;
}

string FileIO::checkNameValue(ifstream& file) {

	char temp;
	string value;
	file.get(temp);

	while (temp == '"') {
		getline(file, value, '"');
		file.get(temp);
	}

	int num = file.tellg();
	file.seekg(num + 1);

	return value;
}

string FileIO::checkNumberValue(ifstream& file, string value) {
	if (value == "501+") {
		return "501";
	}
	else if (value == "601+") {
		return "601";
	}
	else if (value == "-" || value == "") {
		return "0";
	}

	return value;
}