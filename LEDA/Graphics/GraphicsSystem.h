/**
 * @file        GraphicsSystem.h
 * @author      your name (you@domain.com)
 * @brief       graphycs sistem
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_GRAPHICS_SYSTEM_H_
#define LEDA_GRAPHICS_SYSTEM_H_

#include "pch.h"

#include "ISystem.h"
#include "LEDA_System.h"

namespace LEDA {

	class GraphicsSystem : public ISystem {
		std::vector<GameObject*> objects{};

	public:

		GraphicsSystem() {};
		~GraphicsSystem() { objects.clear(); };

		void init();
		void update();
		void free();

		void onRegisterGameObject(GameObject*);
		void onRemoveGameObject(GameObject* obj) {}
	};

}

#endif // LEDA_GRAPHICS_SYSTEM_H_
