/**
 * @file        InputSystem.cpp
 * @author      your name (you@domain.com)
 * @brief       <something here?>
 * @version     0.1
 * @date        21-12-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "LEDA_System.h"
#include "LEDA_Input.h"
#include "InputSystem.h"

using namespace LEDA;

void InputSystem::init() {

	// initialize
	Input::initializeInput();

	// and also add default behaviour (close on escape key)
	Input::addKeyTriggerCallback(Input::KEY::KEY_ESCAPE, []() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	});

}

void InputSystem::update() {

	// important! if not window will not be responding
	glfwPollEvents();

	// (and this too)
	Input::doInput();
	
}

void InputSystem::free() {
	// free free
	return;
}

void InputSystem::onRegisterGameObject(GameObject* obj) {
	// add object to this system's list (what for? todo)
	objects.push_back(obj);
}

void InputSystem::onRemoveGameObject(GameObject* obj) {
	// find object
	std::vector<GameObject*>::iterator found = std::find(objects.begin(), objects.end(), obj);
	if (found == objects.end()) {
		LOG_WARNING(std::string("this game object wasn't found in input system list:\n") + printGameObject(obj));
		return;
	}
	else {
		// delete object from list
		objects.erase(found);
	}
}