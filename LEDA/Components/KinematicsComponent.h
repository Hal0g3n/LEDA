/**
 * @file        LEDA_Components.h
 * @author      your name (you@domain.com)
 * @brief       Component containing kinematics data
 * @version     0.1
 * @date        05-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#include <pch.h>
#include <LEDA_Components.h>

namespace LEDA {

	struct LEDA_API KinematicsComponent : public IComponent {
		Vec2 vel{ 0.0, 0.0 };
		Vec2 acc{ 0.0, 0.0 };
	};

}