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

#include "LEDA_Math.h"

namespace LEDA {

	struct LEDA_API TransformComponent : public IComponent {
		Vector2D position{ 0.0, 0.0 };
		Vector2D scale{ 1.0, 1.0 };
		double rotation{ 0.0 };
	};

}