#include "FileIO.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

//Function prototypes
bool customerLogin();
void customerMenu();
bool moheLogin();
void moheMenu();
void displayUniversityList(bool, Criteria);
void addFavouriteUniversity(int, int);

hashTable addDemoData();

LinkedList<University> uniList;
hashTable userTable;
user* currentUser;

int main() {
	
	FileIO fileIO;
	uniList = fileIO.readUniversityFile();
	userTable = addDemoData();
	
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
			valid = moheLogin();

			if (valid) {
				moheMenu();
				valid = false;
				system("cls");
			}

			system("pause");
			system("cls");
		}

		else if (input == 3) {
			system("cls");
			uniList.insertionSort(RANK, true);
			displayUniversityList(false, NAME);
		}

	} while (input != 4 || !valid);
	
	return 0;
}

void displayUniversityList(bool hasFav, Criteria criteria) {

	int itemNum = 100;
	string input = "";
	
	Stack<University> nextStack;
	Stack<University> currentStack;
	Stack<University> prevStack;

	for (int i = uniList.getSize() - 1; i >= 0; i--) {
		nextStack.push(uniList.getFromPosition(i)->data);
	}

	int numCount = 1;

	do {

		//Display header
		cout << string(135, '=') << endl;
		if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
			cout << left << setw(5) << "No." << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
		}

		else {
			string rank;
			string score;

			switch (criteria) {
			case ARRANK:
			case ARSCORE:
				rank = "AR Rank";
				score = "AR Score";
				break;
			case ERRANK:
			case ERSCORE:
				rank = "ER Rank";
				score = "ER Score";
				break;
			case FSRRANK:
			case FSRSCORE:
				rank = "FSR Rank";
				score = "FSR Score";
				break;
			case CPFRANK:
			case CPFSCORE:
				rank = "CPF Rank";
				score = "CPF Score";
				break;
			case IFRRANK:
			case IFRSCORE:
				rank = "IFR Rank";
				score = "IFR Score";
				break;
			case ISRRANK:
			case ISRSCORE:
				rank = "ISR Rank";
				score = "ISR Score";
				break;
			case IRNRANK:
			case IRNSCORE:
				rank = "IRN Rank";
				score = "IRN Score";
				break;
			case GERRANK:
			case GERSCORE:
				rank = "GER Rank";
				score = "GER Score";
				break;
			case RANK:
			case SCORE_SCALED:
				rank = "Rank";
				score = "Score Scaled";
			}

			cout << left << setw(5) << "No." << setw(10) << rank << setw(90) << "Name" << setw(15) << score << endl;
		}
		cout << string(135, '=') << endl;

		int itemCount = 0;

		while(!nextStack.isEmpty() && itemCount < itemNum) {
			University university = nextStack.pop();
			currentStack.push(university);

			cout << left << setw(5) << numCount + itemCount;
			university.display(criteria);

			itemCount++;
		}

		if (hasFav) {
			cout << endl << "Enter 'P' to view previous page, 'N' to view next page, 'F' to favourite a university: ";
			cin >> input;

			if (input == "F") {
				addFavouriteUniversity(numCount, numCount + itemNum);
			}
		}

		else {
			cout << endl << "Enter 'P' to view previous page, 'N' to view next page: ";
			cin >> input;
		}

		if (input == "P") {

			while (!currentStack.isEmpty()) {
				University temp = currentStack.pop();
				nextStack.push(temp);
			}

			if (prevStack.isEmpty()) {

				cout << "Previous data does not exist!" << endl;
				system("pause");
			}

			else {
				int count = itemNum;

				while (!prevStack.isEmpty() && count > 0) {
					University temp = prevStack.pop();
					currentStack.push(temp);
					count--;
					numCount--;
				}

				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					nextStack.push(temp);
				}
			}
		}

		else if (input == "N") {

			if (nextStack.isEmpty()) {

				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					nextStack.push(temp);
				}

				cout << "Next data does not exist!" << endl;
				system("pause");
			}

			else {
				int count = itemNum;

				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					prevStack.push(temp);
					count--;
					numCount++;
				}
			}
		}

		system("cls");
	} while (input == "N" || input == "P" || input == "F");
}

void addFavouriteUniversity(int min, int max) {

	bool valid = true;
	int favNum = 0;
	string input = "";

	do {
		valid = true;
		//uniList.display(min, max);

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

	currentUser->favUniList.insertToEnd(favUni);

	cout << endl << favUni.getName() << " has been added to favourites!" << endl;
	system("pause");
}

bool customerLogin() {

	string username = "", password = "";
	bool valid = true;

	cout << "Username: ";
	cin >> username;

	cin.clear();
	cin.ignore();

	user* customer = userTable.searchUser(username);

	//If user is found
	if (customer->userName != "") {

		//If user account is a customer
		if (customer->accType == "Customer") {
			cout << "Password: ";
			cin >> password;

			//If password matches
			if (customer->password == password) {
				system("cls");
				currentUser = customer;
				return true;
			}

			else {
				cout << "Wrong password! Please try again." << endl;
				system("pause");
				system("cls");

				return false;
			}
		}
	}

	cout << "Invalid customer username! Please try again." << endl;
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
					system("cls");
					bool isAscOrder = orderOption == 1 ? true : false;
					//uniList.insertionSort(criteria, isAscOrder);
					uniList.quickSort(criteria, isAscOrder);
					displayUniversityList(true, criteria);
				}
			}
		}
		else if (input == 2) {

		}
		else if (input == 3) {
			LinkedList<University> favUniList = currentUser->favUniList;
			favUniList.display(1, favUniList.getSize());

			system("pause");
			system("cls");
		}
		else if (input == 4) {

		}
	} while (input != 5 || !valid);
}

bool moheLogin() {

	string username = "", password = "";
	bool valid = true;

	cout << "Username: ";
	cin >> username;

	cin.clear();
	cin.ignore();

	user* customer = userTable.searchUser(username);

	//If user is found
	if (customer->userName != "") {

		//If user account is a mohe user
		if (customer->accType == "MoHE") {
			cout << "Password: ";
			cin >> password;

			//If password matches
			if (customer->password == password) {
				system("cls");
				currentUser = customer;
				return true;
			}

			else {
				cout << "Wrong password! Please try again." << endl;
				system("pause");
				system("cls");

				return false;
			}
		}
	}

	cout << "Invalid MoHE username! Please try again." << endl;
	system("pause");
	system("cls");

	return false;
}

void moheMenu() {
	int input = 0;
	bool valid = false;

	//Display menu
	do {
		valid = true;

		cout << "1. Display User List" << endl;
		cout << "2. Sort User List" << endl;
		cout << "3. View University Feedback" << endl;
		cout << "4. View Favourite University Summary" << endl;
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

		}
		else if (input == 2) {

		}
		else if (input == 3) {

		}
		else if (input == 4) {

		}
	} while (input != 5 || !valid);
}

hashTable addDemoData() {
	hashTable userTable;

	userTable.addUserAcc("Paul", "Locha", "Customer");
	userTable.addUserAcc("Kim", "Iced Mocha", "Customer");
	userTable.addUserAcc("Annie", "Passion tea", "MoHE");
	userTable.addUserAcc("Sarah", "Chai tea", "Customer");
	userTable.addUserAcc("Eleven", "Apple cider", "MoHE");
	userTable.addUserAcc("Emma", "Hot Mocha", "MoHE");
	userTable.addUserAcc("Bill", "Root bear", "Customer");
	userTable.addUserAcc("Susan", "Skinny Latte", "Customer");
	userTable.addUserAcc("Marie", "Water", "Customer");
	userTable.addUserAcc("Joe", "Green Tea", "Customer");
	userTable.addUserAcc("Max", "Caramel mocha", "Customer");

	return userTable;
}