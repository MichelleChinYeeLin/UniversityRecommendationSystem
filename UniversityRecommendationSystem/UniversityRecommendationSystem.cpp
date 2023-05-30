#include "FileIO.h"
#include"FeedbackLinkedList.hpp"
#include <iostream>
#include <ctime>
#include<string>
#include <iomanip>
#include <limits>
using namespace std;

//Function prototypes
bool customerLogin(hashTable* cus, FeedbackLinkedList* cus1);
void customerMenu(FeedbackLinkedList* cus, string username);
bool moheLogin(hashTable* admin, hashTable* cus, FeedbackLinkedList* cus1);
void moheMenu(hashTable* cus, FeedbackLinkedList* cus1);
void writeFeedback(string username, FeedbackLinkedList* cus);
void readFeedback(FeedbackLinkedList* admin);
void displayUniversityList(bool, Criteria);
void addFavouriteUniversity(int, int);
void registerAsUser(hashTable* cus);
void replyFeedback(FeedbackLinkedList* admin);

//hashTable addDemoData();
LinkedList<University> uniList;
hashTable userTable;
user* currentUser;

void homePage(hashTable* admin, hashTable* cus, FeedbackLinkedList* cus1) {
	FileIO fileIO;
	uniList = fileIO.readUniversityFile();
	//userTable = addDemoData();

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
			customerLogin(cus, cus1);
		}

		else if (input == 2) {
			valid = moheLogin(admin, cus, cus1);

			if (valid) {
				moheMenu(cus, cus1);
				valid = false;
			}
		}

		else if (input == 3) {
			system("cls");
			uniList.insertionSort(RANK, true);
			displayUniversityList(false, NAME);
		}

	} while ((input != 4) || !valid);

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
	favNode->data.addTotalFavNum();
	system("pause");
}

bool customerLogin(hashTable* cus, FeedbackLinkedList* cus1) {
	string username, password;
	bool valid = true;

	cout << "===== Customer Login Page =====" << endl;
	cout << "Please enter your username: ";
	cin >> username;
	string realPassword = cus->searchUser(username)->password;

	while (true) {
		cout << "Please enter your password: ";
		cin >> password;
		if (password == realPassword) {
			customerMenu(cus1, username);
			return true;
		}
		else {
			cout << "Wrong password! Please try again!\n";
		}
	}
	return false;
	//string username = "", password = "";
	//bool valid = true;

	//cout << "Username: ";
	//cin >> username;

	//cin.clear();
	//cin.ignore();

	//user* customer = userTable.searchUser(username);

	////If user is found
	//if (customer->userName != "") {

	//	//If user account is a customer
	//	if (customer->accType == "Customer") {
	//		cout << "Password: ";
	//		getline(cin, password);
	//		cin.clear();

	//		//If password matches
	//		if (customer->password == password) {
	//			system("cls");
	//			currentUser = customer;
	//			return true;
	//		}

	//		else {
	//			cout << "Wrong password! Please try again." << endl;
	//			return false;
	//		}
	//	}
	//}

	//cout << "Invalid customer username! Please try again." << endl;
	//return false;
}

bool moheLogin(hashTable* admin, hashTable* cus, FeedbackLinkedList* cus1) {
	string username, password;
	bool valid = true;

	cout << "===== MoHE Login Page =====" << endl;
	cout << "Please enter your username: ";
	cin >> username;
	string realPassword = admin->searchUser(username)->password;

	while (true) {
		cout << "Please enter your password: ";
		cin >> password;
		if (password == realPassword) {
			user* loggedInUser = admin->searchUser(username);
			loggedInUser->lastActiveTime = time(nullptr);

			moheMenu(cus, cus1);
			return true;
		}
		else {
			cout << "Wrong password! Please try again!\n";
		}
	}
	return false;
}

void moheMenu(hashTable* cus, FeedbackLinkedList* cus1) {
	int input = 0;
	bool valid = false;

	//Display menu
	do {
		valid = true;

		cout << "1. Display User List" << endl;
		cout << "2. Sort User List" << endl;
		cout << "3. View University Feedback" << endl;
		cout << "4. Reply Oldest Feedback" << endl;
		cout << "5. View Favourite University Summary" << endl;
		cout << "6. Delete Inactive Accounts" << endl;
		cout << "7. Logout" << endl;
		cout << "Enter option: ";
		cin >> input;

		system("cls");

		if (cin.fail() || input < 1 || input > 7) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}
		else if (input == 1) {
			cus->printTable();
		}
		else if (input == 2) {
			
		}
		else if (input == 3) {
			readFeedback(cus1);
		}
		else if (input == 4) {
			replyFeedback(cus1);
		}
		else if (input == 5) {
			uniList.insertionSort(TOTAL_FAV_NUM, false);
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
		else if (input == 6) {
			cus->deleteInactiveAccounts();
		}
		else if (input == 7) {
			valid = false;
			system("cls");
			return;
		}
	} while (input != 7 || !valid);
}

void customerMenu(FeedbackLinkedList* cus, string username) {
	int input = 0;
	bool valid = false;

	cout << "\n\n===== Customer Menu =====" << endl << endl;
	//Display menu
	do {
		cout << "1. Sort University Information" << endl;
		cout << "2. Search University" << endl;
		cout << "3. View Favorite Universities" << endl;
		cout << "4. Write Feedback" << endl;
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
			writeFeedback(username, cus);
		}
		else if (input == 5) {
			valid = false;
			system("cls");
			return;
		}
	} while (input != 5 || !valid);
}

void registerAsUser(hashTable* cus) {
	string name, pw;
	char input;
	cout << "===== Customer Register Page =====" << endl << endl;
	cout << "Please enter your name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Please enter your password: ";
	cin >> pw;
	time_t currentTime = time(nullptr);
	cus->addUserAcc(name, pw, "cus", currentTime);
	while (true) {
		cout << "\nCongragulations! You successfully registered as customer! Enter Q to quit " << endl;
		cin >> input;
		cout << endl;
		if (input == 'Q') {
			cout << "==================================" << endl;
			system("cls");
			return;
		}
		else {
			cout << "Invalid input! Please enter again!" << endl;
		}
	}
}

void writeFeedback(string username, FeedbackLinkedList* cus) {
	string feedback;
	time_t currentTime = time(nullptr);

	cout << "===== Write Feedback =====" << endl << endl;
	cout << "Please enter your feedback: ";
	cin.ignore();
	getline(cin, feedback);
	cus->insertToEnd(username, currentTime, feedback, false, "", currentTime);
}

void readFeedback(FeedbackLinkedList* admin) {
	system("cls");
	cout << "===== Read Feedback =====" << endl;
	admin->display();
}

void replyFeedback(FeedbackLinkedList* admin) {
	string reply;
	cout << "===== Reply Feedback =====" << endl << endl;
	cout << "Please enter your reply: ";
	cin.ignore();
	getline(cin, reply);
	admin->replyFeedback(reply);
}

int main() {
	hashTable* cus = new hashTable();
	hashTable* admin = new hashTable();
	FeedbackLinkedList* cus1 = new FeedbackLinkedList();
	time_t currentTime = time(nullptr);
	admin->addUserAcc("hello", "12345", "admin", currentTime); //admin account

	// 30/5/2022
	struct tm timeStruct;
	timeStruct.tm_sec = 0;
	timeStruct.tm_min = 0;
	timeStruct.tm_hour = 0;
	timeStruct.tm_mday = 30;
	timeStruct.tm_mon = 4; 
	timeStruct.tm_year = 122;
	timeStruct.tm_isdst = -1;

	time_t creationTime = mktime(&timeStruct);
	cus->addUserAcc("shin", "shin", "Customer", creationTime);
	cus->addUserAcc("cus2", "67890", "Customer", currentTime);
	homePage(admin, cus, cus1);
	return 0;
}

//hashTable addDemoData() {
//	hashTable userTable;
//
//	userTable.addUserAcc("Paul", "Locha", "Customer");
//	userTable.addUserAcc("Kim", "Iced Mocha", "Customer");
//	userTable.addUserAcc("Annie", "Passion tea", "MoHE");
//	userTable.addUserAcc("Sarah", "Chai tea", "Customer");
//	userTable.addUserAcc("Eleven", "Apple cider", "MoHE");
//	userTable.addUserAcc("Emma", "Hot Mocha", "MoHE");
//	userTable.addUserAcc("Bill", "Root bear", "Customer");
//	userTable.addUserAcc("Susan", "Skinny Latte", "Customer");
//	userTable.addUserAcc("Marie", "Water", "Customer");
//	userTable.addUserAcc("Joe", "Green Tea", "Customer");
//	userTable.addUserAcc("Max", "Caramel mocha", "Customer");
//
//	return userTable;
//}