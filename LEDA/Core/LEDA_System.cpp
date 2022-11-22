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

// include all the systems too
#include "LogicSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"

// to set window title
#include "LEDA_Graphics.h"

#include <string>

using namespace LEDA;

// doubles keeping track of frame and app time
double frameTime = 0.0, appTime = 0.0;

// Tracking Previous, Current and Next GameStates
std::string pre, cur, nxt;

// Frame rate variables
std::chrono::time_point<std::chrono::system_clock> frameStartTime;

// i moved this to the top to avoid error
std::map<std::string, GameObject*> objects;


// List of Systems
std::vector<ISystem*> systems{
	new LogicSystem(),
	new GraphicsSystem(),
	new PhysicsSystem(),
};

void LEDA::LEDA_INIT(bool showConsole, double frameRate, std::string windowTitle, std::string initialState) {

	std::cout << "LEDA runs!\n";

	pre = cur = nxt = initialState;

	// set window title
	LEDA::windowTitle = windowTitle;

	// Initialize important managers
	SceneManager sm{};
	// TODO: We need a window manager?
	
	// initializes all systems (for the current state)
	for (ISystem* system : systems) {
		system->init();
	}

	while (cur != "quit") { // While the application is not quitted yet

		// Scene Load/Initialize (Scene Manager Load level)
		sm.load(cur + ".json");

		while (cur == nxt) { // While state is unchanged

			// Start Frame Timer
			frameStartTime = std::chrono::system_clock::now();

			// System Game Loop Updates
			for (ISystem* system : systems) {
				system->update();
			}
			
			// End Frame Timer
			frameTime = (std::chrono::system_clock::now() - frameStartTime).count();

			// check for forced exit (full of AE)
			// if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
			//  	nxt = "quit";

			// loop until frame time is over
			while ((std::chrono::system_clock::now() - frameStartTime).count() < 1 / frameRate);

			appTime += frameTime;
		}

		// Clear all loaded objects
		for (std::pair<std::string, GameObject*> pairs : objects) removeGameObject(pairs.second);

		// Assets Manager Unload level (Persistent Assets)
		if (nxt != "reset") nxt = cur; // Set up to load same file again

		// Free all our systems for the current state
		for (ISystem* system : systems) system->free();

		// Setting up for next loop
		pre = cur;
		cur = nxt;

	}

	// Destroys all systems
	for (ISystem* system : systems) {
		delete system;
	}

}

// Replace with SceneManager->onSceneEnter(state);
// Exposes certain GameState values for usage
std::string LEDA::getPreviousGameStateFile()		{ return pre; }
std::string LEDA::getCurrentGameStateFile()			{ return cur; }
std::string LEDA::getNextGameStateFile()			{ return nxt; }
void LEDA::setNextGameStateFile(std::string state)  { nxt = state; }

// SceneManager Functions //
std::unordered_map<std::string, GameObject*> objects;

void LEDA::registerGameObject(std::string id, GameObject* obj) {
	// Delete before replace
	delete retrieveGameObject(id);

	// Registers the object to each system
	for (ISystem* system : systems) 
		system->onRegisterGameObject(obj);

	objects.emplace(id, obj);
}

bool LEDA::removeGameObject(GameObject* obj) {
	for (ISystem* sys : systems) sys->onRemoveGameObject(obj);

	// Erase from mapping
	objects.erase(obj->getId());

	// Delete the object
	delete obj;
}

GameObject* LEDA::retrieveGameObject(std::string id) { 
	return (objects.find(id) == objects.end()) ? nullptr : objects.find(id)->second; 
}