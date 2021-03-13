#include <iostream>

using namespace std;

// Bix size is 3x3
static int boxSize = 5;

class Boxes {
private:
	int arenaData[100][100];
	int cursorPosition[1][2];
	bool xTrun;
public:
	// Almost useless constructor
	Boxes(){
		xTrun = true;

		// Deafult arena
		SetArenaToDefault();

		// Default cursor
		SetCursorToDefault();
	}

	// Get cursor current location
	int getCursorLoaction(int x, int y) {
		return cursorPosition[x][y];
	}

	// Set cursor new location
	void setCursorLocation(int x, int y, int value) {
		if (value == 1) {
			cursorPosition[x][y]++;
		}
		else if (value == 0) {
			cursorPosition[x][y]--;
		}
	}

	// Set cursor to default
	void SetCursorToDefault() {
		cursorPosition[0][0] = 0;
		cursorPosition[0][1] = 0;
	}

	// Set arena to default
	void SetArenaToDefault() {
		for (int i = 0; i < boxSize; i++) {
			for (int j = 0; j < boxSize; j++) {
				arenaData[i][j] = 0;
			}
		}
	}

	// Assign pon
	bool AssignPon() {
		if (getArenaIsEmpty(cursorPosition[0][0], cursorPosition[0][1]) == true) {
			if (xTrun) {
				arenaData[cursorPosition[0][0]][cursorPosition[0][1]] = 1;
				setXTurn(false);
			}
			else {
				arenaData[cursorPosition[0][0]][cursorPosition[0][1]] = 2;
				setXTurn(true);
			}
			return true;
		}
		else {
			return false;
		}
	}

	// Get player turn
	bool getXturn() {
		return xTrun;
	}

	// Change player turn
	void setXTurn(bool a) {
		xTrun = a;
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
	void drawBoxes() {
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
				if (cursorPosition[0][0] == i && cursorPosition[0][1] == j) {
					cout << "^";
				}
				else {
					cout << " ";
				}
			} cout << endl;
		}
	}

};
