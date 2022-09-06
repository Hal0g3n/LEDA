/**
 * @file        LEDA_Input.cpp
 * @author      your name (you@domain.com)
 * @brief       Implements some input functions
 * @version     0.1
 * @date        16-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#include "pch.h"
#include "LEDA_Input.h"

using namespace LEDA;


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

}

void LEDA::doInput() {

	// processes received events in the event queue (calling key callbacks)
	glfwPollEvents();

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