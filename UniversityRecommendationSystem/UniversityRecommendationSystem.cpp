//#include "LinkedList.h"
#include "FileIO.h"
//#include "University.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

//Function prototypes
bool customerLogin();
void customerMenu();
void displayUniversityList(bool);
void addFavouriteUniversity(int, int);

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
				system("cls");
			}
		}

		else if (input == 2) {
			//TODO: MoHE Login
			system("pause");
			system("cls");
		}

		else if (input == 3) {
			system("cls");
			uniList.insertionSort(RANK, true);
			displayUniversityList(false);

			system("pause");
			system("cls");
		}

	} while (input != 4 || !valid);
	
	return 0;
}

void displayUniversityList(bool hasFav) {

	int min = 1;
	int max = 100;
	string input = "";
	bool endOfList = false;

	do {
		endOfList = uniList.display(min, max);

		if (endOfList) {
			cout << "End of University List!" << endl;
			system("pause");
		}

		else {

			if (hasFav) {
				cout << "Continue? Enter 'Y' to continue displaying list or 'F' to favourite a university: ";
				cin >> input;
			}

			else {
				cout << "Continue? Enter 'Y' to continue displaying list: ";
				cin >> input;
			}

			if (input == "F") {
				addFavouriteUniversity(min, max);
				system("cls");
			}

			else if (input == "Y") {
				min += 100;
				max += 100;
				system("cls");
			}
		}

	} while ((input == "Y" && !endOfList) || input == "F");
}

void addFavouriteUniversity(int min, int max) {

	bool valid = true;
	int favNum = 0;
	string input = "";

	do {
		valid = true;
		uniList.display(min, max);

		cout << "Enter the No. of the university to be added to favourites (Enter -1 to cancel): ";
		cin >> favNum;

		if (favNum == -1) {
			return;
		}

		else if (cin.fail() || favNum > max || favNum < min) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "The number entered is not a university currently displayed." << endl;
			cout << "Add to favourites anyway? Enter 'Y' to confirm: ";
			cin >> input;

			if (input != "Y") {
				valid = false;
				system("cls");
			}
		}
	} while (!valid);

	Node<University>* favNode = uniList.getFromPosition(favNum - 1);
	University favUni = favNode->data;

	//TODO: add university to user data

	cout << endl << favUni.getName() << " has been added to favourites!" << endl;
	system("pause");
}

bool customerLogin() {
	//temp
	return true;

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
		valid = true;

		cout << "1. Sort University Information" << endl;
		cout << "2. Search University" << endl;
		cout << "3. View Favorite Universities" << endl;
		cout << "4. View Feedback" << endl;
		cout << "5. Logout" << endl;
		cout << "Enter option: ";
		cin >> input;

		system("cls");

		if (cin.fail() || input < 1 || input > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}
		else if (input == 1) {

			int categoryInput = 0;

			cout << "1.  Rank" << endl;
			cout << "2.  Institution Name" << endl;
			cout << "3.  Location Code" << endl;
			cout << "4.  Location" << endl;
			cout << "5.  Academic Reputation (AR)" << endl;
			cout << "6.  Employer Reputation (ER)" << endl;
			cout << "7.  Faculty/Student Ratio (FSR)" << endl;
			cout << "8.  Citations Per Faculty (CPF)" << endl;
			cout << "9.  International Faculty Ratio (IFR)" << endl;
			cout << "10. International Student Ratio (ISR)" << endl;
			cout << "11. International Research Network (IRN)" << endl;
			cout << "12. Employment Outcome (GER)" << endl;
			cout << "Select category to sort: ";
			cin >> categoryInput;

			if (cin.fail() || categoryInput < 1 || categoryInput > 12) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Invalid option! Please try again!" << endl;
				system("pause");
				system("cls");
				valid = false;
			}

			else {
				Criteria criteria;

				switch (categoryInput) {
				case 1:
					criteria = RANK;
					break;
				case 2:
					criteria = NAME;
					break;
				case 3:
					criteria = LOCATION_CODE;
					break;
				case 4:
					criteria = LOCATION;
					break;
				case 5:
					criteria = ARRANK;
					break;
				case 6:
					criteria = ERRANK;
					break;
				case 7:
					criteria = FSRRANK;
					break;
				case 8:
					criteria = CPFRANK;
					break;
				case 9:
					criteria = IFRRANK;
					break;
				case 10:
					criteria = ISRRANK;
					break;
				case 11:
					criteria = IRNRANK;
					break;
				case 12:
					criteria = GERRANK;
					break;
				}

				int orderOption = 0;

				cout << endl << endl;
				cout << "1. Ascending order" << endl;
				cout << "2. Descending order" << endl;
				cout << "Enter option: ";
				cin >> orderOption;

				if (cin.fail() || (orderOption != 1 && orderOption != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Invalid option! Please try again!" << endl;
					system("pause");
					system("cls");
					valid = false;
				}

				else {
					bool isAscOrder = orderOption == 1 ? true : false;
					//uniList.insertionSort(criteria, isAscOrder);
					uniList.quickSort(criteria, isAscOrder);
					displayUniversityList(true);

					system("pause");
					system("cls");
				}
			}
		}
		else if (input == 2) {

		}
		else if (input == 3) {

		}
		else if (input == 4) {

		}
	} while (input != 5 || !valid);
}