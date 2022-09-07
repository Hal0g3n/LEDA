#pragma once

#include "IGameObject.h"

namespace LEDA {

	class ISystem {
		std::vector<IGameObject*> objects;

	public:
		virtual void init()	   const = 0;
		virtual void update()  const = 0;
		virtual void destroy() const = 0;
	};

}