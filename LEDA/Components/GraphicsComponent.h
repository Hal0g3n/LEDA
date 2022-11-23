/**
 * @file        GraphicsComponent.h
 * @author      your name (you@domain.com)
 * @brief       Stores graphics data, such as material type
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_GRAPHICS_COMPONENT_H_
#define LEDA_GRAPHICS_COMPONENT_H_

#include "pch.h"

#include "LEDA_Components.h"
#include "LEDA_Math.h"

namespace LEDA {

	struct LEDA_API GraphicsComponent : public IComponent {
		std::string shape { "triangle" };
		std::string material { "solid" };
		std::vector<double> color { 0.0, 0.0, 0.0, 1.0 };
	};

}

#endif // LEDA_GRAPHICS_COMPONENT_H_