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
		uint16_t id;
		std::unordered_map<std::string, IComponent> components{};
	};
}