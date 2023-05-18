#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <iostream>

using namespace std;

enum Criteria {
	RANK,
	NAME,
	LOCATION_CODE,
	LOCATION,
	ARSCORE,
	ARRANK,
	ERSCORE,
	ERRANK,
	FSRSCORE,
	FSRRANK,
	CPFSCORE,
	CPFRANK,
	IFRSCORE,
	IFRRANK,
	ISRSCORE,
	ISRRANK,
	IRNSCORE,
	IRNRANK,
	GERSCORE,
	GERRANK,
	SCORE_SCALED
};

class University {
private:
	int rank;
	string name, locationCode, location;
	double arScore, erScore, fsrScore, cpfScore, ifrScore, isrScore, irnScore, gerScore, scoreScaled;
	int arRank, erRank, fsrRank, cpfRank, ifrRank, isrRank, irnRank, gerRank;
public:
	University();
	University(int, string, string, string, double, int, double, int, double, int, double, int, double,
		int, double, int, double, int, double, int, double);
	void display();
	void display(Criteria);
	void displayUniversitySummarized();
	string getUniversityStringValue(Criteria);
	double getUniversityNumValue(Criteria);
	void setName(string name);
	int getRank() { return rank; }
	string getName() { return name; }
	string getLocationCode() { return locationCode; }
	string getLocation() { return location; }
	double getArScore() { return arScore; }
	int getArRank() { return arRank; }
	double getErScore() { return erScore; }
	int getErRank() { return erRank; }
	double getFsrScore() { return fsrScore; }
	int getFsrRank() { return fsrRank; }
	double getCpfScore() { return cpfScore; }
	int getCpfRank() { return cpfRank; }
	double getIfrScore() { return ifrScore; }
	int getIfrRank() { return ifrRank; }
	double getIsrScore() { return isrScore; }
	int getIsrRank() { return isrRank; }
	double getIrnScore() { return irnScore; }
	int getIrnRank() { return irnRank; }
	double getGerScore() { return gerScore; }
	int getGerRank() { return gerRank; }
	double getScoreScaled() { return scoreScaled; }
};

#endif