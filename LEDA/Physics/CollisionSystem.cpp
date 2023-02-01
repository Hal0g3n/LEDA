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
		TransformComponent* tc = getComponent<TransformComponent>(obj);
		if (cc != nullptr && tc != nullptr) {
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

				// we need the positions
				Vec2& objPos = getComponent<TransformComponent>(obj)->position;
				Vec2& otherPos = getComponent<TransformComponent>(other)->position;

				// we need the velocities
				Vec2 objVel = getComponent<KinematicsComponent>(obj) == nullptr ? getComponent<KinematicsComponent>(obj)->vel : Vec2{ 0, 0 };
				Vec2 otherVel = getComponent<KinematicsComponent>(other) == nullptr ? getComponent<KinematicsComponent>(other)->vel : Vec2{ 0, 0 };
				if (!otherCom->collide) continue; // the other object does not collide

				// AABB check
				if (instanceof<AABB>(objCom->shape) && instanceof<AABB>(otherCom->shape)) {

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
					// retrieve the old position
					Vec2 objPrevPos = objPos - objVel * frameTime;

					// object output variable
					Vec2 objInterPt;
					double interTime;

					// check: other is also circle
					if (instanceof<Circle>(otherCom->shape)) {
						// retrieve the old position of the other object
						Vec2 otherPrevPos = otherPos - otherVel * frameTime;
						
						// output variable
						Vec2 otherInterPt;
						if (CollisionIntersection_CircleCircle(*dynamic_cast<Circle*>(objCom->shape), objVel, *dynamic_cast<Circle*>(otherCom->shape), otherVel, objInterPt, otherInterPt, interTime)) {
							if (objCom->reflect || otherCom->reflect) {
								Vec2 objReflectPt, objReflectVec, otherReflectPt, otherReflectVec;
								Vec2 reflectNormal = (objInterPt - otherInterPt).normalize();
								CollisionResponse_CircleCircle(reflectNormal, interTime, objVel, objCom->m_mass, objInterPt, otherVel, otherCom->m_mass, otherInterPt, objReflectVec, objReflectPt, otherReflectVec, otherReflectPt);
								if (objCom->reflect) {
									// reflected position and velocity
									objPos = objReflectPt;
									getComponent<KinematicsComponent>(obj)->vel = Vec2{ objVel.x * objReflectVec.x, objVel.y * objReflectVec.y };
								}
								else objPos = objInterPt; // todo: maybe set component parallel to collision normal to 0? 
								// other object too
								if (otherCom->reflect) {
									// reflected position and velocity
									otherPos = otherReflectPt;
									getComponent<KinematicsComponent>(obj)->vel = Vec2{ otherVel.x * otherReflectVec.x, otherVel.y * otherReflectVec.y };
								}
								else otherPos = otherInterPt; // todo: maybe set component parallel to collision normal to 0? 
							}
							else {
								objPos = objInterPt; // see above
								otherPos = otherInterPt;
							}
							if (objCom->collisionResponse != nullptr) {
								objCom->collisionResponse(obj, other);
							}
							if (otherCom->collisionResponse != nullptr) {
								otherCom->collisionResponse(other, obj);
							}
						}
					}

					// check: other is line segment
					if (instanceof<LineSegment>(otherCom->shape)) {
						// we don't mess with the line segment position (it has infinite mass)
						// output
						Vec2 collisionNormal;
						if (CollisionIntersection_CircleLineSegment(*dynamic_cast<Circle*>(objCom->shape), objPrevPos, *dynamic_cast<LineSegment*>(otherCom->shape), objInterPt, collisionNormal, interTime)) {
							if (objCom->reflect) {
								Vec2 reflect;
								CollisionResponse_CircleLineSegment(objInterPt, collisionNormal, objPos, reflect);
							}
							else {
								objPos = objInterPt;
								// maybe do something with the velocity
							}
							// collision response
							if (objCom->collisionResponse != nullptr) {
								objCom->collisionResponse(obj, other);
							}
							if (otherCom->collisionResponse != nullptr) {
								otherCom->collisionResponse(other, obj);
							}
						}
					}
				}

				// obj is line segment
				if (instanceof<LineSegment>(objCom->shape)) {
					// check: other is circle
					if (instanceof<Circle>(otherCom->shape)) {
						// get previous position
						Vec2 otherPrevPos = otherPos - otherVel * frameTime;
						// output
						Vec2 otherInterPos, collisionNormal;
						double interTime;
						if (CollisionIntersection_CircleLineSegment(*dynamic_cast<Circle*>(otherCom->shape), otherPrevPos, *dynamic_cast<LineSegment*>(objCom->shape), otherInterPos, collisionNormal, interTime)) {
							if (objCom->reflect) {
								Vec2 reflect;
								CollisionResponse_CircleLineSegment(otherInterPos, collisionNormal, otherPos, reflect);
							}
							else {
								otherPos = otherInterPos;
								// maybe do something with the velocity
							}
							// collision response
							if (objCom->collisionResponse != nullptr) {
								objCom->collisionResponse(obj, other);
							}
							if (otherCom->collisionResponse != nullptr) {
								otherCom->collisionResponse(other, obj);
							}
						}
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