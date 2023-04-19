#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <iostream>

using namespace std;

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
	//void createUniversity(int, string, string, string, double, int, double, int, double, int, double, int, double,
		//int, double, int, double, int, double, int, double);
	void displayUniversitySummarized();
};

#endif