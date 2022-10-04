/**
 * @file        Circle.h
 * @author      your name (you@domain.com)
 * @brief       The class representing an Axis-Aligned Bounding Box
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#pragma once
#include <LEDA_Math.h>
#include <LEDA_Shapes.h>

namespace LEDA {
	class Circle : Shape {
		Vec2 m_center;
		double m_radius;
	};
}