/**
 * @file        IGameObject.h
 * @author      your name (you@domain.com)
 * @brief       Interface for Game Objects
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_I_GAME_OBJECT_H_
#define LEDA_I_GAME_OBJECT_H_

#include "pch.h"

/* // to remove

#include "IComponent.h"

namespace LEDA {

	class IGameObject {

	private:
		std::unordered_map<std::string, IComponent*> components{};

	public:
		friend void addComponent(IGameObject& obj, IComponent* component);

		// Returns nullptr if component is not found
		template <typename C>
		friend C* getComponent(IGameObject& obj);

	};

	void addComponent(IGameObject& obj, IComponent* component) {
		obj.components.emplace(typeid(component).name(), component);
	}

	template <typename C>
	C* getComponent(IGameObject& obj) {
		std::unordered_map<std::string, IComponent*>::const_iterator value = obj.components.find(typeid(C).name());
		if (value == obj.components.end()) {
			throw "No such component in game object!";
		} else {
			return dynamic_cast<C*>(value->second);
		}
	}

}

*/

#endif // LEDA_I_GAME_OBJECT_H_