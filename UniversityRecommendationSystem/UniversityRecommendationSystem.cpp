#include "FileIO.h"
#include"FeedbackLinkedList.hpp"
#include <iostream>
#include <ctime>
#include<string>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;
using namespace std::chrono;

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

		//Display menu
		cout << "1. Customer Login" << endl;
		cout << "2. MoHE Login" << endl;
		cout << "3. Display University Information" << endl;
		cout << "4. Register As Customer" << endl;
		cout << "5. Quit" << endl;
		cout << "Enter option: ";

		//Read user input
		cin >> input;
		cout << endl << endl;

		//If user input is invalid
		if (cin.fail() || input < 1 || input > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Display error message
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}

		else if (input == 1) {
			valid = customerLogin(cus, cus1);
		}

		else if (input == 2) {
			valid = moheLogin(admin, cus, cus1);
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

		else if (input == 4) {
			system("cls");
			registerAsUser(cus);
			system("cls");
		}

	} while ((input != 5) || !valid);

}

//Display the university list
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

		//Move the elements in the next stack to the current stack and display them
		while(!nextStack.isEmpty() && itemCount < itemNum) {
			University university = nextStack.pop();
			currentStack.push(university);

			cout << left << setw(5) << numCount + itemCount;
			university.display(criteria);

			itemCount++;
		}
		
		//If user is registered and can add university to favorites
		if (hasFav) {
			cout << endl << "Enter 'P' to view previous page, 'N' to view next page, 'F' to favourite a university";
			cout << endl << "Enter any other key to exit";
			cout << endl << "Option: ";
			cin >> input;

			if (input == "F") {
				addFavouriteUniversity(numCount, numCount + itemNum);

				//Move the current stack to the next stack
				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					nextStack.push(temp);
				}
			}
		}

		//If user is unregistered
		else {
			cout << endl << "Enter 'P' to view previous page, 'N' to view next page";
			cout << endl << "Enter any other key to exit";
			cout << endl << "Option: ";
			cin >> input;
		}

		//Customer wants to view previous
		if (input == "P") {

			//Move the current stack to the next stack
			while (!currentStack.isEmpty()) {
				University temp = currentStack.pop();
				nextStack.push(temp);
			}

			//If previous stack is empty
			if (prevStack.isEmpty()) {
				cout << "Previous data does not exist!" << endl;
				system("pause");
			}

			//If previous stack is not empty
			else {
				int count = itemNum;

				//Move the previous elements to the current stack
				while (!prevStack.isEmpty() && count > 0) {
					University temp = prevStack.pop();
					currentStack.push(temp);
					count--;
					numCount--;
				}

				//Move the elements in the current stack to the next stack
				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					nextStack.push(temp);
				}
			}
		}

		//Customer wants to view next
		else if (input == "N") {

			//If next stack is empty
			if (nextStack.isEmpty()) {

				while (!currentStack.isEmpty()) {
					University temp = currentStack.pop();
					nextStack.push(temp);
				}

				cout << "Next data does not exist!" << endl;
				system("pause");
			}

			//If next stack is not empty
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

	user* customer = cus->searchUser(username);
	string realPassword = customer->password;

	cout << "Please enter your password: ";
	cin >> password;

	//If customer password matches
	if (password == realPassword) {
		currentUser = customer;
		system("cls");
		customerMenu(cus1, username);
		return true;
	}

	//If customer password does not match
	else {
		cout << "Invalid credentials! Please try again!\n";
		system("pause");
		system("cls");
		return false;
	}
}

bool moheLogin(hashTable* admin, hashTable* cus, FeedbackLinkedList* cus1) {
	string username, password;
	bool valid = true;

	cout << "===== MoHE Login Page =====" << endl;
	cout << "Please enter your username: ";
	cin >> username;
	string realPassword = admin->searchUser(username)->password;

	cout << "Please enter your password: ";
	cin >> password;

	//If MoHE password matches
	if (password == realPassword) {
		user* loggedInUser = admin->searchUser(username);
		loggedInUser->lastActiveTime = time(nullptr);

		system("cls");
		moheMenu(cus, cus1);
		return true;
	}

	//If MoHE password does not match
	else {
		cout << "Invalid credentials! Please try again!\n";
		system("pause");
		system("cls");
		return false;
	}
}

void moheMenu(hashTable* cus, FeedbackLinkedList* cus1) {
	int input = 0;
	bool valid = false;

	cout << "===== MoHE Menu =====" << endl << endl;
	//Display menu
	do {
		valid = true;

		cout << "1. Display User List" << endl;
		cout << "2. View University Feedback" << endl;
		cout << "3. Reply Oldest Feedback" << endl;
		cout << "4. View Favourite University Summary" << endl;
		cout << "5. Delete Inactive Accounts" << endl;
		cout << "6. Logout" << endl;
		cout << "Enter option: ";
		cin >> input;

		system("cls");

		if (cin.fail() || input < 1 || input > 6) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}
		else if (input == 1) {
			cus->printTable();
			system("cls");
		}
		else if (input == 2) {
			readFeedback(cus1);
			system("cls");
		}
		else if (input == 3) {
			replyFeedback(cus1);
			system("cls");
		}
		else if (input == 4) {
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
		else if (input == 5) {
			cus->deleteInactiveAccounts();
			system("cls");
		}
		else if (input == 6) {
			valid = false;
			system("cls");
			return;
		}
	} while (input != 6 || !valid);
}

void customerMenu(FeedbackLinkedList* cus, string username) {
	int input = 0;
	bool valid = false;

	cout << "===== Customer Menu =====" << endl << endl;
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
					auto start = high_resolution_clock::now();
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
					//start timer for searching 
					auto start = high_resolution_clock::now();

					result = uniList.binarySearch(criteria, key);
					//result = uniList.linearSearch(key);

					//Record time taken for searching
					//auto stop = high_resolution_clock::now();
					//auto duration = duration_cast<microseconds>(stop - start);
					//cout << "Time taken by linear search algorithm: ";
					//cout << duration.count() << " microseconds." << endl;
					//system("pause");
					//system("cls");

					if (result != NULL) {
						University university = result->data;
						cout << string(135, '=') << endl;
						cout << left << setw(5) << "No." << setw(10) << "Rank" << setw(90) << "Name" << setw(10) << "Loc. Code" << setw(30) << "Location" << endl;
						cout << string(135, '=') << endl;
						university.display();
					}

					else {
						cout << "University was not found..." << endl << endl;
					}
				}
				else {
					double key1 = 0.0;
					cout << "Please enter the university search for: ";
					cin >> key1;
					//start timer for searching 
					//auto start = high_resolution_clock::now();

					testResult = uniList.binarySearch(criteria, key1);

					//Record time taken for searching
					/*auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "Time taken by binary search algorithm: ";
					cout << duration.count() << " microseconds." << endl;
					system("pause");
					system("cls");*/

					if (testResult.getSize() == 0) {
						cout << "University was not found..." << endl << endl;
					}
					else {
						testResult.display(0, 100);
					}
				}

				system("pause");
				system("cls");
			}
		}
		else if (input == 3) {
			system("cls");
			LinkedList<University> favUniList = currentUser->favUniList;
			favUniList.display(1, favUniList.getSize());

			system("pause");
			system("cls");
		}
		else if (input == 4) {
			system("cls");
			writeFeedback(username, cus);
			system("cls");
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