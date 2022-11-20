/**
 * @file        GameObject.h
 * @author      your name (you@domain.com)
 * @brief       Game Object
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#ifndef LEDA_GAME_OBJECT_H_
#define LEDA_GAME_OBJECT_H_

#include "pch.h"

#include "IComponent.h"

#include <unordered_map>

namespace LEDA {

	class GameObject {

	private:
		std::unordered_map<std::string, IComponent*> components{};

	public:
		friend void addComponent(GameObject& obj, IComponent* component);

		// Returns nullptr if component is not found
		template <typename C>
		friend C* getComponent(GameObject& obj);

	};

	void addComponent(GameObject& obj, IComponent* component) {
		obj.components.emplace(typeid(component).name(), component);
	}

	template <typename C>
	C* getComponent(GameObject& obj) {
		std::unordered_map<std::string, IComponent*>::const_iterator value = obj.components.find(typeid(C).name());
		if (value == obj.components.end()) {
			return nullptr; // ok don't throw error just handle later (:
		} else {
			return dynamic_cast<C*>(value->second);
		}
	}

}

#endif // LEDA_GAME_OBJECT_H_