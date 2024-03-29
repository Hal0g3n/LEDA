/**
 * @file        Transform.h
 * @author      your name (you@domain.com)
 * @brief       Some transformation functions (definitions).
 * @version     0.1
 * @date        07-09-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_TRANSFORM_H_
#define LEDA_TRANSFORM_H_

#include "pch.h"

#include "LEDA_Graphics.h"
#include "LEDA_Math.h"
#include "LEDA_Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace LEDA {

	glm::f32 LEDA_API* transformMatrix(TransformComponent tc);
	glm::f32 LEDA_API* transformMatrix(double x, double y, double sx, double sy, double rotation);
	glm::f32 LEDA_API* transformMatrix(double x, double y, Vector2D scale, double rotation);
	glm::f32 LEDA_API* transformMatrix(Vector2D translation, Vector2D scale, double rotation);

}


#endif // LEDA_TRANSFORM_H_