#pragma once

#include "IGameObject.h"
#include <string>
#include <vector>

namespace LEDA {

	class ISystem {

	public:
		virtual void init()	   const = 0;
		virtual void update()  const = 0;
		virtual void destroy() const = 0;

		virtual void registerGameObject(IGameObject* objects) const = 0;
	};

}