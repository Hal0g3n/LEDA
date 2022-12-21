/**
 * @file        InputSystem.h
 * @author      your name (you@domain.com)
 * @brief       input system h h h h h
 * @version     0.1
 * @date        21-12-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_INPUT_SYSTEM_H_
#define LEDA_INPUT_SYSTEM_H_

#include "pch.h"

#include "ISystem.h"
#include "LEDA_System.h"

namespace LEDA {

	class InputSystem : public ISystem {
		std::vector<GameObject*> objects{};

	public:

		InputSystem() {};
		~InputSystem() { objects.clear(); };

		void init();
		void update();
		void free();

		void onRegisterGameObject(GameObject*);
		void onRemoveGameObject(GameObject* obj);
	};

}

#endif // LEDA_INPUT_SYSTEM_H_