/**
 * @file        ISystem.h
 * @author      your name (you@domain.com)
 * @brief       Definition of abstract interface system
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_I_SYSTEM_H_
#define LEDA_I_SYSTEM_H_

#include "pch.h"

#include "LEDA_System.h"

namespace LEDA {

	class ISystem {
	public:
		ISystem() {}; // Called on Startup
		virtual ~ISystem() {}; // Called on Exit

		virtual void init()	  = 0; // Called on Game State Initialize
		virtual void update() = 0; // Called on Update (in Game Loop)
		virtual void free()   = 0; // Called on Game State Exit

		virtual void onRegisterGameObject(GameObject* obj) = 0;
		virtual void onRemoveGameObject(GameObject* obj) = 0;
	};

}

#endif // LEDA_I_SYSTEM_H_