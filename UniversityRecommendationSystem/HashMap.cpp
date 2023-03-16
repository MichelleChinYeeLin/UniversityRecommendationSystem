#include<iostream>
using namespace std;

class HashMap {
	int key;
	string value;

public:
	HashMap() {
		cout << "Hash map is created!";
	}

	HashMap(int key, string value) {
		this->key = key;
		this->value = value;
	}

};

int main() {

}