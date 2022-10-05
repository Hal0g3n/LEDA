/**
 * @file        GameObject.cpp
 * @author      your name (you@domain.com)
 * @brief       Game Object
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "GameObject.h"

#include "LEDA_System.h"

namespace LEDA {

	GameObject::GameObject() {
		
	}

	// helper functions for game objects

	void addComponent(GameObject& obj, IComponent component) {
		obj.components.emplace(typeid(component).name(), component);
	}

	IComponent getComponent(GameObject& obj, std::string id) {
		if (obj.components.find(id) == obj.components.end()) {
			throw "Invalid component type id: '" + id + "'!";
		}
		return obj.components.find(id)->second;
	};

};