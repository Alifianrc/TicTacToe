#include <iostream>

using namespace std;



class Boxes {
private:
	int arenaData[6][14];
	bool xTrun;
public:
	// Almost useless constructor
	Boxes(){
		xTrun = true;
	}

	// Get player turn
	bool getXturn() {
		return xTrun;
	}

	// Change player turn
	void setXturn() {
		if (xTrun) {
			xTrun = false;
		}
		else {
			xTrun = true;
		}
	}

	void setXTurn(bool a) {
		xTrun = a;
	}

	// Set current arenaData
	void setBox(int data[6][14]) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				arenaData[i][j] = data[i][j];
			}
		}
	}

	// Check if arena is empty
	bool getArenaLock(int i, int j) {
		if (arenaData[i][j] == 0) {
			return false;
		}
		else {
			true;
		}
	}

	// Draw arena box
	void drawBoxes() {
		//Box size = 6x14
		// 0 = " " ; 1 = "x" ; 2 = "o" ; 3 = "^"
		/* 
		cout << "  x   x   x   " << endl; 0
		cout << "  ^           " << endl; 1
		cout << "  x   o   x   " << endl; 2
		cout << "              " << endl; 3
		cout << "  x   o   o   " << endl; 4
		cout << "              " << endl; 5
		*/
		system("cls");
		if (xTrun) {
			cout << "\n       x Turn\n\n";
		}
		else {
			cout << "\n       o Turn\n\n";
		}
		for (int i = 0; i < 6; i++) {
			cout << "   ";
			for (int j = 0; j < 14; j++) {
				if (j == 4 || j == 8) {
					cout << "|";
				}			
				else if (arenaData[i][j] == 1) {
					cout << "x";
				}
				else if (arenaData[i][j] == 2) {
					cout << "0";
				}
				else if (arenaData[i][j] == 3) {
					cout << "^";
				}
				else if (i == 1 || i == 3) {
					cout << "_";
				}
				else if (arenaData[i][j] == 0) {
					cout << " ";
				}
			}
			if (i == 2) {
				cout << "           Press P to exit";
			}
			cout << endl;
		}
	}

};
