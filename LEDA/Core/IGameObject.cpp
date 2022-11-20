/**
 * @file        IGameObject.cpp
 * @author      your name (you@domain.com)
 * @brief       Game Object
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

 /*

#include "IGameObject.h"

#include "LEDA_System.h"

using namespace LEDA;

// helper functions for game objects
void IGameObject::addComponent(IComponent const component) {
	this->components.emplace(typeid(component).name(), component);
}

template <typename C>
C* IGameObject::getComponent() {
	IComponent* value = this->components.find<C>();
	return value == this->components.end() ? nullptr : value->second;
};

void LEDA::addComponent(IGameObject &obj, IComponent const component) {
	obj.components.emplace(typeid(component).name(), component);
}

template <typename C>
C* LEDA::getComponent(IGameObject &obj) {
	IComponent* value = obj.components.find<C>();
	return value == obj.components.end() ? nullptr : value->second;
};

*/