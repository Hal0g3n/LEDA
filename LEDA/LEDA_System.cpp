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
#include <typeinfo>
#include "LEDA_System.h"
#include "ISystem.h"

using namespace LEDA;

// doubles keeping track of frame and app time
double frameTime = 0.0, appTime = 0.0;

// Tracking Previous, Current and Next GameStates
IGameState *pre, *cur, *nxt;


// List of Systems
std::vector<ISystem *> systems;

void LEDA::LEDA_INIT(bool showConsole, double frameRate, std::string windowTitle, IGameState* initialState) {

	std::cout << "LEDA runs!\n";

	// Sets initial game state
	pre = cur = nxt = initialState;

	while (cur != Quit_GameState) { // while the application is not quitted yet

		// Initializes all our systems for the current state
		for (ISystem* system : systems) system->init();
		

		//loadGameState();


		while (cur == nxt) { // While State is unchanged

			// Start Frame Timer
			// AESysFrameStart();

			// System Game Loop Updates
			for (ISystem* system : systems) system->update();

			
			// End Frame Timer
			// AESysFrameEnd();

			// Check for Forced Exit
			// if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
			// 	nxt = QUIT;

			// frameTime = (f32)AEFrameRateControllerGetFrameTime();
			// appTime += frameTime;
		}

		if (nxt != Restart_GameState) cur->unload();

		pre = cur;
		cur = nxt;
	}

	// Destroys all systems
	for (ISystem* system : systems) system->destroy();
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

// GameObject Manager Functions //
std::map<std::string, IGameObject*> objects;

void LEDA::registerGameObject(std::string id, IGameObject* obj) {
	// Registers the object to each system
	for (ISystem* system : systems) 
		system->registerGameObject(obj);
}

IGameObject* LEDA::retrieveGameObject(std::string id) { 
	return (objects.find(id) == objects.end()) ? nullptr : objects.find(id)->second; 
}