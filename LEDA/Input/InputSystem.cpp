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

bool real_init_done = false;
// important! wait 1 frame? to initialize, because it waits for graphics to initialize first
void real_init() {

	// initialize
	initializeInput();

	// and also add default behaviour (close on escape key)
	addKeyTriggerCallback(INPUT_KEY::KEY_ESCAPE, []() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	});

}

void InputSystem::init() {

}

void InputSystem::update() {
	if (!real_init_done) {
		real_init();
		real_init_done = true;
	}
	doInput();
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
	if (found != objects.end())
		objects.erase(found);
}