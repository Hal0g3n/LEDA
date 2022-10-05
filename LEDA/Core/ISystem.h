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

#include "pch.h"

#include "LEDA_System.h"

namespace LEDA {

	class ISystem {
	public:
		ISystem(); // Called on Startup
		virtual ~ISystem()	  = 0; // Called on Exit
		virtual void init()	  = 0; // Called on Game State Initialize
		virtual void update() = 0; // Called on Update (in Game Loop)
		virtual void free()   = 0; // Called on Game State Exit

		virtual void registerGameObject(IGameObject* objects) = 0;
	};

}