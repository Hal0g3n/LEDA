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

#include "CollisionComponent.h"
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
		CollisionComponent* cc = getComponent<CollisionComponent>(obj);
		KinematicsComponent* kc = getComponent<KinematicsComponent>(obj);
		TransformComponent* tc = getComponent<TransformComponent>(obj);
		if (cc != nullptr && kc != nullptr && tc != nullptr) {
			objects.push_back(obj);
		}
	}

	void CollisionSystem::onRemoveGameObject(GameObject* obj) {
		objects.erase(std::find(objects.begin(), objects.end(), obj));
	}

	void CollisionSystem::init() {};

	void CollisionSystem::update() {

		// updates collision shapes for everything
		for (int i = 0; i < objects.size(); ++i) {
			GameObject* obj = objects.at(i);
			CollisionComponent* objCom = getComponent<CollisionComponent>(obj);
			TransformComponent* tc = getComponent<TransformComponent>(obj);
			if (instanceof<AABB>(objCom->shape)) {
				AABB* aabb = dynamic_cast<AABB*>(objCom->shape);
				aabb->min.x = tc->position.x - tc->scale.x / 2.0;
				aabb->min.y = tc->position.y - tc->scale.y / 2.0;
				aabb->max.x = tc->position.x + tc->scale.x / 2.0;
				aabb->max.y = tc->position.y + tc->scale.y / 2.0;
			}
			else if (instanceof<Circle>(objCom->shape)) {
				Circle* circle = dynamic_cast<Circle*>(objCom->shape);
				circle->m_center.x = tc->position.x;
				circle->m_center.y = tc->position.y;
				circle->m_radius = (tc->scale.x + tc->scale.y) / 2.0 / 2.0;
			}
			else {

			}
		}

		// checks collisions for everything
		for (int i = 0; i < objects.size(); ++i) {
			GameObject* obj = objects.at(i);
			CollisionComponent* objCom = getComponent<CollisionComponent>(obj);
			if (!objCom->collide) continue; // this object does not collide
			for (int j = i + 1; j < objects.size(); ++j) {
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
						// they both trigger!
						if (objCom->collisionResponse != nullptr) {
							objCom->collisionResponse(obj, other);
						}
						if (otherCom->collisionResponse != nullptr) {
							otherCom->collisionResponse(other, obj);
						}
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