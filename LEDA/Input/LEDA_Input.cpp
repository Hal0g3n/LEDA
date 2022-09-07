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

// how to store key trigger/release callback functions:

using callbackMap = std::map<int, std::vector<emptyFunction>>;

callbackMap triggerCallbacks;
callbackMap releaseCallbacks;


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
	return;
}


void LEDA::initializeInput(bool stickyKeys) {

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

void LEDA::doInput() {

	// processes received events in the event queue (calling key callbacks)
	glfwPollEvents();
	
	return;

}


bool LEDA::keyPressed(LEDA::KEY key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool LEDA::keyRepeated(LEDA::KEY key) {
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

void LEDA::addKeyTriggerCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = triggerCallbacks.find(key);
	if (found == triggerCallbacks.end()) {
		std::vector<emptyFunction> tempVector;
		triggerCallbacks.emplace(key, tempVector);
		found = triggerCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}

void LEDA::addKeyReleaseCallback(KEY key, emptyFunction function) {

	callbackMap::iterator found = releaseCallbacks.find(key);
	if (found == releaseCallbacks.end()) {
		std::vector<emptyFunction> tempVector;
		releaseCallbacks.emplace(key, tempVector);
		found = releaseCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}


// functions to remove key callbacks

void LEDA::removeKeyTriggerCallback(KEY key, emptyFunction function) {

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

void LEDA::removeKeyReleaseCallback(KEY key, emptyFunction function) {

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