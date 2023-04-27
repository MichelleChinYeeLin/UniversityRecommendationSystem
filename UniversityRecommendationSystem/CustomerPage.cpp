#include<iostream>
#include"CustomerPage.hpp"
using namespace std;

void displayUniversityList() {
	FileIO *fileIO = new FileIO();
	LinkedList<University> uniList1 = fileIO->readUniversityFile();
	int min = 1;
	int max = 100;
	string input = "";
	bool endOfList = false;

	do {
		endOfList = uniList1.display(min, max);

		if (endOfList) {
			cout << "End of University List!" << endl;
			system("pause");
		}

		else {
			cout << "Continue? Enter 'Y' to continue displaying list: ";
			cin >> input;

			if (input == "Y") {
				min += 100;
				max += 100;
				system("cls");
			}
		}

	} while (input == "Y" && !endOfList);
}

void registerAsUser(hashTable* cus) {
	string name, pw;
	char input;
	cout << "Please enter your name: ";
	cin >> name;
	cout << "Please enter your password: ";
	cin >> pw;
	cus->addUserAcc(name, pw);
	while (true) {
		cout << "Congragulations! You successfully registered as customer! Enter Q to quit " << endl;
		cin >> input;
		if (input == 'Q') {
			return;
		}
		else {
			cout << "Invalid input! Please enter again!" << endl;
		}
	}
}

bool customerLogin(hashTable* cus) {
	string username, password;
	bool valid = true;

	cout << "Please enter your username: ";
	cin >> username;
	string realPassword = cus->searchForUsername(username);

	while (true) {
		cout << "Please enter your password: ";
		cin >> password;
		if (password == realPassword) {
			customerMenu();
		}
		else {
			cout << "Wrong password! Please try again!\n";
		}
	}
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
			writeFeedback();
		}
	} while (input != 5 || !valid);
}

void writeFeedback(FeedbackLinkedList* cus) {
	string feedback;
	string username;
	time_t now = time(0);
	tm* tm = localtime(&now);
	cout << "Please enter your feedback: ";
	cin.ignore();
	getline(cin,feedback);
	cus->insertToEnd(username, tm, feedback);
}

//int main() {
//	return 0;
//}