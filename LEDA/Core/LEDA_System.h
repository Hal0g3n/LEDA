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
#include "SceneManager.h"
/*
#include "InputSystem.h"
#include "LogicSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
*/

namespace LEDA {

	// make frame time, app time accessible for other systems
	extern double LEDA_API frameTime, appTime;

	class LEDA_API SceneManager; // forward reference
	SceneManager LEDA_API * sceneManager;

	// remove this comment and add a more helpful one to describe these 2 things
	std::unordered_map<std::string, std::function<void(void)>> startFunctions;
	std::unordered_map<std::string, std::function<void(void)>> endFunctions;

	// yet another thing to make things work
	std::vector<GameObject*> objectsToDelete; // to delete between this frame and the next frame

	void LEDA_API LEDA_INIT(std::string state, std::function<void(void)> fn_start = []() {}, std::function<void(void)> fn_end = []() {});

	/**
	 * @brief Entry Point into LEDA
	 * @param showConsole	true to show console
	 * @param frameRate		the maximum frame rate (LEDA can only guarantee that frame rate does not exceed it)
	 * @param windowTitle	The Initial Window Title
	 * @param initialState	The Initial Window State
	*/
	void LEDA_API LEDA_START(bool showConsole, double frameRate, std::string windowTitle, std::string initialState);


	// GameStateManager Functions //
	std::string LEDA_API getPreviousGameStateFile();
	std::string LEDA_API getCurrentGameStateFile();
	std::string LEDA_API getNextGameStateFile();
	void LEDA_API setNextGameStateFile(std::string stateFile);
	void LEDA_API setGameStateRestart();
	void LEDA_API setGameStateQuit();

	// GameObjectManager Functions //
	GameObject LEDA_API * retrieveGameObject(std::string id);
	void LEDA_API registerGameObject(std::string id, GameObject* obj);
	bool LEDA_API removeGameObject(GameObject*);
	bool LEDA_API removeGameObject(std::string id);

	// Logger Functions //
	void LEDA_API LOG_WARNING(std::string);

}

#endif // LEDA_SYSTEM_H_