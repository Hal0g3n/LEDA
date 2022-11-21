/**
 * @file        Drawer.h
 * @author      your name (you@domain.com)
 * @brief       Drawing functions. Not a piece of furniture.
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_DRAWER_H_
#define LEDA_DRAWER_H_

#include "pch.h"

#include "LEDA_Graphics.h"
#include "LEDA_Math.h"
#include "LEDA_System.h"
#include "LEDA_Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace LEDA {

	void LEDA_API drawObject(GameObject& object);

	void LEDA_API drawObjects(std::vector<GameObject*> objects);

}


#endif // LEDA_DRAWER_H_