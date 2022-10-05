/**
 * @file        LEDA_Input.cpp
 * @author      your name (you@domain.com)
 * @brief       Implements some input functions
 * @version     0.1
 * @date        06-09-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#include "pch.h"
#include "LEDA_Input.h"

using namespace LEDA;
using namespace LEDA::input;

// how to store key trigger/release callback functions:

using callbackMap = std::map<int, std::vector<emptyFunction>>;

callbackMap triggerCallbacks;
callbackMap releaseCallbacks;
callbackMap repeatCallbacks;


// for (storage purposes; how to iterate through all KEY::s; is shown in the comment below) { ignore all punctuation in this line }
/*
	for (int k = KEY::KEY_SPACE; k < KEY::KEY_LAST; k++)
*/


void mainKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		callbackMap::iterator found = triggerCallbacks.find(key);
		if (found != triggerCallbacks.end()) {
			for (emptyFunction function : (*found).second) {
				function();
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		callbackMap::iterator found = releaseCallbacks.find(key);
		if (found != releaseCallbacks.end()) {
			for (emptyFunction function : (*found).second) {
				function();
			}
		}
	}
	else if (action == GLFW_REPEAT) {
		callbackMap::iterator found = repeatCallbacks.find(key);
		if (found != repeatCallbacks.end()) {
			for (emptyFunction function : (*found).second) {
				function();
			}
		}
	}
	return;
}


void LEDA::input::initializeInput(bool stickyKeys) {

	// set GLFW input modes below

	if (stickyKeys) {
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	} else {
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
	}
	// the last 5 lines can be shortened to 1...
	
	// caps lock and num lock status will be detected in input events
	glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE); // why not

	// set the main key callback
	glfwSetKeyCallback(window, mainKeyCallback);

	return;

}

void LEDA::input::doInput() {

	// processes received events in the event queue (calling key callbacks)
	glfwPollEvents();
	
	return;

}


bool LEDA::input::keyPressed(LEDA::input::KEY key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool LEDA::keyRepeated(LEDA::input::KEY key) {
	return glfwGetKey(window, key) == GLFW_REPEAT;
}


// use key callbacks instead of triggered/released

/*

bool LEDA::keyTriggered(LEDA::KEY key) {
	return glfwGetKey(window, key) == GLFW_PRESSED;
}

bool LEDA::keyReleased(LEDA::KEY key) {
	return glfwGetKey(window, key) == GLFW_RELEASE;
}

*/


// functions to add key callbacks

void LEDA::input::addKeyTriggerCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = triggerCallbacks.find(key);
	if (found == triggerCallbacks.end()) {
		std::vector<emptyFunction> tempVector;
		triggerCallbacks.emplace(key, tempVector);
		found = triggerCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}

void LEDA::input::addKeyReleaseCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = releaseCallbacks.find(key);
	if (found == releaseCallbacks.end()) {
		std::vector<emptyFunction> tempVector;
		releaseCallbacks.emplace(key, tempVector);
		found = releaseCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}

void LEDA::input::addKeyRepeatCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = repeatCallbacks.find(key);
	if (found == repeatCallbacks.end()) {
		std::vector<emptyFunction> tempVector;
		repeatCallbacks.emplace(key, tempVector);
		found = repeatCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}


// functions to remove key callbacks

void LEDA::input::removeKeyTriggerCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = triggerCallbacks.find(key);
	if (found == triggerCallbacks.end()) {
		// there's nothing to remove!
		return;
	}
	std::vector<emptyFunction> vector = found->second;
	std::vector<emptyFunction>::iterator foundAgain = std::find(vector.begin(), vector.end(), function);
	if (foundAgain != vector.end()) {
		// only remove if the function is found
		vector.erase(foundAgain);
	}
	return;

}

void LEDA::input::removeKeyReleaseCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = releaseCallbacks.find(key);
	if (found == releaseCallbacks.end()) {
		// there's nothing to remove!
		return;
	}
	std::vector<emptyFunction> vector = found->second;
	std::vector<emptyFunction>::iterator foundAgain = std::find(vector.begin(), vector.end(), function);
	if (foundAgain != vector.end()) {
		// only remove if the function is found
		vector.erase(foundAgain);
	}
	return;

}

void LEDA::input::removeKeyRepeatCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = repeatCallbacks.find(key);
	if (found == repeatCallbacks.end()) {
		// there's nothing to remove!
		return;
	}
	std::vector<emptyFunction> vector = found->second;
	std::vector<emptyFunction>::iterator foundAgain = std::find(vector.begin(), vector.end(), function);
	if (foundAgain != vector.end()) {
		// only remove if the function is found
		vector.erase(foundAgain);
	}
	return;

}