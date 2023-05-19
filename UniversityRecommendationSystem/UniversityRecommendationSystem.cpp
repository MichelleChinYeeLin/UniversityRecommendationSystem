//#include "LinkedList.h"
//#include "University.h"
#include "FileIO.h"
#include"HashTable.hpp"
#include"CustomerPage.hpp"
#include <iostream>
using namespace std;

bool customerLogin(hashTable* cus, FeedbackLinkedList* cus1) {
	string username, password;
	bool valid = false;

	cout << "===== Customer Login Page =====" << endl << endl;
	cout << "Please enter your username: ";
	cin.ignore();
	getline(cin, username);
	string realPassword = cus->searchForUsername(username);

	while (true) {
		cout << "Please enter your password: ";
		cin >> password;
		if (password == realPassword) {
			customerMenu(cus1, username);
			valid = true;
			break;
		}
		else {
			valid = false;
			cout << "Wrong password! Please try again!\n";
		}
	}
	return valid;
}

bool MoHELogin(hashTable* admin, hashTable* cus, FeedbackLinkedList* cus1) {
	string username, password;
	bool valid = true;

	cout << "===== MoHE Login Page =====" << endl;
	cout << "Please enter your username: ";
	cin >> username;
	string realPassword = admin->searchForUsername(username);

	while (true) {
		cout << "Please enter your password: ";
		cin >> password;
		if (password == realPassword) {
			MoHEMenu(cus,cus1);
		}
		else {
			cout << "Wrong password! Please try again!\n";
		}
	}
	return false;
}

// home page for admin to login and for customer to login/register
void homePage(hashTable* admin, hashTable* cus, FeedbackLinkedList*cus1) {
	int input = 0;
	bool valid = true;

	//Display menu
	do {
		valid = true;

		cout << "1. Register as customer " << endl;
		cout << "2. Customer Login" << endl;
		cout << "3. MoHE Login" << endl;
		cout << "4. Display University Information" << endl;
		cout << "5. Quit" << endl;
		cout << "Enter option: ";
		cin >> input;
		cout << endl << endl;

		if (cin.fail() || input < 1 || input > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}

		else if (input == 1) {
			registerAsUser(cus);
		}

		else if (input == 2) {
			customerLogin(cus, cus1);
		}

		else if (input == 3) {
			valid = MoHELogin(admin, cus,cus1);

			if (valid) {
				MoHEMenu(cus,cus1);
				valid = false;
			}
		}

		else if (input == 4) {
			system("cls");

			displayUniversityList();

			system("pause");
			system("cls");
		}

	} while (input != 5 || !valid);
}

void displayUserDetails(hashTable* cus) {
	system("cls");
	cout << "===== Display user details =====" << endl;
	cus->printTable();
}

void modifyUserDetails(hashTable* cus) {
	string username;
	system("cls");
	cout << "===== Modify user details =====" << endl;
	cout << "Please enter the user you want to update its password: ";
	cin >> username;
	cus->updatePwd(username);
}

void deleteUserAccounts(hashTable* cus) {
	string username;
	system("cls");
	cout << "===== Delete user accounts =====" << endl;
	cout << "Please enter the user you want to delete: ";
	cin >> username;
	cus->removeUserAcc(username);
}

void readFeedback(FeedbackLinkedList* admin) {
	system("cls");
	cout << "===== Read Feedback =====" << endl;
	admin->display();
}

void replyFeedback() {
	system("cls");
	cout << "===== Reply Feedback =====" << endl;

}

void MoHEMenu(hashTable* cus, FeedbackLinkedList* cus1) {
	int input = 0;
	bool valid = true;

	//Display menu
	do {
		cout << "1. Display user details" << endl;
		cout << "2. Modify user details" << endl;
		cout << "3. Delete user accounts" << endl;
		cout << "4. Read feedback from users" << endl;
		cout << "5. Reply to user's feedback" << endl;
		cout << "6. Summarize top 10 universities, generate report" << endl;
		cout << "7. Logout" << endl;
		cout << "Enter option: ";
		cin >> input;
		cout << endl << endl;

		if (cin.fail() || input < 1 || input > 7) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid option! Please try again!" << endl;
			system("pause");
			system("cls");
			valid = false;
		}

		else if (input == 1) {
			displayUserDetails(cus);
		}
		else if (input == 2) {
			modifyUserDetails(cus);
		}
		else if (input == 3) {
			deleteUserAccounts(cus);
		}
		else if (input == 4) {
			readFeedback(cus1);
		}
		else if (input == 5) {
			replyFeedback();
		}
		else if (input == 6) {

		}
		else if (input == 7) {
			valid = false;
			return;
		}
	} while (input != 7 || !valid);
}

int main() {
	hashTable* cus = new hashTable();
	hashTable* admin = new hashTable();
	FeedbackLinkedList* cus1 = new FeedbackLinkedList();
	admin->addUserAcc("hello", "12345"); //admin account
	homePage(admin, cus,cus1);
	return 0;
}