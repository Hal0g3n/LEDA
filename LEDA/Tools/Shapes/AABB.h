/**
 * @file        AABB.h
 * @author      your name (you@domain.com)
 * @brief       The class representing an Axis-Aligned Bounding Box
 * @version     0.1
 * @date        15-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#pragma once
#include <LEDA_Shapes.h>

namespace LEDA {
	class AABB : Shape {
		double m_width, m_height;
	};
}