#include <iostream>
#include <conio.h>
// Andhika

using namespace std;

class Player {
private:
	string name;

public:
	// Get function
	string getName() {
		return name;
	}

	// Reload resume game
	void setPlayerName(string nam) {
		name = nam;
	}	
};
