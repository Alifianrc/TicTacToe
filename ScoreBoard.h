#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Class Scoreboard
class scoreBoards {
private:
	// Struct for data score
	struct score {
		// Name Player x dan o
		string xName, oName;
		// Match winner
		int winner;
	} dataScore[100];

	// For file txt score data
	string data, xNam, oNam, win, last, close;
	// Address file txt
	string fileName;

	struct lastMatch {
		// Name Player x dan o
		string xName, oName;
		// Last condition arena
		int arenaData[6][14];
		// 1 if xTunr, 2 if oTurn
		int xTurn;
	} theLastMatch;
	// For file txt last match
	string lastXName, lastOName, lastData;

	// For saving data copy from txt
	string txtData;
	int MAX;
	char temp[1000];

public:

	// Constructor
	scoreBoards() {
		data = "<Data>";
		xNam = "<xName>";
		oNam = "<oName>";
		win = "<win>";
		last = "<last>";
		close = "<Close>";
		
		fileName = "D:\\Tugas_Kuliah\\Pemrograman_4\\Minggu2\\TicTacToe\\score_data.txt";
		MAX = 1000;
		temp[1000];

		lastXName = "<lastXName>";
		lastOName = "<lastOName>";
		lastData = "<lastData>";
	}

	// Load data from txt file
	void loadData(){
		int findFront = 0, findBack = 0, lenght;

		// Open txt file 
		ifstream file;
		file.open(fileName);
		// If error while opening
		if (!file) {
			cout << "Error Dalam Membuka File!!!" << endl;
			exit(0);
		}

		// Copy all data from file txt
		while (!file.eof()) {
			file.getline(temp, MAX);
			txtData = txtData + temp;
		}
		// Close txt file
		file.close();

		// Load last match data
		findFront = txtData.find(lastXName, findFront + 1) + 11;
		findBack = txtData.find(lastOName, findBack + 1);
		lenght = findBack - findFront;
		theLastMatch.xName = txtData.substr(findFront, lenght);

		findFront = txtData.find(lastOName, findFront + 1) + 11;
		findBack = txtData.find(lastData, findBack + 1);
		lenght = findBack - findFront;
		theLastMatch.oName = txtData.substr(findFront, lenght);

		findFront = txtData.find(lastData, findFront + 1) + 10;
		findBack = txtData.find(last, findBack + 1);
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				theLastMatch.arenaData[i][j] = stoi(txtData.substr(findFront, 1));
				findFront++;
			}
		}
		
		// Load scoreboard
		for (int i = 0; i < 100; i++) {
			findFront = txtData.find(xNam, findFront + 1) + 7;
			findBack = txtData.find(oNam, findBack + 1);
			lenght = findBack - findFront;
			dataScore[i].xName = txtData.substr(findFront, lenght);

			findFront = txtData.find(oNam, findFront + 1) + 7;
			findBack = txtData.find(win, findBack + 1);
			lenght = findBack - findFront;
			dataScore[i].oName = txtData.substr(findFront, lenght);

			findFront = txtData.find(win, findFront + 1) + 5;
			findBack = txtData.find(last, findBack + 1);
			lenght = findBack - findFront;
			dataScore[i].winner = stoi(txtData.substr(findFront, lenght));
		}
	}

	// Set Last match data for resume data
	void setLastMatchData(string xN, string oN, int turn, int data[6][14]) {
		theLastMatch.xName = xN;
		theLastMatch.oName = oN;
		theLastMatch.xTurn = turn;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				theLastMatch.arenaData[i][j] = data[i][j];
			}
		}		
	}

	// Set Last match data to null (no resume data)
	void resetLastMatchData() {
		theLastMatch.xName = "null";
		theLastMatch.oName = "null";
		theLastMatch.xTurn = 1;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				theLastMatch.arenaData[i][j] = 0;
			}
		}
	}

	// Add new data score
	void setDataScore(string xN, string oN, int wN) {
		// New data will added on the top
		dataScore[1].xName = dataScore[0].xName;
		dataScore[1].oName = dataScore[0].oName;
		dataScore[1].winner = dataScore[0].winner;

		dataScore[0].xName = xN;
		dataScore[0].oName = oN;
		dataScore[0].winner = wN;

		// Move Back all data (data 2->3; data 3->4 ...)
		for (int i = 99; i > 1; i--) {
			dataScore[i].xName = dataScore[i - 1].xName;
			dataScore[i].oName = dataScore[i - 1].oName;
			dataScore[i].winner = dataScore[i - 1].winner;
		}
	}

	// Get function
	string getLastMatchXName() {
		return theLastMatch.xName;
	}

	// Get function
	string getLastMatchOName() {
		return theLastMatch.oName;
	}

	int getLastMatchTrun() {
		return theLastMatch.xTurn;
	}

	// Get function
	int getLastMatchArena(int x, int y) {
		return theLastMatch.arenaData[x][y];
	}

	// Save the data to file txt
	void saveGame() {
		// Open file
		ofstream fileOut;
		fileOut.open(fileName);

		// Add new data to txt file
		fileOut << data << endl;

		// Last Match data
		fileOut << lastXName << theLastMatch.xName;
		fileOut << lastOName << theLastMatch.oName;
		fileOut << lastData;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				fileOut << to_string(theLastMatch.arenaData[i][j]);
			}
		}
		fileOut << last << endl;

		// Score data
		for (int i = 0; i < 100; i++) {
			fileOut << xNam << dataScore[i].xName;
			fileOut << oNam << dataScore[i].oName;
			fileOut << win << to_string(dataScore[i].winner);
			fileOut << last << endl;
		}

		fileOut << close;

		// Close txt file
		fileOut.close();
	}

	// Show the scoreboard
	void showScoreboard() {
		system("cls");
		cout << "                 Scoreboard\n\n";
		cout << "     x Player            o Player            Winner\n";
		
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 50;) {
				if (j == 5) {
					cout << dataScore[i].xName;
					j += dataScore[i].xName.size();
				}
				else if (j == 25) {
					cout << dataScore[i].oName;
					j += dataScore[i].oName.size();
				}
				else if (j == 45) {
					if (dataScore[i].winner == 1) {
						cout << "x Player\n";
					}
					else if (dataScore[i].winner == 2) {
						cout << "o Player\n";
					}
					else {
						cout << "Draw\n";
					}
					j = 60;
				}
				else {
					cout << " ";
					j++;
				}
			}
		}
		cout << endl;

		system("pause");
	}
};
