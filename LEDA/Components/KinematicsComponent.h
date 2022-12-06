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

#ifndef LEDA_KINEMATICS_COMPONENT_H_
#define LEDA_KINEMATICS_COMPONENT_H_

#include "pch.h"

#include "LEDA_Components.h"

namespace LEDA {

	struct LEDA_API KinematicsComponent : public IComponent {
		Vec2 vel{ 0.0, 0.0 };
		Vec2 acc{ 0.0, 0.0 };
		double rot_vel{ 0.0 };
		double rot_acc{ 0.0 };
	};

}

#endif // LEDA_KINEMATICS_COMPONENT_H_