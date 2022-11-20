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
		std::vector<IGameObject*> objects{};

	public:
		// Called on Initialize
		LogicSystem() {};

		// Called on Destroy
		~LogicSystem() { for (IGameObject* obj : objects) delete obj; };

		/*
		void init() { for (IGameObject* obj : objects) obj->init(); };
		void update() { for (IGameObject* obj : objects) obj->update(); };
		void free() { for (IGameObject* obj : objects) obj->destroy(); objects.clear(); };
		*/
		// ?
		void init() {};
		void update() {};
		void free() {};
		
		// Called on new Game Object
		void registerGameObject(IGameObject*);

	};
}

#endif // LEDA_LOGIC_SYSTEM_H_