#include <iostream>
// 4210191011 Alifian
using namespace std;

// Box size is 3x3
static int boxSize = 3;

class Boxes {
private:
	int arenaData[100][100];
	int cursorPosition[2];
public:
	// Almost useless constructor
	Boxes(){
		// Deafult arena
		SetArenaToDefault();

		// Default cursor
		SetCursorToDefault();
	}

	// Get cursor current location
	int getCursorLoaction(int a) {
		return cursorPosition[a];
	}

	// Set cursor new location
	void setCursorLocation(int a, int value) {
		if (value == 1) {
			cursorPosition[a]++;
		}
		else if (value == 0) {
			cursorPosition[a]--;
		}
	}

	// Set cursor to default
	void SetCursorToDefault() {
		cursorPosition[0] = 0;
		cursorPosition[1] = 0;
	}

	// Set arena to default
	void SetArenaToDefault() {
		for (int i = 0; i < boxSize; i++) {
			for (int j = 0; j < boxSize; j++) {
				arenaData[i][j] = 0;
			}
		}
	}

	// Check if arena is empty
	bool getArenaIsEmpty(int i, int j) {
		if (arenaData[i][j] == 0) {
			return true;
		}
		else {
			false;
		}
	}

	// Get arena data
	int getArenaData(int x, int y) {
		return arenaData[x][y];
	}

	// Set specific arena data
	void SetArenaData(int x, int y, int value) {
		arenaData[x][y] = value;
	}

	// Draw arena box
	void drawBoxes(bool xTrun) {
		//Box size = 6x14
		// 0 = " " ; 1 = "x" ; 2 = "o" ; 3 = "^"
		/* 
		cout << "   x | x | x" << endl; 
		cout << "   ^        " << endl; 
		cout << "   x | o | x" << "           Press p to exit" <<endl; 
		cout << "            " << endl; 
		cout << "   x | o | o" << endl; 
		cout << "            " << endl; 
		*/
		system("cls");
		if (xTrun) {
			cout << "\n       x Turn\n\n";
		}
		else {
			cout << "\n       o Turn\n\n";
		}
		for (int i = 0; i < boxSize; i++) {
			// For x o
			for (int j = 0; j < boxSize; j++) {
				if (j > 0) {
					cout << " | ";
				}
				else {
					cout << "   ";
				}
		
				if (arenaData[i][j] == 1) {
					cout << "x";
				}
				else if (arenaData[i][j] == 2) {
					cout << "o";
				}
				else if (arenaData[i][j] == 0) {
					cout << " ";
				}
			} 
			// For UI
			if (i == 1) {
				cout << "           Press p to exit";
			} cout << endl;

			// For cursor
			for (int j = 0; j < boxSize; j++) {
				cout << "   ";
				if (cursorPosition[0] == i && cursorPosition[1] == j) {
					cout << "^";
				}
				else {
					cout << " ";
				}
			} cout << endl;
		}
	}

};
