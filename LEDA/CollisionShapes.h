/******************************************************************************/
/*!
\file		CollisionShapes.h
\author 	
\par    	
\date   	December 27, 2022
\brief		Header file for the different types of collision shapes provided

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once

#ifndef LEDA_COLLISION_SHAPES_H
#define LEDA_COLLISION_SHAPES_H

#include "pch.h"

#include "LEDA_Math.h"

namespace LEDA {

	/******************************************************************************/
	/*!
	 */
	 /******************************************************************************/
	struct LEDA_API CollisionShape {
		virtual ~CollisionShape() = 0;
	};

	struct LEDA_API Circle : CollisionShape
	{
		LEDA::Vec2D	m_center;
		float		m_radius{ 1.0f };
		float		m_mass{ 1.0f };
	};

	struct LEDA_API LineSegment : CollisionShape
	{
		LEDA::Vec2D	m_pt0;
		LEDA::Vec2D	m_pt1;

		LEDA::Vec2D	m_normal;
	};

	struct LEDA_API Ray : CollisionShape
	{
		LEDA::Vec2D	m_pt0;
		LEDA::Vec2D	m_dir;
	};

	struct LEDA_API AABB : CollisionShape {
		LEDA::Vec2D min;
		LEDA::Vec2D max;
	};

	/******************************************************************************/
	/*!
	 */
	 /******************************************************************************/
	void LEDA_API BuildLineSegment(LEDA::LineSegment& lineSegment,			// Line segment reference - input
		const LEDA::Vec2D& pos,										// position - input
		double scale,												// scale - input
		double dir);													// direction - input
}

#endif // LEDA_COLLISION_SHAPES_H