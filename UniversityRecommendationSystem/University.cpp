#include "University.h"
#include <iostream>
#include <iomanip>

using namespace std;

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

void University::displayUniversitySummarized() {
	cout << left << setw(5) << this->rank << setw(90) << this->name << setw(10) << this->locationCode 
		 << setw(30) << this->location << endl;
}