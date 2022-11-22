/**
 * @file        PhysicsSystem.h
 * @author      your name (you@domain.com)
 * @brief       <something here>
 * @version     0.1
 * @date        22-11-2022
 *
 * @copyright   Copyright (c) 2022
 */
#pragma once

#include "pch.h"

#include "LEDA_System.h"
#include "ISystem.h"

namespace LEDA {
	class PhysicsSystem : public ISystem {
		std::vector<GameObject*> objects{};

	public:
		// constructor
		PhysicsSystem() {};
		//destructor 
		~PhysicsSystem() { objects.clear(); }

		void init();
		void update();
		void free();

		//registering new objects
		void registerGameObject(GameObject* obj);
	};
}
