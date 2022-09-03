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

// Pointers to the previous, current and next state
IGameState *pre, *cur, *nxt;

// Setting Reserved Pointers QUIT and RESTART
// These addresses are protected by system, so they are impossible values
IGameState *QUIT = (IGameState*) 1, *RESTART = (IGameState*) 2;

// doubles keeping track of frame and app time
double frameTime = 0.0, appTime = 0.0;

void LEDA::LEDA_INIT(bool showConsole, double frameRate, std::string windowTitle, IGameState *initialState) {

	std::cout << "LEDA runs!\n";

	// Initializes all our systems

	// Sets initial game state
	pre = cur = nxt = initialState;

	while (cur != QUIT) { // while the application is not quitted yet

		// reset the system modules
		

		// If not restarting, load the new Game State
		if (cur != RESTART) cur->load();
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

		if (nxt != RESTART) cur->unload();

		pre = cur;
		cur = nxt;
	}

	// Exits the system
}