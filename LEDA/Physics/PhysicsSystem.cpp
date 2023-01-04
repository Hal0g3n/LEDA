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

#include "PhysicsSystem.h"
#include "LEDA_Components.h"

namespace LEDA {

	// registering new object
	void PhysicsSystem::onRegisterGameObject(GameObject* obj) {
		// find the kinematics component and transform component
		KinematicsComponent* kine = getComponent<KinematicsComponent>(obj);
		TransformComponent* trans = getComponent<TransformComponent>(obj);

		if (kine != nullptr && trans != nullptr) {
			objects.push_back(obj);
		}
	}

	void PhysicsSystem::onRemoveGameObject(GameObject* obj) {
		objects.erase(std::find(objects.begin(), objects.end(), obj));
	}

	void PhysicsSystem::init() {
		
	}

	void PhysicsSystem::update() {
		// updates physics by calculating movement of everything
		for (GameObject* obj: objects) {
			KinematicsComponent* kine = getComponent<KinematicsComponent>(obj);
			TransformComponent* trans = getComponent<TransformComponent>(obj);

			// update the velocity
			kine->vel += kine->acc * frameTime;

			// update the displacement, which is in transform component
			trans->position += kine->vel * frameTime;

			// update the angular velocity
			kine->rot_vel += kine->rot_acc * frameTime;

			// update the angle
			trans->rotation += kine->rot_vel * frameTime;
		}
	}

	void PhysicsSystem::free() {
		// clear the object list
		objects.clear();
	}

}