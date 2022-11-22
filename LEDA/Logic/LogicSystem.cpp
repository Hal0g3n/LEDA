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

void LogicSystem::onRegisterGameObject(GameObject* obj) {
	LogicComponent* logic = getComponent<LogicComponent>(*obj);

	if (logic == nullptr) return;
	
	// logic->init();

	// Add Object to logic system list
	objects.push_back(obj);
}

void LogicSystem::onRemoveGameObject(GameObject* obj) {
	LogicComponent* logic = getComponent<LogicComponent>(*obj);

	if (logic == nullptr) return;

	// logic->init();

	// Find and Erase Object from the logic system list
	objects.erase(std::find(objects.begin(), objects.end(), obj));
}