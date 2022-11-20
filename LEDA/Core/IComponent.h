/**
 * @file        IComponent.h
 * @author      your name (you@domain.com)
 * @brief       Interface for a Component in a GameObject
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_I_COMPONENT_H_
#define LEDA_I_COMPONENT_H_

#include "pch.h"

namespace LEDA {

	struct LEDA_API IComponent {

		// make this class polymorphic
		virtual ~IComponent() {};

	};

}

#endif LEDA_I_COMPONENT_H_