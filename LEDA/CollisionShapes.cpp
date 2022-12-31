/******************************************************************************/
/*!
\file		CollisionShapes.cpp
\author
\par
\date   	December 27, 2022
\brief		Source file for the different types of collision shapes provided

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "pch.h"
#include "CollisionShapes.h"

namespace LEDA {
	/******************************************************************************/
/*!
	Builds a line segment with the given center, scale dir
 */
 /******************************************************************************/
	void BuildLineSegment(LEDA::LineSegment& lineSegment,
		const LEDA::Vec2D& pos,
		double scale,
		double dir) {

		lineSegment = LEDA::LineSegment{};

		// Calculate pt0, pt1
		lineSegment.m_pt0 = pos + scale / 2 * Vec2{ cos(dir), sin(dir) };
		lineSegment.m_pt1 = pos + scale / 2 * Vec2{ -cos(dir), -sin(dir) };

		// m_normal = (y, -x)
		lineSegment.m_normal = lineSegment.m_pt1 - lineSegment.m_pt0;
		lineSegment.m_normal.x = -lineSegment.m_normal.x;		   // Negate x
		std::swap(lineSegment.m_normal.x, lineSegment.m_normal.y); // Swap (-x) and y

		// Normalise the normal
		lineSegment.m_normal = lineSegment.m_normal.normalize();

	}
}