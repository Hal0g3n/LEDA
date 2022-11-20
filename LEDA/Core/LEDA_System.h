/**
 * @file        LEDA_System.h
 * @author      your name (you@domain.com)
 * @brief       Includes the entire LEDA Core Systems Library
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_SYSTEM_H_
#define LEDA_SYSTEM_H_

#include "pch.h"

#include "GameObject.h"
#include "IComponent.h"
#include "ISystem.h"
#include "IGameState.h"

// should this be here?
//#include "LogicSystem.h"

namespace LEDA {
	/**
	 * @brief Entry Point into LEDA
	 * @param showConsole  true to show console
	 * @param frameRate	   The maximum frame rate (LEDA can only garuntee that frame rate does not exceed)
	 * @param windowTitle  The Initial Window Title
	 * @param initState    The Initial Window State
	*/
	void LEDA_API LEDA_INIT(bool showConsole, double frameRate, std::string windowTitle, IGameState *initState);


	// GameStateManager Functions //
	bool registerGameState(std::string id, IGameState* state);
	IGameState* retrieveGameState(std::string id);

	IGameState* getPreviousGameState();
	IGameState* getCurrentGameState();
	IGameState* getNextGameState();
	void setNextGameState(IGameState* state);

	// GameObjectManager Functions //
	void registerGameObject(std::string id, GameObject* obj);
	GameObject* retrieveGameObject(std::string id);
}

#endif // LEDA_SYSTEM_H_