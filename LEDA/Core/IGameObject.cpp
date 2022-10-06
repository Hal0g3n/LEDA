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

#include "IGameObject.h"

#include "LEDA_System.h"

using namespace LEDA;

// helper functions for game objects
void LEDA::addComponent(IGameObject &obj, IComponent const component) {
	obj.components.emplace(typeid(component).name(), component);
}

template <typename Component>
IComponent LEDA::getComponent(IGameObject &obj) {
	if (components.find(typeid(Component).name()) == components.end()) {
		throw "Invalid component type id: '" + id + "'!";
	}
	return obj.components.find(id)->second;
};