/**
 * @file        CollisionSystem.h
 * @author      your name (you@domain.com)
 * @brief       <something here>
 * @version     0.1
 * @date        22-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_COLLISION_SYSTEM_H_
#define LEDA_COLLISION_SYSTEM_H_

#include "pch.h"

#include "LEDA_System.h"
#include "ISystem.h"

namespace LEDA {

	class CollisionSystem : public ISystem {
		std::vector<GameObject*> objects{};

	public:
		// constructor
		CollisionSystem() {};
		// destructor 
		~CollisionSystem() { objects.clear(); }

		void init();
		void update();
		void free();

		// registering new objects
		void onRegisterGameObject(GameObject* obj);
		void onRemoveGameObject(GameObject* obj);
	};

}

#endif // LEDA_COLLISION_SYSTEM_H_