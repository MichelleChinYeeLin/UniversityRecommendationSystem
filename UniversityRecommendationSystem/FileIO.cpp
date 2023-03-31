#include "LinkedList.h"
#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

UniList FileIO::readUniversityFile() {
	UniList uniList = UniList();
	ifstream file("2023 QS World University Rankings.csv");
	
	string rank;
	string name, locationCode, location;
	string arScore, erScore, fsrScore, cpfScore, ifrScore, isrScore, irnScore, gerScore, scoreScaled;
	string arRank, erRank, fsrRank, cpfRank, ifrRank, isrRank, irnRank, gerRank;

	while (file.good()) {
		getline(file, rank, ',');

		if (rank == "Rank") {
			getline(file, rank);
			continue;
		}
		else if (rank == "") {
			break;
		}

		getline(file, name, ',');
		getline(file, locationCode, ',');
		getline(file, location, ',');
		getline(file, arScore, ',');
		getline(file, arRank, ',');
		getline(file, erScore, ',');
		getline(file, erRank, ',');
		getline(file, fsrScore, ',');
		getline(file, fsrRank, ',');
		getline(file, cpfScore, ',');
		getline(file, cpfRank, ',');
		getline(file, ifrScore, ',');
		getline(file, ifrRank, ',');
		getline(file, isrScore, ',');
		getline(file, isrRank, ',');
		getline(file, irnScore, ',');
		getline(file, irnRank, ',');
		getline(file, gerScore, ',');
		getline(file, gerRank, ',');
		getline(file, scoreScaled);

		if (arRank == "501+") {
			arRank = "501";
		}
		if (erRank == "501+") {
			erRank = "501";
		}
		if (fsrRank == "601+") {
			fsrRank = "601";
		}
		if (cpfRank == "601+") {
			cpfRank = "601";
		}
		if (ifrRank == "601+") {
			ifrRank = "601";
		}
		if (isrRank == "601+") {
			isrRank = "601";
		}
		if (irnRank == "601+") {
			irnRank = "601";
		}
		if (gerRank == "601+") {
			gerRank = "601";
		}
		if (scoreScaled == "-") {
			scoreScaled = "0";
		}

		uniList.insertToEnd(stoi(rank), name, locationCode, location, stod(arScore), stoi(arRank), stod(erScore), stoi(erRank),
			stod(fsrScore), stoi(fsrRank), stod(cpfScore), stoi(cpfRank), stod(ifrScore), stoi(ifrRank), stod(isrScore),
			stoi(isrRank), stod(irnScore), stoi(irnRank), stod(gerScore), stoi(gerRank), stod(scoreScaled));
	}

	return uniList;
}