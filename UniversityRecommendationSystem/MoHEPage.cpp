#include <iostream>
#include"MoHEPage.hpp"
using namespace std;

void displayUserDetails(hashTable* cus) {
	system("cls");
	cout << "-----Display user details-----" << endl;
	cus->printTable();
}

void modifyUserDetails(hashTable* cus) {
	string username;
	cout << "Please enter the user you want to update its password: ";
	cin >> username;
	cus->updatePwd(username);
}

void deleteUserAccounts(hashTable* cus) {
	string username;
	cout << "Please enter the user you want to delete: ";
	cin >> username;
	cus->removeUserAcc(username);
}

void readFeedback(FeedbackLinkedList*admin) {
	cout << "===== Read Feedback =====";
	admin->display();
}

void replyFeedback() {

}

bool MoHELogin(hashTable* admin, hashTable* cus) {
	string username, password;
	bool valid = true;

	cout << "Please enter your username: ";
	cin >> username;
	string realPassword = admin->searchForUsername(username);

	while (true) {
		cout << "Please enter your password: ";
		cin >> password;
		if (password == realPassword) {
			MoHEMenu(cus);
		}
		else {
			cout << "Wrong password! Please try again!\n";
		}
	}
	return false;
}

void MoHEMenu(hashTable* cus) {
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

		}
		else if (input == 5) {

		}
		else if (input == 6) {

		}
	} while (input != 7 || !valid);
}