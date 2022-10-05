#pragma once

#include "IGameObject.h"
#include <string>
#include <vector>

namespace LEDA {

	class ISystem {
	public:
		ISystem();				   // Called on Startup
		virtual ~ISystem()	  = 0; // Called on Exit
		virtual void init()	  = 0; // Called on Game State Initialize
		virtual void update() = 0; // Called on Update (in Game Loop)
		virtual void free()   = 0; // Called on Game State Exit

		virtual void registerGameObject(IGameObject* objects) = 0;
	};

}