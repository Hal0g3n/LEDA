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

#include "IComponent.h"

namespace LEDA {

	class IGameObject {

	private:
		std::unordered_map<std::string, IComponent> components{};

	public:
		friend void addComponent(IGameObject&, IComponent);

		// Returns nullptr if Component is not found
		template <typename Component>
		friend Component* getComponent();

	};

	void addComponent(IGameObject&, IComponent);

	template <typename Component>
	Component* getComponent(IGameObject&);
}

#endif // LEDA_I_GAME_OBJECT_H_