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
#include "IGameObject.h"

using namespace LEDA;

void LogicSystem::registerGameObject(IGameObject* obj) {
	this->objects.push_back(obj);
	LogicComponent* logic = getComponent<LogicComponent>(*obj);

	if (logic == nullptr) return;
	
	// logic->init();
	objects.push_back(obj);
}