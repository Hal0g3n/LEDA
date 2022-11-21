/**
 * @file        LogicSystem.cpp
 * @author      your name (you@domain.com)
 * @brief       <something here>
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "LEDA_System.h"
#include "LogicSystem.h"
#include "LogicComponent.h"

using namespace LEDA;

void LogicSystem::registerGameObject(GameObject* obj) {

	// check if the object contains a logic component
	LogicComponent* logic = getComponent<LogicComponent>(*obj);
	if (logic != nullptr) {
		// if so, add to this system's object list
		this->objects.push_back(obj);
	}

}