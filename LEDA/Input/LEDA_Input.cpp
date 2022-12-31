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

#include "LEDA_System.h"
#include "LEDA_Input.h"

using namespace LEDA;


// for (storage purposes; how to iterate through all INPUT_KEY::s; is shown in the comment below) { ignore all punctuation in this line }
/*
	for (int k = INPUT_KEY::KEY_SPACE; k < INPUT_KEY::KEY_LAST; k++)
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
	// important! if not the window will not respond
	glfwPollEvents();

}


bool LEDA::keyPressed(INPUT_KEY key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool LEDA::keyRepeated(INPUT_KEY key) {
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

void LEDA::addKeyTriggerCallback(INPUT_KEY key, emptyFunction function) {

	callbackMap::iterator found = triggerCallbacks.find(key);
	if (found == triggerCallbacks.end()) {
		std::vector<emptyFunction> tempFunctionList;
		triggerCallbacks.emplace(key, tempFunctionList);
		found = triggerCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}

void LEDA::addKeyReleaseCallback(INPUT_KEY key, emptyFunction function) {

	callbackMap::iterator found = releaseCallbacks.find(key);
	if (found == releaseCallbacks.end()) {
		std::vector<emptyFunction> tempFunctionList;
		releaseCallbacks.emplace(key, tempFunctionList);
		found = releaseCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}

void LEDA::addKeyRepeatCallback(INPUT_KEY key, emptyFunction function) {

	callbackMap::iterator found = repeatCallbacks.find(key);
	if (found == repeatCallbacks.end()) {
		std::vector<emptyFunction> tempFunctionList;
		repeatCallbacks.emplace(key, tempFunctionList);
		found = repeatCallbacks.find(key);
	}
	found->second.push_back(function);
	return;

}


// functions to remove key callbacks

void LEDA::removeKeyTriggerCallback(INPUT_KEY key, emptyFunction function) {

	callbackMap::iterator found = triggerCallbacks.find(key);
	if (found == triggerCallbacks.end()) {
		// there's nothing to remove!
		return;
	}
	std::vector<emptyFunction> functionList = found->second;
	std::vector<emptyFunction>::iterator foundAgain = std::find(functionList.begin(), functionList.end(), function);
	if (foundAgain != functionList.end()) {
		// only remove if the function is found
		functionList.erase(foundAgain);
	}
	return;

}

void LEDA::removeKeyReleaseCallback(INPUT_KEY key, emptyFunction function) {

	callbackMap::iterator found = releaseCallbacks.find(key);
	if (found == releaseCallbacks.end()) {
		// there's nothing to remove!
		return;
	}
	std::vector<emptyFunction> functionList = found->second;
	std::vector<emptyFunction>::iterator foundAgain = std::find(functionList.begin(), functionList.end(), function);
	if (foundAgain != functionList.end()) {
		// only remove if the function is found
		functionList.erase(foundAgain);
	}
	return;

}

void LEDA::removeKeyRepeatCallback(INPUT_KEY key, emptyFunction function) {

	callbackMap::iterator found = repeatCallbacks.find(key);
	if (found == repeatCallbacks.end()) {
		// there's nothing to remove!
		return;
	}
	std::vector<emptyFunction> functionList = found->second;
	std::vector<emptyFunction>::iterator foundAgain = std::find(functionList.begin(), functionList.end(), function);
	if (foundAgain != functionList.end()) {
		// only remove if the function is found
		functionList.erase(foundAgain);
	}
	return;

}