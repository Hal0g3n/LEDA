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

	void GameObject::init() {
		// todo
		std::cout << "init";
	}
	
	void GameObject::update() {
		// todo
		// std::cout << "update";
	}

	void GameObject::destroy() {
		// todo
		std::cout << "destroy";
	}

	IComponent GameObject::getComponent(std::string string) {
		if (this->components.find(string) == this->components.end()) {
			throw "Invalid component type string: '" + string + "'!";
		}
		return this->components.at(string);
	}

};