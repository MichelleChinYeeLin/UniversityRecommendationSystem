#include "LinkedList.h"
#include "FileIO.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
	
	FileIO fileIO;
	UniList uniList = fileIO.readUniversityFile();
	
	int input = 0;
	bool valid = true;

	//Display menu
	do {
		valid = true;

		cout << "1. Customer Login" << endl;
		cout << "2. MoHE Login" << endl;
		cout << "3. Display University Information" << endl;
		cout << "4. Quit" << endl;
		cout << "Enter option: ";
		cin >> input;
		cout << endl << endl;

		if (cin.fail() || input < 1 || input > 4) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}

		else if (input == 1) {
			system("pause");
			system("cls");
		}

		else if (input == 2) {
			system("pause");
			system("cls");
		}

		else if (input == 3) {
			system("cls");
			uniList.displayList();

			system("pause");
			system("cls");
		}

	} while (input != 4 || !valid);
	
	return 0;
}