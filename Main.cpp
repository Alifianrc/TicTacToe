#include "Arena.h"
#include "ThePlayer.h"
#include "ScoreBoard.h"

using namespace std;

class TicTacToe : public Boxes, public Player, public scoreBoards {
private:
	bool inMenu, isQuit, inGame;
	int arenaData[6][14];

	// For Menu
	char menuInput;
	int menuA;

	// Cursor position
	int cursorPosition[1][2];
	
	// Step
	int stepCount = 0;
	bool gameOver;
	int winner;
	bool stopGame;
	
public:
	// Constructor
	TicTacToe() {
		// Game not started yet
		inMenu = true;
		isQuit = false;
		gameOver = false;
		inGame = false;
		stopGame = false;

		// Load game data
		loadData();

		// Cursor deafult
		cursorPosition[0][0] = 1;
		cursorPosition[0][1] = 2;

		// Menu default
		menuA = 0;

		// Arena default
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				if (cursorPosition[0][0] == i && cursorPosition[0][1] == j) {
					arenaData[i][j] = 3;
				}
				else {
					arenaData[i][j] = 0;
				}			
			}
		}
		// Set Dasar Arena
		setBox(arenaData);

		// Draw Menu
		drawMenu(menuA);
	}

	// For menu
	void mainMenu() {
		menuInput = getInput();
		int a = menuA;

		// Cursor go up
		if (menuInput == 'w') {
			menuA--;
			if (menuA < 0) {
				menuA = 3;
			}
			drawMenu(menuA);
		}
		// Cursor go down
		else if (menuInput == 's') {
			menuA++;
			if (menuA > 3) {
				menuA = 0;
			}
			drawMenu(menuA);
		}
		// If 'enter'
		else if (menuInput == 'a' || menuInput == 'd' || menuInput == '\r') {
			system("cls");
			// Adjust user input
			if (menuA == 0) {
				// Resume last match
				resumeGame();
			}
			else if (menuA == 1) {
				// New game, input Name
				inputName();

				inMenu = false;
				inGame = true;
				drawBoxes();

				// Temporary
				menuA = 0;
			}
			else if (menuA == 2) {
				// Show scoreboard
				showScoreboard();

				drawMenu(menuA);
			}
			else if (menuA == 3) {
				// Exit Game
				exit(0);
			}
			
		}
	}
	// Drawing menu UI
	void drawMenu(int a) {
		system("cls");
		if (a == 0) {
			cout << "     Resume <<<\n"
				<< "    New Game \n"
				<< "   Scoreboard \n"
				<< "      Quit \n";
		}
		else if (a == 1) {
			cout << "     Resume \n"
				<< "    New Game <<<\n"
				<< "   Scoreboard \n"
				<< "      Quit \n";
		}
		else if (a == 2) {
			cout << "     Resume \n"
				<< "    New Game \n"
				<< "   Scoreboard <<<\n"
				<< "      Quit \n";
		}
		else if (a == 3) {
			cout << "     Resume \n"
				<< "    New Game \n"
				<< "   Scoreboard \n"
				<< "      Quit <<<\n";
		}
	}

	// For resume game
	void resumeGame() {
		int arenaXCount = 0, arenaOCount = 0;

		// Load last arena
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				arenaData[i][j] = getLastMatchArena(i, j);
				// Set cursor
				if (arenaData[i][j] == 3) {
					cursorPosition[0][0] = i;
					cursorPosition[0][1] = j;
				}

				// Check arena condition
				if (arenaData[i][j] == 1) {
					arenaXCount++;
				}
				else if (arenaData[i][j] == 2) {
					arenaOCount++;
				}
			}
		}

		// Can't resume if arena data empty
		if (arenaXCount == 0 && getLastMatchXName() == "null" && getLastMatchOName() == "null") {
			drawMenu(menuA);
			cout << "\n     No resume data";
		}

		else {
			// Set witch turn
			if (arenaXCount > arenaOCount) {
				setXTurn(false);
			}
			else if (arenaXCount < arenaOCount) {
				setXTurn(true);
			}
			else {
				setXTurn(true);
			}
			
			// Set stepCount
			stepCount = arenaXCount + arenaOCount;

			// Set arena data
			setBox(arenaData);

			// Set player name
			setPlayerName(getLastMatchXName(), getLastMatchOName());

			// Diactivate menu
			inMenu = false;
			inGame = true;
			drawBoxes();
		}	
	}

	// For Game
	void mainGame() {
		bool isUpdate = gameInput();

		if (isUpdate && !gameOver) {
			updateMap();
			gameOver = checkWin();
			drawBoxes();			
		}
		else if (gameOver) {
			if (winner == 1) {
				cout << "    Winner is x";
			}
			else if (winner == 2) {
				cout << "    Winner is o";
			}
			else {
				cout << "        Draw";
			}
			cout << "\n\n";

			// Reset last Match data???
			resetLastMatchData();

			// Save the game
			setDataScore(getXName(), getOName(), winner);
			saveGame();

			// Setting bool
			inGame = false;
			inMenu = true;
			gameOver = false;

			// Restart The game data
			restartGame();

			// Pause the screen
			system("pause");
			drawMenu(menuA);
		}
		else if (stopGame) {
			// Save match
			int turn;
			if (getXturn()) {
				turn = 1;
			}
			else {
				turn = 2;
			}
			setLastMatchData(getXName(), getOName(), turn, arenaData);
			saveGame();

			// Setting bool
			inGame = false;
			inMenu = true;
			stopGame = false;

			// Restart The game data
			restartGame();

			drawMenu(menuA);
		}
	}
	// For input user
	bool gameInput() {
		bool update = false;
		char input = getInput();
		if (input == 'w') {
			if (cursorPosition[0][0] != 1) {
				cursorPosition[0][0] -= 2;
			}
			update = true;
		}
		else if (input == 'a') {
			if (cursorPosition[0][1] != 2) {
				cursorPosition[0][1] -= 4;
			}
			update = true;
		}
		else if (input == 's') {
			if (cursorPosition[0][0] != 5) {
				cursorPosition[0][0] += 2;
			}
			update = true;
		}
		else if (input == 'd') {
			if (cursorPosition[0][1] != 10) {
				cursorPosition[0][1] += 4;
			}
			update = true;
		}
		else if (input == '\r') {
			// Assign Pon
			if (!getArenaLock((cursorPosition[0][0] - 1), cursorPosition[0][1])) {
				if (getXturn()) {
					arenaData[(cursorPosition[0][0] - 1)][cursorPosition[0][1]] = 1;
					setXturn();
				}
				else {
					arenaData[(cursorPosition[0][0] - 1)][cursorPosition[0][1]] = 2;
					setXturn();
				}
				stepCount++;
			}
			update = true;
		}
		else if (input == 'p') {
			// Game stopped
			stopGame = true;
		}

		return update;
	}
	// Update map
	void updateMap() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				// Update cursor position
				if (cursorPosition[0][0] == i && cursorPosition[0][1] == j) {
					arenaData[i][j] = 3;
				}
				// Delete last cursor position
				else if (i == 1 || i == 3 || i == 5) {
					arenaData[i][j] = 0;
				}
			}
		}
		// Update 
		setBox(arenaData);
	}
	// Check win condition
	bool checkWin() {
		// Draw case
		if (stepCount >= 9) {
			winner = 4;
			return true;
		}

		int x = 0, y = 2;
		// Check column
		for (int i = 0; i < 3; i++) {
			if (arenaData[x][y] == arenaData[x][y + 4] && arenaData[x][y] == arenaData[x][y + 8] && arenaData[x][y] != 0) {
				// Winner is...
				if (arenaData[x][y] == 1) {
					// ... x
					winner = 1;
				}
				else if (arenaData[x][y] == 2) {
					// ... o
					winner = 2;
				}
				return true;
				break;
			}
			x += 2;
		}


		// Check line
		x = 0; y = 2;
		for (int i = 0; i < 3; i++) {
			if (arenaData[x][y] == arenaData[x + 2][y] && arenaData[x][y] == arenaData[x + 4][y] && arenaData[x][y] != 0) {
				// Winner is...
				if (arenaData[x][y] == 1) {
					// ... x
					winner = 1;
				}
				else if (arenaData[x][y] == 2) {
					// ... o
					winner = 2;
				}
				return true;
				break;
			}
			y += 4;
		}

		// Check diagonaly
		if (arenaData[0][2] == arenaData[2][6] && arenaData[0][2] == arenaData[4][10] && arenaData[0][2] != 0) {
			// Winner is...
			if (arenaData[0][2] == 1) {
				// ... x
				winner = 1;
			}
			else if (arenaData[0][2] == 2) {
				// ... o
				winner = 2;
			}
			return true;
		}
		else if (arenaData[4][2] == arenaData[2][6] && arenaData[4][2] == arenaData[0][10] && arenaData[4][2] != 0) {
			// Winner is...
			if (arenaData[4][2] == 1) {
				// ... x
				winner = 1;
			}
			else if (arenaData[4][2] == 2) {
				// ... o
				winner = 2;
			}
			return true;
		}
		else {
			return false;
		}
	}
	// Reset game to next play
	void restartGame() {
		// Cursor deafult
		cursorPosition[0][0] = 1;
		cursorPosition[0][1] = 2;

		// Set xTurn
		setXTurn(true);

		// Reset stepCount
		stepCount = 0;

		// Arena default
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 14; j++) {
				if (cursorPosition[0][0] == i && cursorPosition[0][1] == j) {
					arenaData[i][j] = 3;
				}
				else {
					arenaData[i][j] = 0;
				}
			}
		}
		// Set Dasar Arena
		setBox(arenaData);
	}

	// Looping Game in here
	void update() {
		while (!isQuit) {
			// Menu function
			if (inMenu) {
				mainMenu();
			}

			// Game function
			else if (inGame) {
				mainGame();
			}			
		}
	}
};


int main() {
	// Just need to call update
	TicTacToe game;
	game.update();

	return 0;
}