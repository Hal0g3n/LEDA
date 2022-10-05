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

#include "pch.h"

namespace LEDA {

	struct LEDA_API TransformComponent : public IComponent {
		double x{ 0.0 };
		double y{ 0.0 };
		double scale{ 1.0 };
		double rotation{ 0.0 };
	};

}