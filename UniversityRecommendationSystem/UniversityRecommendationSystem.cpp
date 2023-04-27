//#include "LinkedList.h"
//#include "University.h"
#include "FileIO.h"
#include"HashTable.hpp"
#include"CustomerPage.hpp"
#include"MoHEPage.hpp"
#include <iostream>
using namespace std;

// home page for admin to login and for customer to login/register
void homePage(hashTable* admin, hashTable* cus) {
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
			customerLogin(cus);
		}

		else if (input == 3) {
			valid = MoHELogin(admin, cus);

			if (valid) {
				MoHEMenu(cus);
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

int main() {
	hashTable* cus = new hashTable();
	hashTable* admin = new hashTable();
	FeedbackLinkedList* cus1 = new FeedbackLinkedList();
	admin->addUserAcc("hello", "12345"); //admin account
	homePage(admin, cus);
	return 0;
}