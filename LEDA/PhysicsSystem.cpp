/**
 * @file        PhysicsSystem.cpp
 * @author      your name (you@domain.com)
 * @brief       <something here>
 * @version     0.1
 * @date        22-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "LEDA_System.h"
#include "PhysicsSystem.h"
#include "KinematicsComponent.h"
#include "TransformComponent.h";

namespace LEDA {
	// registering new object
	void PhysicsSystem::registerGameObject(GameObject* obj) {
		// find the kinematics component and transform component; physics system only governs movement for now
		KinematicsComponent* kine = getComponent<KinematicsComponent>(*obj);
		TransformComponent* trans = getComponent<TransformComponent>(*obj);

		if (kine != nullptr && trans != nullptr) {
			objects.push_back(obj);
		}
	}

	void PhysicsSystem::update() {
		// updates physics by calculating movement of everything
		for (GameObject* obj: objects) {
			KinematicsComponent* kine = getComponent<KinematicsComponent>(*obj);
			TransformComponent* trans = getComponent<TransformComponent>(*obj);

			//update the velocity
			kine->vel += kine->acc * frameTime;

			// update the displacement, which is in transform component
			trans->position += kine->vel * frameTime;
		}
	}

	void PhysicsSystem::free() {
		// clear the object list
		objects.clear();
	}
}