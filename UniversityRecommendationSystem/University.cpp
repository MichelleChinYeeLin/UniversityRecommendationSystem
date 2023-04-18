#include "University.h"
#include <iostream>

using namespace std;

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
