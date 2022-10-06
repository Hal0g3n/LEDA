#ifndef LEDA_COMPONENTS_H_
#define LEDA_COMPONENTS_H_

#include "pch.h"

#include "IComponent.h"

namespace LEDA {
	struct LogicComponent: IComponent {
		virtual void init()	  const;
		virtual void update() const;
		virtual void free()	  const;
	};
}

#endif // LEDA_COMPONENTS_H_