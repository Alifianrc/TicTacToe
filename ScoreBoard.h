#include <string>
#include <fstream>
#include <iostream>
#include <vector>
// 4210191011 Alifian
using namespace std;

// Class Scoreboard
class ScoreBoards {
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

	// For file txt last match
	string lastXName, lastOName, lastData;

	// For saving data copy from txt
	string txtData;
	int MAX;
	char temp[1000];
	vector<int> lastMatchData;

public:

	// Constructor
	ScoreBoards() {
		data = "<Data>";
		xNam = "<xName>";
		oNam = "<oName>";
		win = "<win>";
		last = "<last>";
		close = "<Close>";

		fileName = "D:\\Tugas_Kuliah\\Pemrograman_4\\Minggu2\\TicTacToe\\score_data.txt";
		MAX = 1000;
		//temp[1000];

		lastXName = "<lastXName>";
		lastOName = "<lastOName>";
		lastData = "<lastData>";
	}

	// Load data from txt and get scoreboard data
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

	// Get last match x name from data
	string GetLastMatchXName() {
		int findFront = 0, findBack = 0, lenght;
		
		findFront = txtData.find(lastXName, findFront + 1) + 11;
		findBack = txtData.find(lastOName, findBack + 1);
		lenght = findBack - findFront;
		string data = txtData.substr(findFront, lenght);
		return data;
	}

	// Get last match x name from data
	string GetLastMatchOName() {
		int findFront = 0, findBack = 0, lenght;

		findFront = txtData.find(lastOName, findFront + 1) + 11;
		findBack = txtData.find(lastData, findBack + 1);
		lenght = findBack - findFront;
		string data = txtData.substr(findFront, lenght);
		return data;
	}

	// Get last match data from data
	int GetLastMatchData(int x) {
		int findFront = 0;

		findFront = txtData.find(lastData, findFront + 1) + 10 + x;
		int data = stoi(txtData.substr(findFront, 1));

		return data;
	}

	// Add new data score
	void setDataScore(string xN, string oN, int wN) {
		
		// Move Back all data (data 2->3; data 3->4 ...)
		for (int i = 99; i > 0; i--) {
			dataScore[i].xName = dataScore[i - 1].xName;
			dataScore[i].oName = dataScore[i - 1].oName;
			dataScore[i].winner = dataScore[i - 1].winner;
		}
	
		dataScore[0].xName = xN;
		dataScore[0].oName = oN;
		dataScore[0].winner = wN;		
	}

	// Get data from Boxes class and save it in vector
	void saveArenaData(int value) {
		lastMatchData.push_back(value);
	}

	// Save the data to file txt
	void saveGame(string lastXNameData, string lastONameData) {
		// Open file
		ofstream fileOut;
		fileOut.open(fileName);

		// Add new data to txt file
		fileOut << data << endl;

		// Last Match data
		
		fileOut << lastXName << lastXNameData;
		fileOut << lastOName << lastONameData;
		fileOut << lastData;
		for (int i = 0; i < lastMatchData.size(); i++) {
			fileOut << to_string(lastMatchData[i]);
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

		// Reset Vector
		lastMatchData.clear();

		// Reset txtData
		txtData = "";
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
