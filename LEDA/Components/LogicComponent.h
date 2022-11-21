/**
 * @file        LogicComponent.h
 * @author      your name (you@domain.com)
 * @brief       Stores logic information
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#ifndef LOGIC_COMPONENTS_H_
#define LOGIC_COMPONENTS_H_

#include "pch.h"

#include "IComponent.h"

namespace LEDA {

	struct LEDA_API LogicComponent : IComponent {
		// virtual void init()	  const;
		// virtual void update()  const;
		// virtual void free()	  const;
	};

}

#endif // LOGIC_COMPONENTS_H_