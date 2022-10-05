/**
 * @file        Drawer.cpp
 * @author      your name (you@domain.com)
 * @brief       Game object drawing implementation. Not related to a piece of furniture.
 * @version     0.1
 * @date        07-09-2022
 *
 * @copyright   Copyright (c) 2022
 */


#include "pch.h"

#include "Drawer.h"

#include <GLFW/glfw3.h>

void LEDA::drawObject(IGameObject& object) {

	TransformComponent transformComponent = (TransformComponent) object.getComponent("TransformComponent"); // todo: transform component
	double x = transformComponent.x;
	double y = transformComponent.y;

	transformMatrix(transformComponent);


}