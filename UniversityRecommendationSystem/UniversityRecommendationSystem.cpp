#include "LinkedList.h"
#include "FileIO.h"
#include "University.h"
#include <iostream>
#include <limits>
using namespace std;

//Function prototypes
bool customerLogin();
void customerMenu();
void displayUniversityList();

LinkedList<University> uniList;

int main() {
	
	FileIO fileIO;
	uniList = fileIO.readUniversityFile();
	
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
			valid = customerLogin();

			if (valid) {
				customerMenu();
				valid = false;
			}
		}

		else if (input == 2) {
			//TODO: MoHE Login
			system("pause");
			system("cls");
		}

		else if (input == 3) {
			system("cls");
			
			displayUniversityList();

			//system("pause");
			system("cls");
		}

	} while (input != 4 || !valid);
	
	return 0;
}

void displayUniversityList() {

	int min = 1;
	int max = 100;
	string input = "";

	do {
		uniList.displayList(min, max);
		cout << "Continue? Enter 'Y' to continue displaying list: ";
		cin >> input;

		if (input == "Y") {
			min += 100;
			max += 100;
			system("cls");
		}

	} while (input == "Y");
}

bool customerLogin() {
	string username = "", password = "";
	bool valid = true;

	cout << "Username: ";
	cin >> username;

	cin.clear();
	cin.ignore();

	//TODO: Loop through list of users
	while (false) {

		//If user found
		cout << "Password: ";
		cin >> password;
		//If password ==, return true

		system("cls");
	}

	cout << "Invalid username! Please try again." << endl;
	system("pause");
	system("cls");

	return false;
}

void customerMenu() {
	int input = 0;
	bool valid = false;

	//Display menu
	do {
		cout << "1. Sort University Information" << endl;
		cout << "2. Search University" << endl;
		cout << "3. View Favorite Universities" << endl;
		cout << "4. View Feedback" << endl;
		cout << "5. Logout" << endl;
		cout << "Enter option: ";
		cin >> input;

		if (cin.fail() || input < 1 || input > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}
		else if (input == 1) {

		}
		else if (input == 2) {

		}
		else if (input == 3) {

		}
		else if (input == 4) {

		}
	} while (input != 5 || !valid);
}