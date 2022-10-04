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

#include <unordered_map>
#include <string>
#include "IComponent.h"

namespace LEDA {
	class IGameObject {

	public:
		std::unordered_map<std::string, IComponent> components{};

		// required functions
		virtual void init()    const = 0;
		virtual void update()  const = 0;
		virtual void destroy() const = 0;

		// helper functions
		virtual IComponent getComponent(std::string string) const = 0;
	};
}