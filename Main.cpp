#include "Arena.h"
#include "ThePlayer.h"
#include "ScoreBoard.h"

using namespace std;

class TicTacToe : public Boxes, public Player, public scoreBoards {
private:
	bool inMenu, isQuit, inGame;
	
	// For Menu
	char menuInput;
	int menuA;
	
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

		// Menu default
		menuA = 0;

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
		setPlayerName(GetLastMatchXName(), GetLastMatchOName());
		int tempCount = 0;
		for (int i = 0; i < boxSize; i++) {
			for (int j = 0; j < boxSize; j++) {
				int data = GetLastMatchData(tempCount);
				tempCount++;
				SetArenaData(i, j, data);

				if (data == 1) {
					arenaXCount++;
				}
				else if(data == 2) {
					arenaOCount++;
				}
			}
		}

		// Can't resume if arena data empty
		if (getXName() == "null" && getOName() == "null") {
			drawMenu(menuA);
			cout << "\n     No resume data";
		}
		// If data wasn't empty
		else {
			// Set witch turn
			if (arenaXCount > arenaOCount) {
				setXTurn(false);
			}
			else {
				setXTurn(true);
			}
			
			// Set stepCount
			stepCount = arenaXCount + arenaOCount;

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
			drawBoxes();
			gameOver = checkWin();
		}
		// Game is Finish
		else if (gameOver) {
			// Show Winner
			if (winner == 1) {
				cout << "    Winner is x";
			}
			else if (winner == 2) {
				cout << "    Winner is o";
			}
			else if (winner == 3) {
				cout << "        Draw";
			}
			cout << "\n\n";

			// Change scoreboard
			setDataScore(getXName(), getOName(), winner);

			// Save the game and reset last match data to null (can't resume)
			for (int i = 0; i < boxSize; i++) {
				for (int j = 0; j < boxSize; j++) {
					saveArenaData(0);
				}
			}
			saveGame("null", "null");

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
		// Player press p
		else if (stopGame) {
			// Save the game
			for (int i = 0; i < boxSize; i++) {
				for (int j = 0; j < boxSize; j++) {
					saveArenaData(getArenaData(i, j));
				}
			}
			saveGame(getXName(), getOName());

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
			if (getCursorLoaction(0, 0) != 0) {
				setCursorLocation(0, 0, 0);
			}
			update = true;
		}
		else if (input == 'a') {
			if (getCursorLoaction(0, 1) != 0) {
				setCursorLocation(0, 1, 0);
			}
			update = true;
		}
		else if (input == 's') {
			if (getCursorLoaction(0, 0) != (boxSize - 1)) {
				setCursorLocation(0, 0, 1);
			}
			update = true;
		}
		else if (input == 'd') {
			if (getCursorLoaction(0, 1) != (boxSize - 1)) {
				setCursorLocation(0, 1, 1);
			}
			update = true;
		}
		else if (input == '\r') {
			bool ponAssigned = false;
			// Assign Pon
			ponAssigned = AssignPon();
			if (ponAssigned == true) {
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
	// Check win condition
	bool checkWin() {
		// Draw case
		if (stepCount >= (boxSize * boxSize)) {
			winner = 3;
			return true;
		}

		// Check column
		int correctCount = 0;
		for (int i = 0; i < boxSize; i++) {
			for (int j = 0; j < (boxSize - 1); j++) {
				if (getArenaData(i, j) == getArenaData(i, j + 1) && getArenaData(i, j) != 0) {
					correctCount++;
				}
			}
			if (correctCount == (boxSize - 1)) {
				winner = getArenaData(i, 0);
				return true;
			}
			else {
				correctCount = 0;
			}
		}


		// Check line
		for (int i = 0; i < boxSize; i++) {
			for (int j = 0; j < (boxSize - 1); j++) {
				if (getArenaData(j, i) == getArenaData(j + 1, i) && getArenaData(j, i) != 0) {
					correctCount++;
				}
			}
			if (correctCount == (boxSize - 1)) {
				winner = getArenaData(0, i);
				return true;
			}
			else {
				correctCount = 0;
			}
		}

		// Check diagonaly
		for (int i = 0; i < (boxSize - 1); i++) {
			if (getArenaData(0, 0) == getArenaData(i + 1, i + 1) && getArenaData(0, 0) != 0) {
				correctCount++;
			}
			if (correctCount == (boxSize - 1)) {
				winner = getArenaData(0, 0);
				return true;
			}
			else {
				correctCount = 0;
			}
		}

		int j = 1;
		for (int i = (boxSize - 1); i > 0; i--) {
			if (getArenaData(0, boxSize - 1) == getArenaData(j, i - 1) && getArenaData(0, boxSize - 1) != 0) {
				correctCount++;
			}
			if (correctCount == (boxSize - 1)) {
				winner = getArenaData(0, boxSize - 1);
				return true;
			}
			j++;
		}

		return false;
	}
	// Reset game to next play
	void restartGame() {
		// Cursor deafult
		SetCursorToDefault();

		// Arena to default
		SetArenaToDefault();

		// Set xTurn
		setXTurn(true);

		// Reset stepCount
		stepCount = 0;	

		// Load a New Game data
		loadData();
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