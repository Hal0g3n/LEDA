/**
 * @file        GraphicsSystem.cpp
 * @author      your name (you@domain.com)
 * @brief       not related to graphs
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "LEDA_System.h"
#include "LEDA_Graphics.h"
#include "GraphicsSystem.h"
#include "GraphicsComponent.h"

using namespace LEDA;

void GraphicsSystem::init(void) {

	initializeDrawer();

}

void GraphicsSystem::update(void) {

	drawObjects(this->objects);

}

void GraphicsSystem::free(void) {

	freeDrawer();

}

void GraphicsSystem::registerGameObject(GameObject* obj) {

	// check if the object contains a graphics component
	GraphicsComponent* graphics = getComponent<GraphicsComponent>(*obj);
	if (graphics != nullptr) {
		// if so, add to this system's object list
		this->objects.push_back(obj);
	}

}