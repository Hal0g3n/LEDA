/**
 * @file        GameObject.h
 * @author      your name (you@domain.com)
 * @brief       Game Object
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_GAME_OBJECT_H_
#define LEDA_GAME_OBJECT_H_

#include "pch.h"

#include "IComponent.h"
#include "LEDA_Components.h"

#include <unordered_map>
#include <sstream>

namespace LEDA {

	class LEDA_API GameObject {

	private:
		std::string id;
		std::unordered_map<std::string, IComponent*> components{};

	public:
		// Initialize with id
		GameObject(std::string id) : id{ id } {}
		GameObject() = default; // compatibility for now

		std::string getId() { return id; }

		friend void LEDA_API addComponent(GameObject* obj, IComponent* component);

		// Returns nullptr if component is not found
		template <typename C>
		friend C LEDA_API * getComponent(GameObject* obj);

		friend void LEDA_API deleteAllComponents(GameObject* obj);

		friend std::string LEDA_API printGameObject(GameObject* obj);

	};

	void addComponent(GameObject* obj, IComponent* component) {
		obj->components.emplace(typeid(*component).name(), component);
	}

	template <typename C>
	C * getComponent(GameObject* obj) {
		std::unordered_map<std::string, IComponent*>::const_iterator value = obj->components.find(typeid(C).name());
		if (value == obj->components.end()) {
			return nullptr; // don't throw error just handle later (:
		} else {
			return dynamic_cast<C*>(value->second);
		}
	}

	void deleteAllComponents(GameObject* obj) {
		for (std::pair<const std::string, IComponent*>& pair : obj->components) {
			IComponent* component = pair.second;
			delete component;
		}
		obj->components.clear();
	}

	std::string printGameObject(GameObject* obj) {

		std::stringstream ss;
		ss << "{\n    ID: " << obj->id;
		TransformComponent* tc = getComponent<TransformComponent>(obj);
		if (tc != nullptr) {
			ss << "\n    position: (" << tc->position.x << ", " << tc->position.y << ")\n    scale: (" << tc->scale.x << ", " << tc->scale.y << ")\n    rotation: " << tc->rotation;
		}
		GraphicsComponent* gc = getComponent<GraphicsComponent>(obj);
		if (gc != nullptr) {
			ss << "\n    material: " << gc->material << "\n    shape: " << gc->shape << "\n    color: [";
			for (double& i : gc->color) {
				ss << i << ", ";
			}
			ss << "\b\b]"; // WOW using backspace works!
		}
		KinematicsComponent* kc = getComponent<KinematicsComponent>(obj);
		if (kc != nullptr) {
			ss << "\n    velocity: "; // TODO vector std::string operator thing
		}
		LogicComponent* lc = getComponent<LogicComponent>(obj);
		if (lc != nullptr) {
			ss << "\n    logic: <exists>";
		}
		ss << "\n}\n";
		return ss.str();
		
	}

}

#endif // LEDA_GAME_OBJECT_H_