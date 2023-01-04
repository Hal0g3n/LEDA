/**
 * @file        CollisionSystem.cpp
 * @author      your name (you@domain.com)
 * @brief       <something here>
 * @version     0.1
 * @date        22-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "GameObject.h"
#include "CollisionSystem.h"
#include "Collision.h"
#include "LEDA_Components.h"

namespace LEDA {

	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	} // cause this doesn't exist in c++

	void CollisionSystem::onRegisterGameObject (GameObject* obj) {
		// find the collision component
		CollisionComponent* col = getComponent<CollisionComponent>(obj);
		if (col != nullptr) objects.push_back(obj);
	}

	void CollisionSystem::onRemoveGameObject(GameObject* obj) {
		objects.erase(std::find(objects.begin(), objects.end(), obj));
	}

	void CollisionSystem::init() {};

	void CollisionSystem::update() {
		// checks collisions for everything
		for (int i = 0; i < objects.size(); ++i) {
			GameObject* obj = objects.at(i);
			CollisionComponent* objCom = getComponent<CollisionComponent>(obj);
			if (!objCom->collide) continue; // this object does not collide
			for (int j = i; j < objects.size(); ++j) {
				GameObject* other = objects.at(j);
				CollisionComponent* otherCom = getComponent<CollisionComponent>(other);
				if (!otherCom->collide) continue; // the other object does not collide

				// AABB check
				if (instanceof<AABB>(objCom->shape) && instanceof<AABB>(otherCom->shape)) {
					// we need the velocities
					Vec2 objVel = getComponent<KinematicsComponent>(obj) == nullptr ? getComponent<KinematicsComponent>(obj)->vel : Vec2{ 0, 0 };
					Vec2 otherVel = getComponent<KinematicsComponent>(other) == nullptr ? getComponent<KinematicsComponent>(other)->vel : Vec2{ 0, 0 };

					// perform collision check
					if (CollisionIntersection_AABB(dynamic_cast<AABB*>(objCom->shape), objVel, dynamic_cast<AABB*>(otherCom->shape), otherVel)) {
						objCom->collisionResponse(other);
						otherCom->collisionResponse(obj); // they both trigger!
					}
				}

				// obj is circle
				if (instanceof<Circle>(objCom->shape)) {
					// check: other is also circle
					if (instanceof<Circle>(otherCom->shape)) {

					}
				}
			}
		}

	}
	
	void CollisionSystem::free() {
		// clear object list
		objects.clear();
	}

}