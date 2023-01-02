/**
 * @file        CollisionComponent.h
 * @author      your name (you@domain.com)
 * @brief       Component containing collision data
 * @version     0.1
 * @date        05-10-2022
 *
 * @copyright   Copyright (c) 2022
 */
#pragma once

#ifndef LEDA_COLLISION_COMPONENT_H
#define LEDA_COLLISION_COMPONENT_H

#include "pch.h"
#include "LEDA_Components.h"
#include "CollisionShapes.h"

namespace LEDA {
	struct LEDA_API CollisionComponent : public IComponent {
		CollisionShape* shape;
		bool collide{ true }; //flag for if this object collides with others
		bool reflect{ true }; // flag for reflection upon collision; otherwise just stick
		void (*collisionResponse)(GameObject* other) = 0; // function pointer: collision response when colliding with other
	};
}

#endif //LEDA_COLLISION_COMPONENT_H
