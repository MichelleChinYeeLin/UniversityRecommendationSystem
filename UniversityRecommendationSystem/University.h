#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <iostream>
#include <iomanip>

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

University::University() {
	this->rank = 0;
	this->name = "";
	this->locationCode = "";
	this->location = "";
	this->arScore = 0;
	this->arRank = 0;
	this->erScore = 0;
	this->erRank = 0;
	this->fsrScore = 0;
	this->fsrRank = 0;
	this->cpfScore = 0;
	this->cpfRank = 0;
	this->ifrScore = 0;
	this->ifrRank = 0;
	this->isrScore = 0;
	this->isrRank = 0;
	this->irnScore = 0;
	this->irnRank = 0;
	this->gerScore = 0;
	this->gerRank = 0;
	this->scoreScaled = 0;
}

University::University(int rank, string name, string locationCode, string location, double arScore, int arRank,
	double erScore, int erRank, double fsrScore, int fsrRank, double cpfScore, int cpfRank, double ifrScore,
	int ifrRank, double isrScore, int isrRank, double irnScore, int irnRank, double gerScore, int gerRank, double scoreScaled)
{
	this->rank = rank;
	this->name = name;
	this->locationCode = locationCode;
	this->location = location;
	this->arScore = arScore;
	this->arRank = arRank;
	this->erScore = erScore;
	this->erRank = erRank;
	this->fsrScore = fsrScore;
	this->fsrRank = fsrRank;
	this->cpfScore = cpfScore;
	this->cpfRank = cpfRank;
	this->ifrScore = ifrScore;
	this->ifrRank = ifrRank;
	this->isrScore = isrScore;
	this->isrRank = isrRank;
	this->irnScore = irnScore;
	this->irnRank = irnRank;
	this->gerScore = gerScore;
	this->gerRank = gerRank;
	this->scoreScaled = scoreScaled;
}

void University::display() {
	cout << left << setw(5) << this->rank << setw(90) << this->name << setw(10) << this->locationCode
		<< setw(30) << this->location << endl;
}

void University::display(Criteria criteria) {
	if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
		display();
	}

	else {
		int rank = 0;
		double score = 0;

		switch (criteria) {
		case ARRANK:
		case ARSCORE:
			rank = arRank;
			score = arScore;
			break;
		case ERRANK:
		case ERSCORE:
			rank = erRank;
			score = erScore;
			break;
		case FSRRANK:
		case FSRSCORE:
			rank = fsrRank;
			score = fsrScore;
			break;
		case CPFRANK:
		case CPFSCORE:
			rank = cpfRank;
			score = cpfScore;
			break;
		case IFRRANK:
		case IFRSCORE:
			rank = ifrRank;
			score = ifrScore;
			break;
		case ISRRANK:
		case ISRSCORE:
			rank = isrRank;
			score = isrScore;
			break;
		case IRNRANK:
		case IRNSCORE:
			rank = irnRank;
			score = irnScore;
			break;
		case GERRANK:
		case GERSCORE:
			rank = gerRank;
			score = gerScore;
			break;
		case RANK:
		case SCORE_SCALED:
			rank = rank;
			score = scoreScaled;
		}

		cout << left << setw(5) << rank << setw(90) << this->name << setw(5) << score << endl;
	}
}

void University::displayUniversitySummarized() {
	cout << left << setw(5) << this->rank << setw(90) << this->name << setw(10) << this->locationCode
		<< setw(30) << this->location << endl;
}

string University::getUniversityStringValue(Criteria criteria) {

	switch (criteria) {
	case NAME:
		return name;
		break;
	case LOCATION_CODE:
		return locationCode;
		break;
	case LOCATION:
		return location;
	}

	return "";
}

double University::getUniversityNumValue(Criteria criteria) {

	switch (criteria) {
	case RANK:
		return rank;
		break;
	case ARSCORE:
		return arScore;
		break;
	case ARRANK:
		return arRank;
		break;
	case ERSCORE:
		return erScore;
		break;
	case ERRANK:
		return erRank;
		break;
	case FSRSCORE:
		return fsrScore;
		break;
	case FSRRANK:
		return fsrRank;
		break;
	case CPFSCORE:
		return cpfScore;
		break;
	case CPFRANK:
		return cpfRank;
		break;
	case IFRSCORE:
		return ifrScore;
		break;
	case IFRRANK:
		return ifrRank;
		break;
	case ISRSCORE:
		return isrScore;
		break;
	case ISRRANK:
		return isrRank;
		break;
	case IRNSCORE:
		return irnScore;
		break;
	case IRNRANK:
		return irnRank;
		break;
	case GERSCORE:
		return gerScore;
		break;
	case GERRANK:
		return gerRank;
		break;
	case SCORE_SCALED:
		return scoreScaled;
	}

	return 0;
}

#endif