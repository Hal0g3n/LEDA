/**
 * @file        TransformComponent.h
 * @author      your name (you@domain.com)
 * @brief       Stores transformation information
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_TRANSFORM_COMPONENT_H_
#define LEDA_TRANSFORM_COMPONENT_H_

#include "pch.h"

#include "LEDA_Components.h"
#include "LEDA_Math.h"

namespace LEDA {

	struct LEDA_API TransformComponent : public IComponent {
		Vector2D position{ 0.0, 0.0 };
		Vector2D scale{ 1.0, 1.0 };
		double rotation{ 0.0 };
	};

}

#endif // LEDA_TRANSFORM_COMPONENT_H_