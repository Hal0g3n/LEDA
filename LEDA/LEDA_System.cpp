/**
 * @file        LEDA_System.cpp
 * @author      your name (you@domain.com)
 * @brief       Implementation of Main Game Loop
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"
#include "LEDA_System.h"

using namespace LEDA;

// doubles keeping track of frame and app time
double frameTime = 0.0, appTime = 0.0;

// Tracking Previous, Current and Next GameStates
IGameState *pre, *cur, *nxt;

void LEDA::LEDA_INIT(bool showConsole, double frameRate, std::string windowTitle, IGameState* initialState) {

	std::cout << "LEDA runs!\n";

	// Initializes all our systems

	// Sets initial game state
	pre = cur = nxt = initialState;

	while (cur != Quit_GameState) { // while the application is not quitted yet

		// reset the system modules
		

		// If not restarting, load the new Game State
		if (cur != Restart_GameState) cur->load();
		else nxt = cur = pre;

		// Initialize the gamestate
		cur->init();

		while (cur == nxt) { // While State is unchanged

			// Start Frame Timer
			// AESysFrameStart();

			cur->update();
			cur->draw();
			
			// End Frame Timer
			// AESysFrameEnd();

			// Check for Forced Exit
			// if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
			// 	nxt = QUIT;

			// frameTime = (f32)AEFrameRateControllerGetFrameTime();
			// appTime += frameTime;
		}

		cur->free();

		if (nxt != Restart_GameState) cur->unload();

		pre = cur;
		cur = nxt;
	}

	// Exits the system
}

// GameStateManager Functions //
std::map<std::string, IGameState*> states;

// Stores States
bool LEDA::registerGameState(std::string id, IGameState* state) {
	// Already Exists
	if (states.find(id) != states.end()) return false;

	// Register the Game State
	states.insert({ id, state });
	return true;
}

// Retrieves registered states
IGameState* LEDA::retrieveGameState(std::string id) {
	if (states.find(id) == states.end()) return 0;
	else return states.find(id)->second;
}

// Exposes certain GameState values for usage
IGameState* LEDA::getPreviousGameState()		  { return pre; }
IGameState* LEDA::getCurrentGameState()		  { return cur; }
IGameState* LEDA::getNextGameState()			  { return nxt; }
void LEDA::setNextGameState(IGameState* state)  { nxt = state; }