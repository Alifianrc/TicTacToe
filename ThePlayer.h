#include <iostream>
#include <conio.h>


using namespace std;

class Player {
private:
	string name1, name2;

public:
	
	// Input player name from user
	void inputName() {
		system("cls");
		cout << "\n   Input Player Name\n";
		cout << "   Player x : "; cin >> name1;
		cout << "   Player o : "; cin >> name2;
	}

	// Get function
	string getXName() {
		return name1;
	}

	// Get function
	string getOName() {
		return name2;
	}

	// Reload resume game
	void setPlayerName(string xNam, string oNam) {
		name1 = xNam;
		name2 = oNam;
	}

	// Get Kerboard input
	char getInput() {
		char theInput = 'x';
		if (_kbhit()) {
			theInput = _getch();
		}
		else {
			theInput = 'x';
		}
		return theInput;
	}
};
