/**
 * @file        LogicSystem.h
 * @author      your name (you@domain.com)
 * @brief       Defines the logic system.
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_LOGIC_SYSTEM_H_
#define LEDA_LOGIC_SYSTEM_H_

#include "pch.h"

#include "ISystem.h"
#include "LEDA_System.h"

namespace LEDA {

	class LogicSystem : public ISystem {
		std::vector<GameObject*> objects{};

	public:
		// Called on Initialize
		LogicSystem() {};

		// Called on Destroy
		~LogicSystem() {};

		/*
		void init() { for (GameObject* obj : objects) obj->init(); };
		void update() { for (GameObject* obj : objects) obj->update(); };
		void free() { for (GameObject* obj : objects) obj->destroy(); objects.clear(); };
		*/
		// ?
		void init() {};
		void update() {};
		void free() {};
		
		// Called on new Game Object
		void onRegisterGameObject(GameObject*);
		void onRemoveGameObject(GameObject*);
	};

}

#endif // LEDA_LOGIC_SYSTEM_H_