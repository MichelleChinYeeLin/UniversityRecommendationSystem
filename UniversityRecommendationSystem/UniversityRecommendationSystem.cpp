#include "FileIO.h"
#include <iostream>
#include<string>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Function prototypes
bool customerLogin();
void customerMenu();
bool moheLogin();
void moheMenu();
void displayUniversityList(bool, Criteria);
void addFavouriteUniversity(int, int);

hashTable addDemoData();

LinkedList<University> uniList;
LinkedList<University> uniList1;
hashTable userTable;
user* currentUser;

int main() {
	//Read the university CSV file
	FileIO fileIO;
	uniList = fileIO.readUniversityFile();

	//Add user data for demonstration
	userTable = addDemoData();
	
	int input = 0;
	bool valid = true;

	//Display menu
	do {
		valid = true;

		//Display menu
		cout << "1. Customer Login" << endl;
		cout << "2. MoHE Login" << endl;
		cout << "3. Display University Information" << endl;
		cout << "4. Quit" << endl;
		cout << "Enter option: ";

		//Read user input
		cin >> input;
		cout << endl << endl;

		//If user input is invalid
		if (cin.fail() || input < 1 || input > 4) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Display error message
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}

		else if (input == 1) {
			//Allow user to log in as customer
			valid = customerLogin();

			//If customer username and password is valid
			if (valid) {
				customerMenu();
				valid = false;
				system("cls");
			}

			//If customer username and password is invalid
			else {
				system("pause");
				system("cls");
			}
		}

		else if (input == 2) {
			//Allow user to log in as MoHE
			valid = moheLogin();

			//If MoHE username and password is valid
			if (valid) {
				moheMenu();
				valid = false;
				system("cls");
			}

			//If MoHE username and password is invalid
			else {
				system("pause");
				system("cls");
			}
		}

		else if (input == 3) {
			system("cls");

			//Set default sorting criteria as 'rank'
			uniList.insertionSort(RANK, true);

			//Display university list
			//Without option to add favourites
			//Display the 'name' criteria
			displayUniversityList(false, NAME);
		}

	} while (input != 4 || !valid);
	
	return 0;
}

//Display the university list
//hasFav: allows the user to add a university to favourites
//criteria: set the criteria that needs to be displayed
void displayUniversityList(bool hasFav, Criteria criteria) {

	//Display 100 universities at one time
	int itemNum = 100;
	string input = "";
	
	//Create stacks to act as 'next' and 'previous' university list
	Stack<University> nextStack;
	Stack<University> currentStack;
	Stack<University> prevStack;

	//Add all universities into the next stack
	for (int i = uniList.getSize() - 1; i >= 0; i--) {
		nextStack.push(uniList.getFromPosition(i)->data);
	}

	int numCount = 1;

	do {

		//Display header
		cout << string(135, '=') << endl;

		//If the criteria is 'name', 'location_code' or 'location'
		if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
			cout << left << setw(5) << "No." << setw(10) << "Rank" << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
		}

		else {
			string rank;
			string score;

			//Check the criteria to create the header
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

			//Display the header based on the criteria
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
			cout << endl << "Enter 'P' to view previous page, 'N' to view next page, 'F' to favourite a university";
			cout << endl << "Enter any other key to exit";
			cout << endl << "Option: ";
			cin >> input;

			if (input == "F") {
				addFavouriteUniversity(numCount, numCount + itemNum);

				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					nextStack.push(temp);
				}
			}
		}

		else {
			cout << endl << "Enter 'P' to view previous page, 'N' to view next page";
			cout << endl << "Enter any other key to exit";
			cout << endl << "Option: ";
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
	favNode->data.addTotalFavNum();
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
			getline(cin, password);
			cin.clear();

			//If password matches
			if (customer->password == password) {
				system("cls");
				currentUser = customer;
				return true;
			}

			else {
				cout << "Wrong password! Please try again." << endl;
				return false;
			}
		}
	}

	cout << "Invalid customer username! Please try again." << endl;
	return false;
}

void customerMenu() {
	int input = 0;
	bool valid = false;

	//Display menu
	do {
		valid = true;

		cout << "========== Customer Menu ==========" << endl;
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
			cout << "========== Sort University Information ==========" << endl << endl;
			cout << "=============== Category ===============" << endl;
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
				cout << "========== Order ==========" << endl;
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

					//Start timer for sorting
					//auto start = high_resolution_clock::now();
					//uniList.insertionSort(criteria, isAscOrder);

					uniList.quickSort(criteria, isAscOrder);

					//Record time taken for sorting//
					/*auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "Time taken by quick sort algorithm: ";
					cout << duration.count() << " microseconds." << endl;
					system("pause");
					system("cls");*/

					displayUniversityList(true, criteria);
				}
			}
		}
		else if (input == 2) {
			//string name = "";
			//cout << endl << endl;
			//cout << "========== Search University ==========" << endl << endl;
			//cout << "Please enter the university search for: ";
			//cin.ignore();
			//getline(cin, name);
			//University key;
			//key.setName(name);
			//uniList.insertionSort(NAME, 1);
			////Node<University>* result = uniList.binarySearch(key);
			//Node<University>* result = uniList.linearSearch(key);
			//if (result == NULL) {
			//	cout << "University was not found..." << endl << endl;
			//}
			//else {
			//	cout << result->data.getName() << setw(10) <<
			//		result->data.getLocationCode() << setw(30) <<
			//		result->data.getLocation() << endl;
			//	cout << "University was found!" << endl << endl;
			//}

			int categoryInput = 0;
			cout << "========== Search University Information ==========" << endl << endl;
			cout << "=============== Category ===============" << endl;
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
			cout << "Select category to search: ";
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
					criteria = ARSCORE;
					break;
				case 6:
					criteria = ERSCORE;
					break;
				case 7:
					criteria = FSRSCORE;
					break;
				case 8:
					criteria = CPFSCORE;
					break;
				case 9:
					criteria = IFRSCORE;
					break;
				case 10:
					criteria = ISRSCORE;
					break;
				case 11:
					criteria = IRNSCORE;
					break;
				case 12:
					criteria = GERSCORE;
					break;
				}
				
				cout << endl << endl;
				cout << "========== Search University ==========" << endl << endl;
				uniList.quickSort(criteria, 1);
				Node<University>* result;
				LinkedList<University> testResult;
				if (criteria == NAME || criteria == LOCATION_CODE || criteria == LOCATION) {
					string key = "";
					cout << "Please enter the university search for: ";
					cin.ignore();
					getline(cin, key);
					//result = uniList.binarySearch(criteria, key);
				}
				else {
					double key1 = 0.0;
					cout << "Please enter the university search for: ";
					cin >> key1;
					testResult = uniList.binarySearch(criteria, key1);

				}

				if (testResult.getSize() == 0) {
					cout << "University was not found..." << endl << endl;
				}
				else {
					testResult.display(0, 100);
					/*Node<University> currentUniversity = testResult->head;
					cout << testResult.getName() << setw(10) <<
						testResult-.getLocationCode() << setw(30) <<
						testResult->data.getLocation() << endl;
					cout << "University was found!" << endl << endl;*/
				}
			}
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

	user* mohe = userTable.searchUser(username);

	//If user is found
	if (mohe->userName != "") {

		//If user account is a mohe user
		if (mohe->accType == "MoHE") {
			cout << "Password: ";
			getline(cin, password);
			cin.clear();
			//cin >> password;


			//If password matches
			if (mohe->password == password) {
				system("cls");
				currentUser = mohe;
				return true;
			}

			else {
				cout << "Wrong password! Please try again." << endl;
				return false;
			}
		}
	}

	cout << "Invalid MoHE username! Please try again." << endl;
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
			//uniList.insertionSort(TOTAL_FAV_NUM, false);
			uniList.quickSort(TOTAL_FAV_NUM, false);
			cout << "========== Top 10 Favourite University ==========" << endl;
			for (int i = 0; i < 10; i++) {
				University university = uniList.getFromPosition(i)->data;

				if (i == 0 && university.getTotalFavNum() == 0) {
					cout << "No favourite university available! Please try again." << endl;
					break;
				}

				else if (university.getTotalFavNum() == 0) {
					break;
				}

				cout << i + 1 << " ";
				university.display(TOTAL_FAV_NUM);
				cout << endl;
			}
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