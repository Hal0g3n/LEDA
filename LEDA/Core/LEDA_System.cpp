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

#include "SceneManager.h"

// include all the systems too
#include "LogicSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"

// to set window title
#include "LEDA_Graphics.h"

using namespace LEDA;

/****************************
*   File Scope Variables    *
****************************/

extern double LEDA::frameTime = 0.0, LEDA::appTime = 0.0;

// Tracking Previous, Current and Next GameStates
std::string pre, cur, nxt;

// Frame rate variables
std::chrono::time_point<std::chrono::system_clock> frameStartTime;

// Game Objects List
std::unordered_map<std::string, GameObject*> objects;

extern LEDA::SceneManager sceneManager;

/****************************
*   Main System Functions   *
****************************/

// List of Systems
std::vector<ISystem*> systems{
	new LogicSystem(),
	new GraphicsSystem(),
	new PhysicsSystem(),
};

// why china
void china() {}

void LEDA::LEDA_INIT(std::string state, std::function<void(void)> fn) {
	// it works
	startFunctions.insert(std::make_pair(state, fn));
}

void LEDA::LEDA_START(bool showConsole, double frameRate, std::string windowTitle, std::string initialState) {

	std::cout << "LEDA runs!" << std::endl;

	pre = cur = nxt = initialState;

	// set window title
	LEDA::windowTitle = windowTitle;

	// scene manager
	LEDA::sceneManager = new SceneManager{};

	// TODO: We need a window manager?
	
	// initializes all systems (for the current state)
	for (ISystem* system : systems) {
		system->init();
	}

	while (cur != "quit") { // While the application is not quitted yet

		std::cout << "Loading scene '" << cur << "'..." << std::endl;

		// Scene Load/Initialize (Scene Manager Load level)
		sceneManager->load(cur + ".json");

		// something to make it work
		std::unordered_map<std::string, std::function<void(void)>>::iterator something_iterator = startFunctions.find(cur);
		if (something_iterator != startFunctions.end()) {
			// i hope this works
			something_iterator->second();
		}

		while (cur == nxt) { // While state is unchanged

			// Start Frame Timer
			frameStartTime = std::chrono::system_clock::now();

			// System Game Loop Updates
			for (ISystem* system : systems) {
				system->update();
			}
			
			// End Frame Timer
			frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - frameStartTime).count() / 1e9;

			// if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
			//  	nxt = "quit";

			// loop until frame time is over
			while (frameTime < 1.0 / frameRate) {
				frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - frameStartTime).count() / 1e9;
			}

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

	delete sceneManager;

}

// Replace with SceneManager->onSceneEnter(state);
// Exposes certain GameState values for usage
std::string LEDA::getPreviousGameStateFile()		{ return pre; }
std::string LEDA::getCurrentGameStateFile()			{ return cur; }
std::string LEDA::getNextGameStateFile()			{ return nxt; }
void LEDA::setNextGameStateFile(std::string state)  { nxt = state; }

// SceneManager Functions //
void LEDA::registerGameObject(std::string id, GameObject* obj) {
	
	// check if an object with the same id already exists
	if (objects.find(id) != objects.end()) {
		LOG_WARNING("GameObject with id \"" + id + "\" exists! (replacing with newer object)");
		removeGameObject(id);
	}

	// Registers the object to each system
	for (ISystem* system : systems) {
		system->onRegisterGameObject(obj);
	}

	objects.emplace(id, obj);

}

bool LEDA::removeGameObject(GameObject* obj) {
	if (obj == nullptr) return false;

	for (ISystem* sys : systems) sys->onRemoveGameObject(obj);
	
	// remove all components from object first
	deleteAllComponents(obj);

	// Erase from mapping
	objects.erase(obj->getId());

	// Delete the object
	delete obj;

	return true;
}

bool LEDA::removeGameObject(std::string id) {
	GameObject* obj = retrieveGameObject(id);
	return obj ? removeGameObject(obj) : false;
};

GameObject* LEDA::retrieveGameObject(std::string id) { 
	return (objects.find(id) == objects.end()) ? nullptr : objects.find(id)->second; 
}

void LEDA::LOG_WARNING(std::string msg) {
	std::cerr << "[LEDA WARNING]: " << msg << '\n';
}