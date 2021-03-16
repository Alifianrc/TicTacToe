#include <iostream>
#include <conio.h>
// 4210191024 Andhika

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
